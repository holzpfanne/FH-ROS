#include "ros/ros.h"                //ROS includes  
#include "koenig/custom.h"     //Include custom msg
int main( int argc, char** argv ) { // Note, Wen need argc and argv for node initialization
    //---------------------//
    //--- Init ROS node ---//
    //---------------------//
    ros::init( argc, argv, "Publisher" ); // Init Node with given parameters (e.g.: arguments)
    ros::NodeHandle n( "~" ); // The node handle is used for node startup/shutdown and namespace
                              // handling (note: ~ => private node namespace)

    ros::Publisher chatter_pub = n.advertise< koenig::custom >(
                                    "mytopicPub", 1 );    // Create a topic with message=custom msg, the bufferlength is 1
    
    ros::Rate loop_rate( 10 ); // Spin with this rate

    //create and init msg data
    koenig::custom msg;
    msg.pos = 0.5;
    msg.radius = 5;
    msg.radmove = 1;
    ROS_INFO_STREAM( "Init Publisher complete"); 

    while( ros::ok( ) ) {      // Do till ROS error occurs (e.g.: strg+C or ROS shutdown signal)
        chatter_pub.publish( msg );    // Send message
        ros::spinOnce( );              // Update buffer
        loop_rate.sleep( );            // Sleep with given frequency
        msg.radmove++;                 //move robot
    }
    return 0; // Everything is fine :)
}