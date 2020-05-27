#include <ros/ros.h>
#include <iostream>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char **argv) {

    ros::init(argc, argv, "goal_pub");
    ros::NodeHandle n;


    //Init MoveBaseClient
    MoveBaseClient ac("move_base", true);

    //wait for the action server to start
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the server to come up");
    }

    //def goal
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    n.param<double>("goal_pub/target_x", goal.target_pose.pose.position.x, 7);
    n.param<double>("goal_pub/target_y", goal.target_pose.pose.position.y, 7);
    goal.target_pose.pose.orientation.w = 1;

    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Path planned!, exiting...");
    else
        ROS_INFO("Failed to plan path, exiting...");

    return 0;
}