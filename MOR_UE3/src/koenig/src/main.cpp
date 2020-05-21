#include <ros/ros.h>
#include <iostream>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/GetMap.h>

typedef actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> Server;

void execute(const boost::shared_ptr<const move_base_msgs::MoveBaseGoal> goal, Server* as)
{
  std::cout << "got goal by server\n";
  as->setSucceeded();
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "finder");
    ros::NodeHandle n("~koenig");

    Server ser(n, "jonny_plan",boost::bind(&execute, _1, &ser), false);
    ser.start();
    //ROS_INFO("my goal server starte");

    nav_msgs::GetMap srv_map;
    ros::ServiceClient map_service_client_ = n.serviceClient<nav_msgs::GetMap>("/static_map");

    

    //get map
    if (map_service_client_.call(srv_map))
    {
      ROS_INFO("Map service called successfully");
      const nav_msgs::OccupancyGrid& map (srv_map.response.map);
      pathPlanning.getMapArray(map);
    }
    else
    {
      ROS_ERROR("Failed to call map service");
      return 0;
    }
    
    while(ros::ok()){
		    create_path.publish(pathPlanning.path_result);
        ros::spinOnce();
    }



    ros::spin();
    return 0;
}


