#include "planner.h"

planner::planner(){

}

void planner::set_map(nav_msgs::OccupancyGrid set_map){
    this->map = set_map;
}

void planner::server_callback(const boost::shared_ptr<const move_base_msgs::MoveBaseGoal> received_goal, Server* as){

    std::cout << "got goal by server\n";
    const move_base_msgs::MoveBaseGoal* goal = received_goal.get();
    this->destination.first = goal->target_pose.pose.position.x * this->map.info.resolution;
    this->destination.second = goal->target_pose.pose.position.y * this->map.info.resolution;

    //print goal
    cout << "print goal\n";
    cout << "x: " << this->destination.first << endl;
    cout << "y: " << this->destination.second << endl;
    
}