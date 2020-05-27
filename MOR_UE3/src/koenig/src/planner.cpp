#include "planner.h"

pixel::pixel(){
    this->is_obstical = false;
    this->parents.first = -1;
    this->parents.second = -1;
}

planner::planner(ros::Publisher *prt_path_pub){
    this->path_pup = prt_path_pub;
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
            grid_map[i][j].location.first = i;
            grid_map[i][j].location.second = j;
        }
    }
    this->expand_walls();
}

void planner::publish_path(){
    //waiting for Rviz to start with sleep
    ros::Duration(2.0).sleep();
    //while(ros::ok()){
    this->path_pup->publish(this->path);
    ROS_INFO("Path published");
    //}
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

    boost::shared_ptr<tf2_msgs::TFMessage const> msg = ros::topic::waitForMessage<tf2_msgs::TFMessage> ("/tf");
    const tf2_msgs::TFMessage *start_pose = msg.get();

    this->start.second =  start_pose->transforms[0].transform.translation.x / this->map.info.resolution;
    this->start.first = start_pose->transforms[0].transform.translation.y / this->map.info.resolution;
    
    //print goal
    cout << "Start\n";
    cout << "y: " << start_pose->transforms[0].transform.translation.y << "m" << endl;
    cout << "x: " << start_pose->transforms[0].transform.translation.x << "m" << endl;

    cout << "Goal\n";
    cout << "x: " << goal->target_pose.pose.position.x << "m" << endl;
    cout << "y: " << goal->target_pose.pose.position.y << "m" << endl;
    

    if(this->plan_path()) {as->setSucceeded();}
    else {as->setAborted();}
    
}

void planner::rviz_server_callback(const boost::shared_ptr<const geometry_msgs::PoseStamped> received_goal){

    cout << "rviz callback\n";
    const geometry_msgs::PoseStamped* goal = received_goal.get();
    this->destination.first = goal->pose.position.y / this->map.info.resolution;
    this->destination.second = goal->pose.position.x / this->map.info.resolution;

    boost::shared_ptr<tf2_msgs::TFMessage const> msg = ros::topic::waitForMessage<tf2_msgs::TFMessage> ("/tf");
    const tf2_msgs::TFMessage *start_pose = msg.get();

    this->start.second =  start_pose->transforms[0].transform.translation.x / this->map.info.resolution;
    this->start.first = start_pose->transforms[0].transform.translation.y / this->map.info.resolution;
    
    //print goal
    cout << "Start\n";
    cout << "x: " << start_pose->transforms[0].transform.translation.x << "m" << endl;
    cout << "y: " << start_pose->transforms[0].transform.translation.y << "m" << endl;

    cout << "Goal\n";
    cout << "x: " << goal->pose.position.x << "m" << endl;
    cout << "y: " << goal->pose.position.y << "m" << endl;
    

    this->plan_path();
}

bool planner::plan_path(){
    this->calculate_distances();
    vector<pair<int, int>> neighbors = {{-1,0}, {1,0}, {0, 1}, {0,-1}, {-1, 1}, {-1,-1}, {1,1},{1,-1}};

    double diagonal = sqrt(2);

    if(!this->start_valid()){
        ROS_INFO("start not valid");
        return false;
    }
    if(!this->goal_valid()){
        ROS_INFO("goal not valid");
        return false;
    }
    if(this->goal_prereached()){
        ROS_INFO("goal equals start point");
        return false;
    }
    ROS_INFO("start and goal valid");

    vector<pixel>checked, list;
    pixel tmp = this->grid_map[this->start.first][this->start.second];
    tmp.parents = this->start;
    tmp.location = this->start;
    tmp.walked_distance = 0;
    list.push_back(tmp);

    pair<int, int> now = this->start;
 
    while(1){
        for(int i = 0;i < 8;i++){
            //field in map?
            if(!field_valid(list[0].location ,neighbors[i])) {continue;}
            tmp = this->grid_map[list[0].location.first+neighbors[i].first][list[0].location.second+neighbors[i].second];

            if(abs(neighbors[i].first) + abs(neighbors[i].second) == 2 /*if diagonal*/) {tmp.walked_distance = list[0].walked_distance + diagonal;}
            else {tmp.walked_distance = list[0].walked_distance + 1;}
            tmp.heuristik = tmp.goal_distance + tmp.walked_distance;

            //if old version shorter -> continue
            if(this->grid_map[list[0].location.first+neighbors[i].first][list[0].location.second+neighbors[i].second].walked_distance <= tmp.walked_distance 
            && this->grid_map[list[0].location.first+neighbors[i].first][list[0].location.second+neighbors[i].second].parents.first != -1
            && this->grid_map[list[0].location.first+neighbors[i].first][list[0].location.second+neighbors[i].second].parents.second != -1) {continue;}

            //set parent
            tmp.parents.first = list[0].location.first;
            tmp.parents.second = list[0].location.second;
            this->grid_map[list[0].location.first+neighbors[i].first][list[0].location.second+neighbors[i].second] = tmp;
            list.push_back(tmp);
        }
        list.erase(list.begin());
        this->reorder_list(list);

        //check if goal found
        if(this->goal_found(list)) {break;}
    }
    ROS_INFO("path found");

    //follow destination to start
    this->draw_path();
    this->publish_path();
    return true;
}

void planner::draw_path(){
    stack<pixel> points;
    pair<int, int> tracker = this->destination;
    while(this->grid_map[tracker.first][tracker.second].location.first != this->start.first
       || this->grid_map[tracker.first][tracker.second].location.second != this->start.second)
    {
        points.push(this->grid_map[tracker.first][tracker.second]);
        tracker = this->grid_map[tracker.first][tracker.second].parents;
    }

    geometry_msgs::PoseStamped tmp;
    pixel on_view;

    this->path.poses.clear();
    this->path.header.frame_id = "map";

    do{
        on_view = points.top();
        points.pop();

        tmp.pose.position.x = on_view.location.second * this->map.info.resolution;
        tmp.pose.position.y = on_view.location.first * this->map.info.resolution;
        tmp.header.frame_id = "map";
        tmp.header.seq = 0;
        tmp.pose.position.z = 0;

        this->path.poses.push_back(tmp);
    }while (!points.empty());
}

bool planner::goal_found(vector<pixel> &list){
    if(this->grid_map[this->destination.first][this->destination.second].parents.first != -1 
    && this->grid_map[this->destination.first][this->destination.second].parents.second != -1) {
        for(pixel ele : list){
            if(ele.walked_distance < this->grid_map[this->destination.first][this->destination.second].walked_distance) {return false;}
        }
        return true;
    }
    return false;
}

void planner::reorder_list(vector<pixel> &list){
    unsigned int biggest_index = 0;
    double biggest = 0;

    if(list.size() <= 1 || list.empty() ) {return;}

    for(int i = 0; i < list.size(); i++){
        for(int j = 0 + i; j < list.size(); j++){
            if(list[j].heuristik > biggest) {
                biggest = list[j].heuristik;
                biggest_index = j;
            }
        }
        biggest = 0;

        list.insert(list.begin(), list[biggest_index]);
        list.erase(list.begin() + biggest_index + 1);
    }
}

bool planner::goal_prereached(){
    if(destination == start) {return true;}
    return false;
}

bool planner::field_valid(pair<int ,int>field, pair<int ,int>neighbor){
    //goal on map and not in wall
    if(field.first + neighbor.first < 0
    || field.second + neighbor.second < 0
    || field.first + neighbor.first >= this->map.info.height
    || field.second + neighbor.second >= this->map.info.width) {return false;}

    if(this->grid_map[field.first + neighbor.first][field.second + neighbor.second].is_obstical) {return false;}

    return true;
}

bool planner::goal_valid(){
    //goal on map and not in wall
    if(this->destination.first < 0
    || this->destination.second < 0
    || this->destination.first >= this->map.info.height
    || this->destination.second >= this->map.info.width) {return false;}

    if(this->grid_map[this->destination.first][this->destination.second].is_obstical) {return false;}
    return true;
}

bool planner::start_valid(){
    //goal on map and not in wall
    if(this->start.first < 0
    || this->start.second < 0
    || this->start.first >= this->map.info.height
    || this->start.second >= this->map.info.width) {return false;}

    if(this->grid_map[this->start.first][this->start.second].is_obstical) {return false;}
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