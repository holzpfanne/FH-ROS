#include <ros/ros.h>
#include <iostream>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <actionlib_msgs/GoalStatusArray.h>

actionlib_msgs::GoalStatusArray gloal_status;

void callback(const actionlib_msgs::GoalStatusArray msg){

    gloal_status = msg;

}

int main(int argc, char **argv) {

    ros::init(argc, argv, "finder");
    ros::NodeHandle n("~koenig");

    geometry_msgs::PoseStamped mygoal;
    mygoal.pose.position.x = 7.5;
    mygoal.pose.position.y = 7.0;
    mygoal.pose.orientation.w = 1;
    mygoal.header.frame_id = "map";

    //move_base_msgs::MoveBaseActionGoal goal;
    //goal.goal.target_pose.pose.position.x = 7.5;
    //goal.goal.target_pose.pose.position.y = 7.1;
    //goal.goal.target_pose.pose.orientation.w = 1;
    //goal.goal.target_pose.header.frame_id = "map";

    ros::Publisher goal_pub = n.advertise<geometry_msgs::PoseStamped>("goal", 1);
    //ros::Subscriber sub_status = n.subscribe<actionlib_msgs::GoalStatusArray>("/move_base/status", 1, callback);

    ros::Rate myclock(10);
    
    while(ros::ok()){
        //if(gloal_status.status_list.empty() == false && gloal_status.status_list[0].status == 1) {break;}
        goal_pub.publish(mygoal);
        ros::spinOnce();
    }
    

    return 0;
}


