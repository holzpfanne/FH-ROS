#include "ros/ros.h"
#include <math.h>
#include "koenig/custom.h"     //Include custom msg
//--------------------------------------//
//--- Function attached to the topic ---//
//--------------------------------------//
void callback( const koenig::custom::ConstPtr& msg ) {         // Function is called when message arrived
    int X, Y;
    X = (msg->radmove * msg->radius) * cos(msg->pos);   //radiant * radius * cos(orientierung) 
    Y = (msg->radmove * msg->radius) * sin(msg->pos);
    ROS_INFO_STREAM( "X: " << X << "/Y: " << Y);
}
int main( int argc, char** argv ) {
    ros::init( argc, argv, "Subscriber" ); // Init node with given parameters and node name
    ros::NodeHandle n( "~" ); // The node handle is used for node startup/shutdown and namespace handling (note: ~ => private node namespace)
    ros::Subscriber sub = n.subscribe( "mytopicSub", // Listen to this topic
                                       1,              // Buffer length is 1
                                       callback );     // Function to be called when message arrives
    ROS_INFO_STREAM( "Init Subscriber complete");                                  
    ros::spin( );                                      // Do a ''main-loop'', which waits for new messages
    return 0;                                          // Everything is fine :)
}