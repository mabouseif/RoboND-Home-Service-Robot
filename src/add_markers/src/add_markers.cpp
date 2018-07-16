#include <ros/ros.h>
#include <visualization_msgs/Marker.h>


// Some ideas were borrowed from Muthanna A. Attyah


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  // ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();
    marker.type = shape;

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;


    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0.0;
    marker.pose.position.y = 3.0;
    marker.pose.position.z = 1.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Marker published for pick-up..");



    std::string robot_position;
    ros::Rate r(1);

		while (ros::ok())
		{
			if (ros::param::get("/robot_position", robot_position)){
				// ROS_INFO("Robot Position %s", robot_position.c_str());

				if (robot_position=="Picked_Up"){

				    // Set the marker action to DELETE
				    marker.action = visualization_msgs::Marker::DELETE;
				    // Publish the marker
				    marker_pub.publish(marker);
				    ROS_INFO("Arrived at marker at pick-up point");
		                    ros::param::set("/robot_position", "Change_State");

				    // Sleep for 5 sec
				    ros::Duration(5.0).sleep();
				    // Set the drop-off pose of the marker.
				    // This is relative to the frame/time specified above
				    marker.pose.position.x = 1.0;
				    marker.pose.position.y = 0.0;
				    marker.pose.position.z = 1.0;
				    // Set the marker action to ADD.
				    marker.action = visualization_msgs::Marker::ADD;
				    // Publish the marker
				    marker_pub.publish(marker);
				    ROS_INFO("Published marker at drop-off point");

			    	}

				if (robot_position=="Dropped_Off"){


				    ROS_INFO("Arrived at marker at drop-off point");

				    // Sleep for 5 sec
				    ros::Duration(3.0).sleep();
				    marker.action = visualization_msgs::Marker::DELETE;
				    marker_pub.publish(marker);
	
				    }

			}

				if (robot_position=="Dropped_Off") break;
		      
		}

	   ROS_INFO("DONE!!!");
	   r.sleep();
	   break;

  }
    
}
