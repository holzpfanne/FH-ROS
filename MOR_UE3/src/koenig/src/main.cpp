#include <ros/ros.h>
#include <iostream>
#include <nav_msgs/OccupancyGrid.h>

nav_msgs::OccupancyGrid map;
bool loaded = false;

void get_map(const nav_msgs::OccupancyGrid map_in){

    map = map_in;
    loaded = true;
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "finder");
    ros::NodeHandle n("~koenig");

    ros::Subscriber map_loader = n.subscribe<nav_msgs::OccupancyGrid>("OccupancyGrid", 1, get_map);


    while(!loaded);


    return 0;
}


