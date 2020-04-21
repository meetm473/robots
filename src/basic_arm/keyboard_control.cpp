// ROS Libraries
#include <ros/ros.h>
#include <std_msgs/Float64.h>

// Misc Libraries
#include <termios.h>
#include <thread>

// defining publishers
ros::Publisher set_arm_0;
ros::Publisher set_arm_1;
ros::Publisher set_gripper_hand;

// Control variables
std_msgs::Float64 set_value;
float cur_set_point[3];													// Set points from user: 0 - arm_0; 1 - arm_1; 2 - gripper;
float prev_set_point[3];

// Misc variables
static struct termios old, current;
bool do_not_quit = true;


/* Receiving set point from the user */
void initTermios(void){
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  current.c_lflag &= ~ECHO; /* set no echo mode */
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}
void resetTermios(void){
  tcsetattr(0, TCSANOW, &old);
}
char getch(void){
  char ch;
  initTermios();
  ch = getchar();
  resetTermios();
  return ch;
}
void read_input(void){
	char input;
	
	while(do_not_quit){
		input = getch();
		
		switch(input){
			case 'q': do_not_quit = false;
					  break;
			case 'd': cur_set_point[0] = cur_set_point[0] + 0.05;
					  break;
			case 'a': cur_set_point[0] = cur_set_point[0] - 0.05;
					  break;
			case 'l': cur_set_point[1] = cur_set_point[1] + 0.05;
					  break;
			case 'j': cur_set_point[1] = cur_set_point[1] - 0.05;
					  break;
			case 'n': cur_set_point[2] = cur_set_point[2] + 0.05;
					  break;
			case 'v': cur_set_point[2] = cur_set_point[2] - 0.05;
					  break;
		}		
	}
}

/* Sending set point to Gazebo */
void send_set_points(void){
	for(int i=0;i<3;i++){
		if(prev_set_point[i] != cur_set_point[i]){
			set_value.data = cur_set_point[i];
			switch(i){
				case 0: set_arm_0.publish(set_value); break;
				case 1: set_arm_1.publish(set_value); break;
				case 2: set_gripper_hand.publish(set_value); break;
			}
			ros::spinOnce();
			prev_set_point[i] = cur_set_point[i];
		}			
	}
}

int main(int argc, char **argv){
	
	ros::init(argc,argv,"keyboard_control");
	ros::NodeHandle nh;
	ros::Rate rate(2);
	
	// advertising the publishers
	set_arm_0 = nh.advertise<std_msgs::Float64>("/robots/basic_arm/arm_0_pos_controller/command", 1000);
	set_arm_1 = nh.advertise<std_msgs::Float64>("/robots/basic_arm/arm_1_pos_controller/command", 1000);
	set_gripper_hand = nh.advertise<std_msgs::Float64>("/robots/basic_arm/gripper_hand_pos_controller/command", 1000);
	
	// setting default values
	for(int i=0;i<3;i++){
		cur_set_point[i] = 0;
		prev_set_point[i] = 0;
	}
	
	std::cout << "\nUse the following commands: "<< std::endl
			<< "d: increase arm_0 angle by 0.05 rad" << std::endl
			<< "a: decrease arm_0 angle by 0.05 rad" << std::endl
			<< "l: increase arm_1 angle by 0.05 rad" << std::endl
			<< "j: decrease arm_1 angle by 0.05 rad" << std::endl
			<< "n: close gripper" << std::endl
			<< "v: open gripper" << std::endl
			<< "q: to quit\n" << std::endl;
			
	std::thread reading_input_thread(read_input);
	reading_input_thread.detach();

	while(do_not_quit && ros::ok()){
		send_set_points();
	}
	
	std::cout << "Successfully ended the program."<< std::endl;
}
