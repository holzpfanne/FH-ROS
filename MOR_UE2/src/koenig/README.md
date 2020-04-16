# Start program

`roslaunch ./{path_to}/run.launch`

# publish soll pose

`rostopic pub -1 /soll geometry_msgs/Pose2D  "0.5" "3.0" "2.1"`