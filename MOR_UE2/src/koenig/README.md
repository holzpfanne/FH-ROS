### Start program

`roslaunch ./{path_to}/run.launch`

### publish soll pose

`rostopic pub -1 /soll geometry_msgs/Pose2D  "X" "Y" "theta"`

where `"X"` has to be replaced by the target X coordinates
where `"Y"` has to be replaced by the target Y coordinates
where `"theta"` has to be replaced by the target orientation in radian
