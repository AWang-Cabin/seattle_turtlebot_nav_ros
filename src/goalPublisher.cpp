/*
 * This program will act as a lcm subscriber and ros topic publisher at the same time.
 * Date: 12/5/2021
 * Author: Yinuo Wang
 * */

//ros
#include <ros/ros.h>
#include <ros/time.h>
#include <geometry_msgs/PoseStamped.h>
//c++
#include <cstdio>
#include <mutex>
#include <iostream>
//lcm
#include <lcm/lcm-cpp.hpp>
#include "../include/destination_t.hpp"
using namespace std;

ros::Publisher lcm_goal_pub;
float goalPos[2]= {0,0};//{2.5,-0.55};

class LcmSubscribe{
public:
    ~LcmSubscribe(){}
    /*
     * Handle the lcm destination message from java program
     * */
    void handleDestination(const lcm::ReceiveBuffer* rbuf,
                           const std::string& chan, const destination_t* msg){
        (void)rbuf;
        (void)chan;
        lcmMutex.lock();
        goalPos[0] = msg->des_x;
        goalPos[1] = msg->des_y;
        lcmMutex.unlock();
        //cout<<"x:"<<msg->des_x<<" y:"<<msg->des_y<<endl;
    }

private:
    mutex lcmMutex;
};


/*
 * Subscribe the lcm message and publish ros topic
 * */
int main(int argc, char **argv)
{
    // initialize ros
    ros::Time::init();
    ros::Rate loop_rate(1);
    ros::init(argc, argv, "lcm_goal_publisher");
    ros::NodeHandle nh;
    lcm_goal_pub = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal",1);

    // initialize lcm
    lcm::LCM lcm;
    LcmSubscribe destinationHandler;
    lcm.subscribe("Destination", &LcmSubscribe::handleDestination, &destinationHandler);

    uint32_t seqCount = 0;
    while(ros::ok() && 0 == lcm.handle())
    {
        seqCount++;
        geometry_msgs::PoseStamped target_pose;
        // header
        target_pose.header.seq = seqCount;
        target_pose.header.stamp =ros::Time::now();
        target_pose.header.frame_id = "map";
        // pose
        target_pose.pose.position.x = goalPos[0];
        target_pose.pose.position.y = goalPos[1];
        target_pose.pose.position.z = 0.0;
        target_pose.pose.orientation.x = 0.0;
        target_pose.pose.orientation.y = 0.0;
        target_pose.pose.orientation.z = 0.0;
        target_pose.pose.orientation.w = 1.0;
        //publish topic
        lcm_goal_pub.publish(target_pose);
        // update rate = 1Hz
        loop_rate.sleep();
    }
    return -1;

}