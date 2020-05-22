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
    this->expand_walls();
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
    
    /*
    this->print_map();
    this->expand_walls();
    cout << endl;
    this->print_map();
    */
    this->plan_path();
    as->setSucceeded();
}

void planner::plan_path(){
    this->calculate_distances();
    
}

void planner::expand_walls(){
    //in order to privent the robot from driving into the wall the wall will be made bigger //Dilatation
    int matrix[3][3] = {{1,1,1}, {1,2,1}, {1,1,1}}; 
    int height = this->map.info.height;
    int width = this->map.info.width;

    vector<vector<bool>> new_grid_map(height, vector<bool>(width, 0));
    
    for(int i = 0,k; i < height; i++){
        for(int j = 0; j < width; j++, k++){
            int sum = 0;
            vector<pair<int, int>> round = {{-1,0}, {1,0}, {0, 1}, {0,-1}, {-1, 1}, {-1,-1}, {1,1},{1,-1}};

            for(int k = 0; k < 8;k++){
                if(i+round[k].first < 0 || j+round[k].second < 0 || i+round[k].first >= height || j+round[k].second >= width) {continue;}
                sum += this->grid_map[i+round[k].first][j+round[k].second].is_obstical * matrix[1+round[k].first][1+round[k].second];
            }
            if(sum > 0) {new_grid_map[i][j] = true;}
        }
    }

    //copy new grid into map
    for(int i = 0,k; i < height; i++){
        for(int j = 0; j < width; j++, k++){
            this->grid_map[i][j].is_obstical = new_grid_map[i][j];
        }
    }
}

void planner::calculate_distances(){
    int height = this->map.info.height;
    int width = this->map.info.width;

    for(int i = 0,k; i < height; i++){
        for(int j = 0; j < width; j++, k++){
            this->grid_map[i][j].goal_distance = sqrt(pow(this->destination.first-i, 2) + pow(this->destination.second-j, 2));
        }
    }
}