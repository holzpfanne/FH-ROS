#include <ros/ros.h>
#include <iostream>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/GetMap.h>

typedef actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> Server;

using namespace std;

class planner{
    public:
        planner();
        void server_callback(const boost::shared_ptr<const move_base_msgs::MoveBaseGoal> received_goal, Server* as);
        void set_map(nav_msgs::OccupancyGrid set_map);

    private:
        nav_msgs::OccupancyGrid map;
        pair<int, int> start, destination;


        void plan_path(const move_base_msgs::MoveBaseGoal);

};