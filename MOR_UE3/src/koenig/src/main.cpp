#include <ros/ros.h>
#include <iostream>
#include <move_base_msgs/MoveBaseActionGoal.h>

int main(int argc, char **argv) {

    ros::init(argc, argv, "finder");
    ros::NodeHandle n("~koenig");

    move_base_msgs::MoveBaseActionGoal goal;
    goal.goal.target_pose.pose.position.x = 7.5;
    goal.goal.target_pose.pose.position.y = 7.1;
    goal.goal.target_pose.pose.orientation.w = 1;
    goal.goal.target_pose.header.frame_id = "map";

    ros::Publisher goal_pub = n.advertise<move_base_msgs::MoveBaseActionGoal>("goal", 1);

    ros::Rate myclock(10);
    
    while(ros::ok()){
        goal_pub.publish(goal);
        ros::spinOnce();
    }
    

    return 0;
}


