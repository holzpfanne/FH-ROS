#include <ros/ros.h>
#include <iostream>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/GetMap.h>

using namespace std;

typedef actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> Server;

nav_msgs::Path planner(pair<int, int> goal, nav_msgs::GetMap srv_map) {
    //plan path.....
}

void execute(const boost::shared_ptr<const move_base_msgs::MoveBaseGoal> received_goal, Server* as, nav_msgs::GetMap& srv_map)
{
    std::cout << "got goal by server\n";
    const move_base_msgs::MoveBaseGoal* goal = received_goal.get();

    //plan path
    
    cout << "print goal\n";
    cout << "x: " << goal->target_pose.pose.position.x << endl;
    pair<int, int> index_goal((int)(goal->target_pose.pose.position.x*0.2), (int)(goal->target_pose.pose.position.y*0.2));
    planner(index_goal, srv_map);
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "finder");
    ros::NodeHandle n("~koenig");
    nav_msgs::GetMap srv_map;

    //int Server
    Server ser(n, "jonny_plan",boost::bind(&execute, _1, &ser, srv_map), false);
    
    //int 
    ros::ServiceClient map_service_client = n.serviceClient<nav_msgs::GetMap>("/static_map");

    //get map
    map_service_client.waitForExistence();
    if (map_service_client.call(srv_map))
    {
        ROS_INFO("Map service called successfully");
        const nav_msgs::OccupancyGrid& map (srv_map.response.map);
    }
    else
    {
        ROS_ERROR("Failed to call map service");
        return 0;
    }
    
    // start server
    ser.start();

    ros::spin();
    return 0;
}


