#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  ros::param::set("/robot_position", "Start_Point");

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  
  move_base_msgs::MoveBaseGoal goal_pick_up;

  // set up the frame parameters
  goal_pick_up.target_pose.header.frame_id = "map";
  goal_pick_up.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal_pick_up.target_pose.pose.position.x = 0.0;
  goal_pick_up.target_pose.pose.position.y = 3.0;
  goal_pick_up.target_pose.pose.orientation.w = 1.0;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Attempting pick up...");

  ac.sendGoal(goal_pick_up);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Successfully reached pick up zone");
    ros::param::set("/robot_position", "Picked_Up");
  }
  else
  {
    ROS_INFO("Failed to reach pick up zone");
  }



  ROS_INFO("Waiting ...");
  ros::Duration(5.0).sleep();
  ROS_INFO("Waited for 5 seconds.");




  move_base_msgs::MoveBaseGoal goal_drop_off;

  // set up the frame parameters
  goal_drop_off.target_pose.header.frame_id = "map";
  goal_drop_off.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal_drop_off.target_pose.pose.position.x = 1.0;
  goal_drop_off.target_pose.pose.position.y = 0.0;
  goal_drop_off.target_pose.pose.orientation.w = 1.0;



   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Attempting drop off...");
  ac.sendGoal(goal_drop_off);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Successfully reached drop off zone");
    ros::param::set("/robot_position", "Dropped_Off");
  }
  else
  {
    ROS_INFO("Failed to reach drop off zone");
  }

  return 0;
}
