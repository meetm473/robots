# robots

This is a **ROS package**, consisting of all the files used to create the following robots by the author:
1. basic_arm
2. claw
3. prismatic_revolute_test
4. tri_wheeler

SolidWorks 2019 Premium has been used for modelling every robot in this repository.

## About the robots

### basic_arm
A basic arm with stationary base with a shoulder, and an elbow joint along with a gripper to grab objects. Each joint is controlled using keyboard.
#### Resources referred and used:
* [Mastering ROS for Robotics Programming][8]
#### Commands
To view the model in *RViz*:
```
roslaunch robots display-rviz.launch model:='$(find robots)/urdf/basic_arm.xacro'
```
To control the bot on Gazebo:
```
roslaunch robots gazebo.launch model_config:='$(find robots)/launch/basic_arm.launch'
```
```
rosrun robots keyboard_control
```

---
### claw
A three fingered claw. The purpose of this robot is to understand how to simulate links with more than one joint in Gazebo using URDF. 
The claw can the spawned into the Gazebo environment, but on application of gravity, it doesn't behave as expected. It's simulation is still under construction.
#### Resources referred and used:
* Model of the claw was taken from [here][9] and modified.
---
### prismatic_revolute_test
A test model to understand the **mimic** joint feature in URDF.

---
### tri_wheeler
First robot to understand the [SW2URDF][10] plugin and top-down approach of modelling in SolidWorks.
#### Resources referred and used:
* [Tutorial][11] on how to convert a SW model to URDF.

## About the folders
1. **config** - contains controller *yaml* for each robot and *RViz* configuration files.
2. **launch** - contains the ROS launch files.
3. **meshes** - contains *.STL* files.
4. **multimedia** - contains images of the robots and videos of their simulation.
5. **src** - contains *.cpp* source files.
6. **sw_files** - contains SolidWorks files used to model the robots.
7. **urdf** - contains URDF files.
8. **worlds** - contains *.world* files for Gazebo.

[8]:https://mastering-ros.com/
[9]:https://grabcad.com/library/gripper-148
[10]:http://wiki.ros.org/sw_urdf_exporter
[11]:https://blogs.solidworks.com/teacher/wp-content/uploads/sites/3/WPI-Robotics-SolidWorks-to-Gazebo.pdf
