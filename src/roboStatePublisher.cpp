//
// Created by allen on 12/6/21.
//
// ros
#include <ros/ros.h>
#include <ros/time.h>
#include <geometry_msgs/PolygonStamped.h>
#include <nav_msgs/Odometry.h>
// c++
#include <string>
#include <cstdio>
#include <cmath>
#include <iostream>
// lcm
#include <lcm/lcm-cpp.hpp>
#include "../include/robot_state_t.hpp"
using namespace std;

ros::Publisher pos_pub;
lcm::LCM _lcm;
robot_state_t state_lcm;


void globalPos_Callback(const geometry_msgs::PolygonStamped& globalPos) {
    float global_x, global_y;
    global_x = 0.;
    global_y = 0.;
    for (int i = 0; i < 4; ++i) {
        global_x += globalPos.polygon.points[i].x;
        global_y += globalPos.polygon.points[i].y;

    }
    global_x = global_x *0.25;
    global_y = global_y *0.25;

    state_lcm.robo_x = global_x;
    state_lcm.robo_y = global_y;
//    cout<<state_lcm.robo_x<<endl;

}
void vel_Callback(const nav_msgs::Odometry& vel){
    float vel_x = vel.twist.twist.linear.x;
    float vel_y = vel.twist.twist.linear.y;
    //prepare lcm data
    state_lcm.robo_vx = vel_x;
    state_lcm.robo_vy = vel_y;


    // lcm publish data
    _lcm.publish("RobotState", &state_lcm);

}
int main(int argc, char **argv) {
    ros::Time::init();
//    ros::Rate loop_rate(1);
    ros::init(argc, argv, "roboStatePublisher");
    ros::NodeHandle nh;

    ros::Subscriber sub1 = nh.subscribe("/move_base/global_costmap/footprint", 1, globalPos_Callback);
    ros::Subscriber sub2 = nh.subscribe("/odom", 1, vel_Callback);

    ros::spin();
//    loop_rate.sleep();
}
