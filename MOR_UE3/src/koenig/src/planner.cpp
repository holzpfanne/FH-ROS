#include "planner.h"

pixel::pixel(){
    this->is_obstical = false;
    this->parents.first = -1;
    this->parents.second = -1;
}

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
    vector<pair<int, int>> neighbors = {{-1,0}, {1,0}, {0, 1}, {0,-1}, {-1, 1}, {-1,-1}, {1,1},{1,-1}};

    double diagonal = sqrt(2);

    if(!this->goal_valid()){
        ROS_INFO("goal not valid");
        return;
    }
    if(this->goal_prereached()){
        ROS_INFO("goal equals start point");
        return;
    }

    vector<pixel>checked, list;
    pixel tmp = this->grid_map[this->start.first][this->start.second];
    tmp.parents = this->start;
    tmp.location = this->start;
    tmp.walked_distance = 0;
    list.push_back(tmp);

    pair<int, int> now = this->start;
 
    while(1){
        //list.push_back(tmp);
        for(int i = 0;i < 8;i++){
            tmp = this->grid_map[list[0].location.first+neighbors[i].first][list[0].location.second+neighbors[i].second];
            if(!field_valid(tmp.location)) {continue;}

            if(abs(neighbors[i].first) + abs(neighbors[i].second) == 2) {tmp.walked_distance = list[0].walked_distance + diagonal;}
            else {tmp.walked_distance = list[0].walked_distance + 1;}
            tmp.heuristik = tmp.goal_distance + tmp.walked_distance;

            list.push_back(tmp);
        }

        checked.push_back(list[0]);
        list.erase(list.begin());
        this->reorder_list(list);

        //check if goal found
        if(this->goal_found(list)) {break;}
    }

    //follow destination to start
    this->draw_path();
    
}

void planner::draw_path(){



}

bool planner::goal_found(vector<pixel> &list){
    if(this->grid_map[this->destination.first][this->destination.second].parents.first != -1 
    && this->grid_map[this->destination.first][this->destination.second].parents.second != -1) {
        for(pixel ele : list){
            if(ele.walked_distance < list[0].walked_distance ) {return false;}
            return true;
        }
    }
    
    return false;
}

void planner::reorder_list(vector<pixel> &list){
    unsigned int search_index = 0, biggest_index;
    double biggest = 0;

    for(int i = 0; i < list.size() - 1; i++){
        for(int j = 0 + search_index; j < list.size(); j++){
            if(list[(int)i].heuristik > biggest) {
                biggest = list[j].heuristik;
                biggest_index = j;
            }
        }
        swap(list[search_index],list[biggest_index]);
        search_index++;
    }
}

bool planner::goal_prereached(){
    if(destination == start) {return true;}
    return false;
}

bool planner::field_valid(pair<int ,int>field){
    //goal on map and not in wall
    if(field.first < 0
    || field.second < 0
    || field.first >= this->map.info.height
    || field.second >= this->map.info.width) {return false;}

    if(this->grid_map[field.first][field.first].is_obstical) {return false;}
    return true;
}

bool planner::goal_valid(){
    //goal on map and not in wall
    if(this->destination.first < 0
    || this->destination.second < 0
    || this->destination.first >= this->map.info.height
    || this->destination.second >= this->map.info.width) {return false;}

    if(this->grid_map[this->destination.first][this->destination.first].is_obstical) {return false;}
    return true;
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
            vector<pair<int, int>> neighbors = {{-1,0}, {1,0}, {0, 1}, {0,-1}, {-1, 1}, {-1,-1}, {1,1},{1,-1}};

            for(int k = 0; k < 8;k++){
                if(i+neighbors[k].first < 0 || j+neighbors[k].second < 0 || i+neighbors[k].first >= height || j+neighbors[k].second >= width) {continue;}
                sum += this->grid_map[i+neighbors[k].first][j+neighbors[k].second].is_obstical * matrix[1+neighbors[k].first][1+neighbors[k].second];
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