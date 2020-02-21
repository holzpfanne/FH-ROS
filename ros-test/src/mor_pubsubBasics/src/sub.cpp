#include "ros/ros.h"
#include "std_msgs/String.h"
//--------------------------------------//
//--- Function attached to the topic ---//
//--------------------------------------//
void callback( const std_msgs::String::ConstPtr& msg ) {         // Function is called when message arrived
    ROS_INFO_STREAM( "Message arrived:" << msg->data.c_str( ) ); // Just plot the message arrived
}
int main( int argc, char** argv ) {
    ros::init( argc, argv, "MOR_Subscriber" ); // Init node with given parameters and node name
    ros::NodeHandle n( "~" ); // The node handle is used for node startup/shutdown and namespace handling (note: ~ => private node namespace)
    ros::Subscriber sub = n.subscribe( "/MOR_Publisher/MOR_Chatter", // Listen to this topic
                                       1,              // Buffer length is 1
                                       callback );     // Function to be called when message arrives
    ROS_INFO_STREAM( "Init complete");                                  
    ros::spin( );                                      // Do a ''main-loop'', which waits for new messages
    return 0;                                          // Everything is fine :)
}