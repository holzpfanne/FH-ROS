#include <ros/ros.h>
#include <iostream>
#include <cmath>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/GetMap.h>

typedef actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> Server;

using namespace std;

typedef class pixel{
    public:
        bool is_obstical;
        pair<int, int> parents, location; //parent -1 -1: not visented
        double goal_distance;
        double walked_distance, heuristik;
        //neighbours are all eight around

        pixel(){
            this->is_obstical = false;
        }
}pixel;

class planner{
    public:
        planner(nav_msgs::Path *pub_path);
        void server_callback(const boost::shared_ptr<const move_base_msgs::MoveBaseGoal> received_goal, Server* as);
        void set_map(nav_msgs::OccupancyGrid set_map);

    private:
        nav_msgs::OccupancyGrid map;
        pair<int, int> start, destination;
        nav_msgs::Path *path;
        vector<vector<pixel>> grid_map;

        void plan_path();
        void expand_walls();
        void print_map();
        void calculate_distances();
        bool goal_reached();
        bool goal_valid();
        bool field_valid(pair<int ,int>field);
        void reorder_list(vector<pixel> &list);
};