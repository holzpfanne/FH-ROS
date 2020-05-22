#include "planner.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "finder");
    ros::NodeHandle n("~koenig");
    nav_msgs::GetMap srv_map;
    planner custom;

    //int Server
    Server ser(n, "jonny_plan",boost::bind(&planner::server_callback, &custom, _1, &ser), false);
    
    //int map Client
    ros::ServiceClient map_service_client = n.serviceClient<nav_msgs::GetMap>("/static_map");

    //get map
    map_service_client.waitForExistence();
    if (map_service_client.call(srv_map))
    {
        ROS_INFO("Map service called successfully");
        //load map into planner
        custom.set_map(srv_map.response.map);
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


