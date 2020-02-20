#include "ros/ros.h"                //ROS includes
#include "std_msgs/String.h"        //Include for chosen message (a string)
int main( int argc, char** argv ) { // Note, Wen need argc and argv for node initialization
    //---------------------//
    //--- Init ROS node ---//
    //---------------------//
    ros::init( argc, argv, "MOR_Publisher" ); // Init Node with given parameters (e.g.: arguments)
    ros::NodeHandle n( "~" ); // The node handle is used for node startup/shutdown and namespace
                              // handling (note: ~ => private node namespace)
    //----------------------//
    //--- Create a topic ---//
    //----------------------//
    ros::Publisher chatter_pub = n.advertise< std_msgs::String >(
        "MOR_Chatter", 1 );    // Create a topic with message=string, the bufferlength is 1
    int cnt = 0;
    
    ros::Rate loop_rate( 10 ); // Spin with this rate
    std_msgs::String msg;      // Define a message to send
    ROS_INFO_STREAM( "Init complete"); 

    while( ros::ok( ) ) {      // Do till ROS error occurs (e.g.: strg+C or ROS shutdown signal)
        msg.data = "My first message " + std::to_string(cnt); // Fill message
        chatter_pub.publish( msg );    // Send message
        ros::spinOnce( );              // Update buffer
        loop_rate.sleep( );
        cnt++;          // Sleep with given frequency
    }
    return 0; // Everything is fine :)
}