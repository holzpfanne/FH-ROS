#!/bin/bash

#run core
roscore&

sleep 10

#run publisher
rosrun koenig Publisher&

#run subscriber
rosrun koenig Subscriber /Subscriber/mytopicSub:=/Publisher/mytopicPub

#---------------------------#
#--- Warten auf strg. +C ---#
#---------------------------#
nodes=$(rosnode list)		#Wir holen uns den Namen aller ROS nodes
for i in $nodes				#Wir loopen über diese Namen
do 
	rosnode kill $i > /dev/null	#Kill node und verhindere Nachricht am Bildschirm
done