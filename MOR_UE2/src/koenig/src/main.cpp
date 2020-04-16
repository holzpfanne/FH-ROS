#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

geometry_msgs::Pose2D current_pose, soll_pose;
ros::Publisher pub_pose2d;
ros::Publisher movement_pub;

bool go;

void get_soll(const geometry_msgs::Pose2D soll){

    //get soll pose
    soll_pose = soll;
    go = true;
    ROS_INFO("received pose");
}

void sub_callback(const nav_msgs::OdometryConstPtr msg)
{
    // linear position
    current_pose.x = msg->pose.pose.position.x;
    current_pose.y = msg->pose.pose.position.y;

    // quaternion to RPY conversion
    tf::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);

    // angular position
    current_pose.theta = yaw;
    pub_pose2d.publish(current_pose);
}

int main(int argc, char **argv)
{
    double alpha, beta, distance; //d
    go = false;
    //init ROS
    ros::init(argc, argv, "DFD");
    ros::NodeHandle n("~koenig");
    ros::Subscriber sub_odometry = n.subscribe<nav_msgs::OdometryConstPtr>("odom", 1, sub_callback);
    ros::Subscriber sub_soll = n.subscribe<geometry_msgs::Pose2D>("soll", 1, get_soll);
    movement_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    pub_pose2d = n.advertise<geometry_msgs::Pose2D>("turtlebot_pose2d", 1);
    geometry_msgs::Twist move_cmd;

    ros::Rate calc_rate(10); //calc rate
    const double PI = 3.14159265358979323846;

    //wait for soll pose
    while(!go){ros::spinOnce();};

    /*
    //           /_
    //          /  \
    //         /   beta
    // Y soll /      \
    // A     *-----|--|----x//X 
    // |    / \  theta|
    // |  d/   \_/   /
    // |  /_    \   /
    // | /  \    \_/
    // |/   alpha_\/
    //0|------|---------------> X
    // 0
    */

    //calc angle and distance
    alpha = atan2(soll_pose.y, soll_pose.x);
    distance = sqrt(pow(soll_pose.x,2)+pow(soll_pose.y,2));

    //first turn
    ROS_INFO("first turn");
    while (ros::ok() && (current_pose.theta > alpha && alpha < 0) 
                        ||(current_pose.theta < alpha && alpha > 0)
                        ||(current_pose.theta == 0 && alpha != 0))
    {
        move_cmd.linear.x = 0;
        if(alpha < 0) {move_cmd.angular.z = -0.2;}
        else {move_cmd.angular.z = 0.2;}
        movement_pub.publish(move_cmd);
        ros::spinOnce();
        calc_rate.sleep();
    }

    //stop
    move_cmd.linear.x = 0;
    move_cmd.angular.z = 0;
    movement_pub.publish(move_cmd);
    ros::spinOnce();
    calc_rate.sleep();

    //drive forward
    ROS_INFO("forward");
    while (ros::ok() && (sqrt(pow(current_pose.x,2)+pow(current_pose.y,2)) < distance))
    {
        move_cmd.linear.x = 0.2;
        move_cmd.angular.z = 0;
        movement_pub.publish(move_cmd);
        ros::spinOnce();
        calc_rate.sleep();
    }

    //stop
    move_cmd.linear.x = 0;
    move_cmd.angular.z = 0;
    movement_pub.publish(move_cmd);
    ros::spinOnce();
    calc_rate.sleep();

    beta = soll_pose.theta - alpha;

    //second turn
    ROS_INFO("second turn");
    while (ros::ok() && (current_pose.theta < soll_pose.theta && beta > 0) 
                        ||(current_pose.theta > soll_pose.theta && beta < 0))
    {
        move_cmd.linear.x = 0;
        if(beta > 0) {move_cmd.angular.z = 0.3;}
        else {move_cmd.angular.z = -0.3;}
        movement_pub.publish(move_cmd);
        ros::spinOnce();
        calc_rate.sleep();
    }

    //stop
    move_cmd.linear.x = 0;
    move_cmd.angular.z = 0;
    movement_pub.publish(move_cmd);
    ros::spinOnce();
    ROS_INFO("finished");

    return 0;
}