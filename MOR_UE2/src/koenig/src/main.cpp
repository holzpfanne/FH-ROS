#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

geometry_msgs::Pose2D current_pose, soll_pose;
ros::Publisher pub_pose2d;
ros::Publisher movement_pub;

bool go = false;

void get_soll(const geometry_msgs::Pose2D soll){

    //get soll pose
    soll_pose = soll;
    go = true;
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
    int quatrant;
    double alpha, beta, distance; //d
    
    ros::init(argc, argv, "rectangle");
    ros::NodeHandle n;
    ros::Subscriber sub_odometry = n.subscribe<nav_msgs::OdometryConstPtr>("odom", 1, sub_callback);
    ros::Subscriber sub_odometry = n.subscribe<geometry_msgs::Pose2D>("setter", 1, get_soll);
    movement_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    pub_pose2d = n.advertise<geometry_msgs::Pose2D>("turtlebot_pose2d", 1);

    ros::Rate calc_rate(10); //calc rate
    const double PI = 3.14159265358979323846;

    while(!go);

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
    
    alpha = atan2(soll_pose.y, soll_pose.x);
    quatrant = (int)(alpha / (PI/2));
    distance = sqrt(pow(soll_pose.x,2)+pow(soll_pose.y,2));
    beta = alpha - soll_pose.theta;

    //first turn
    while (ros::ok() && (current_pose.theta < alpha && quatrant < 2) 
                        ||(current_pose.theta > alpha && quatrant > 1))
    {
        geometry_msgs::Twist move;
        //Set speed
        move.linear.x = 0;
        if(quatrant < 2) {move.angular.z = 0.3;}
        else {move.angular.z = -0.3;}
        movement_pub.publish(move);
        ros::spinOnce();
        calc_rate.sleep();
    }

    //drive linear
    while (ros::ok() && (sqrt(pow(current_pose.x,2)+pow(current_pose.y,2)) < distance))
    {
        geometry_msgs::Twist move;
        //Set speed
        move.linear.x = 0.2; //speed value m/s
        move.angular.z = 0;
        movement_pub.publish(move);
        ros::spinOnce();
        calc_rate.sleep();
    }

    //second turn
    while (ros::ok() && (current_pose.theta < beta && beta < 180) 
                        ||(current_pose.theta > beta && beta >= 180))
    {
        geometry_msgs::Twist move;
        //Set speed
        move.linear.x = 0;
        if(beta < 180) {move.angular.z = 0.3;}
        else {move.angular.z = -0.3;}
        movement_pub.publish(move);
        ros::spinOnce();
        calc_rate.sleep();
    }

    //stop
    geometry_msgs::Twist move;
    move.linear.x = 0;
    move.angular.z = 0;
    movement_pub.publish(move);

    ros::spinOnce();
    return 0;
}