#include "planner.h"

planner::planner(nav_msgs::Path *pub_path){
    this->path = pub_path;

    this->start.first = 14;
    this->start.second = 2;
}

void planner::set_map(nav_msgs::OccupancyGrid set_map){

    this->map = set_map;
    //load map into grod_map for forther algorythm
    int height = this->map.info.height;
    int width = this->map.info.width;
    this->grid_map.resize(height, vector<pixel>(width));
    
    for(int i = 0,k = 0; i < height; i++){
        for(int j = 0; j < width; j++, k++){
            if(this->map.data[k] > 0) {grid_map[i][j].is_obstical = true;}
        }
    }
}

void planner::expand_walls(){
    //in order
}

void planner::print_map(){
    int height = this->map.info.height;
    int width = this->map.info.width;
    string out;
    for(int i = 0,k; i < height; i++){
        for(int j = 0; j < width; j++, k++){
            if(this->grid_map[i][j].is_obstical) {out += "#";}
            else {out += " ";}
        }
        out += "\n";
    }
    cout << out;
}

void planner::server_callback(const boost::shared_ptr<const move_base_msgs::MoveBaseGoal> received_goal, Server* as){

    const move_base_msgs::MoveBaseGoal* goal = received_goal.get();
    this->destination.first = goal->target_pose.pose.position.x / this->map.info.resolution;
    this->destination.second = goal->target_pose.pose.position.y / this->map.info.resolution;

    /*
    //print goal
    cout << "print start\n";
    cout << "x: " << this->start.first << endl;
    cout << "y: " << this->start.second << endl;

    cout << "print goal\n";
    cout << "x: " << this->destination.first << endl;
    cout << "y: " << this->destination.second << endl;
    */
    
    this->print_map();
}

void planner::plan_path(){

}