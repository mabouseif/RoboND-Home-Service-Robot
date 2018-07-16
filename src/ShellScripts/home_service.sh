#!/bin/sh

xterm -e "source devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find wall_follower)/world/u_world.world" &
sleep 8
xterm -e "source devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roslaunch turtlebot_navigation amcl_demo.launch map_file:=$(rospack find wall_follower)/map/my_map.yaml" & 
sleep 5
xterm -e "source devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roslaunch turtlebot_rviz_launchers view_navigation.launch" & 
sleep 5
xterm -e "source devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; rosrun add_markers add_markers" &
sleep 5
xterm -e "source devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; rosrun pick_objects pick_objects"


