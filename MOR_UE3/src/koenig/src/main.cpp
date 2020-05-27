#include "planner.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "finder");
    ros::NodeHandle n("~koenig");
    nav_msgs::GetMap srv_map;
    

    //init plan publisher
    ros::Publisher path = n.advertise<nav_msgs::Path>("/custom_path", 1);
    ROS_INFO("pub init");

    //init planner instance
    planner custom(&path);

    //init rviz goal subscriber
    ros::Subscriber rviz_goal = n.subscribe<geometry_msgs::PoseStamped>("/rviz_goal", 1, boost::bind(&planner::rviz_server_callback, &custom, _1));
    
    //init goal Server
    Server ser(n, "jonny_plan",boost::bind(&planner::server_callback, &custom, _1, &ser), false);
    ROS_INFO("goal server init");
    
    //init map Client
    ros::ServiceClient map_service_client = n.serviceClient<nav_msgs::GetMap>("/static_map");
    ROS_INFO("map client init");

    //get map
    map_service_client.waitForExistence();
    ROS_INFO("mapserver available");
    if (map_service_client.call(srv_map))
    {
        ROS_INFO("Map service called successfully");
        //load map into planner
        custom.set_map(srv_map.response.map);
        ROS_INFO("loaded map into planner");
    }
    else
    {
        ROS_ERROR("Failed to call map service");
        return 0;
    }
    
    // start goal server
    ser.start();

    //let ROS do it's magic 
    ros::spin();
    return 0;
}