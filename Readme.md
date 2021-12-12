# Seattle_turtlebot_navigation

----
**Date:** 12/2021\
**Author:** Yinuo Wang\
**Email:** ywang3781@gatech.edu
## Introduction

This repository is a ROS package to connect the [Seattle library management application]() with Turtlebot3 with LCM.

The node **goalPublisher** will receive the "*Destination*" channel in LCM and publish */move_base_simple/goal* topic in ROS,

and the node **roboStatePublisher** will receive the "*/move_base/global_costmap/footprint*" and "*/odom*" topic from Turtlebot and publish *RobotState* topic for ROS.

## Build
  * To build this package, all [dependencies](#Dependency) must be installed at first.
  * Create the workspace
     ```
    cd
    mkdir -p ~/catkin_ws/src && cd catkin_ws/src
    catkin_init_workspace
    ```
  * Test the workspace
    ```
    cd catkin_ws
    catkin_make
    ```
  * Configure the environment variable
    ```
    echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
    source ~/.bashrc
    ```
  * Then compile the work space
    ```
    cd catkin_ws
    catkin_make
    ```

## Run
* launch the simulator
```
roslaunch seattle_gazebo turtlebot3_seattle.launch
```
* launch the robot
```
roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=/home/allen/catkin_ws/src/seattle_gazebo/map/map1.yaml
```

# Dependency
* **LCM** (Recommend lcm-1.4)
    * Download package [lcm-1.4.0](https://github.com/AWang-Cabin/MiLAB-Cheetah-Software/releases/download/v1.0.0/lcm-1.4.0.zip) 
    * Unzip to /home and install (Must unzip to /home)
        ```
        cd lcm-1.4.0
        mkdir build && cd build
        cmake ..
        make -j4
        sudo make install
        sudo ldconfig
        ```
      * If meet make error, check your java jdk version
    * [LCM main page](https://lcm-proj.github.io/)

* **ROS (Melodic)**
  * [Install Melodic for Ubuntu-18.x](http://wiki.ros.org/melodic/Installation/Ubuntu)


* **Tutlebot3 ROS package**
  * Install dependency
  ```
  sudo apt install ros-melodic-desktop-full ros-melodic-joy ros-melodic-teleop-twist-joy ros-melodic-teleop-twist-keyboard ros-melodic-laser-proc ros-melodic-rgbd-launch ros-melodic-depthimage-to-laserscan ros-melodic-rosserial-arduino ros-melodic-rosserial-python ros-melodic-rosserial-server ros-melodic-rosserial-client ros-melodic-rosserial-msgs ros-melodic-amcl ros-melodic-map-server ros-melodic-move-base ros-melodic-urdf ros-melodic-xacro ros-melodic-compressed-image-transport ros-melodic-rqt-image-view ros-melodic-gmapping ros-melodic-navigation ros-melodic-interactive-markers ros-melodic-turtlebot3-gazebo
  ```

  * If you have installed ROS and had a catkin workspace, then download turtlebot3
    ```
    cd /catkin_ws/src
    git clone https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git
    git clone https://github.com/ROBOTIS-GIT/turtlebot3.git
    git clone https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git
    ```
  * Compile the package
    ```
    cd /catkin_ws
    rosdep install --from-paths src -i -y 
    catkin_make
    source ./devel/setup.bash

    ```
  * Copy the model to gazebo model folder
    ```
    cd /catkin_ws/src/seattle_turtlebot_nav_ros
    sudo cp -r /gazebo/library ~/.gazebo/models/
    ```
  * Configure the environment variables
    ```
    export TURTLEBOT3_MODEL=waffle_pi
    echo export TURTLEBOT3_MODEL=waffle_pi >> ~/.bashrc
    ```
