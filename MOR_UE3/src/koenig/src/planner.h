#include <ros/ros.h>
#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/GetMap.h>
#include <tf2_msgs/TFMessage.h>
#include <geometry_msgs/PoseStamped.h>

typedef actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> Server;

using namespace std;

class pixel{
    public:
        bool is_obstical;
        pair<int, int> parents, location; //parent -1 -1: not visented
        double goal_distance;
        double walked_distance, heuristik;
        //neighbours are all eight around

        pixel();
};

class planner{
    public:
        planner(ros::Publisher *prt_path_pub);
        void server_callback(const boost::shared_ptr<const move_base_msgs::MoveBaseGoal> received_goal, Server* as);
        void rviz_server_callback(const boost::shared_ptr<const geometry_msgs::PoseStamped> received_goal);
        void set_map(nav_msgs::OccupancyGrid set_map);

    private:
        nav_msgs::OccupancyGrid map;
        pair<int, int> start, destination;
        nav_msgs::Path path;
        ros::Publisher *path_pup;
        vector<vector<pixel>> grid_map;

        bool plan_path();
        void expand_walls();
        void print_map();
        void calculate_distances();
        bool goal_prereached();
        bool goal_valid();
        bool start_valid();
        bool field_valid(pair<int ,int>field, pair<int ,int>neighbor);
        void reorder_list(vector<pixel> &list);
        bool goal_found(vector<pixel> &list);
        void draw_path();
        void publish_path();
        void clear_map();
};