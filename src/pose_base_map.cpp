#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "my_tf2_listener");

  ros::NodeHandle node;

  //   ros::service::waitForService("spawn");
  //   ros::ServiceClient spawner =
  //     node.serviceClient<turtlesim::Spawn>("spawn");
  //   turtlesim::Spawn turtle;
  //   turtle.request.x = 4;
  //   turtle.request.y = 2;
  //   turtle.request.theta = 0;
  //   turtle.request.name = "turtle2";
  //   spawner.call(turtle);

  ros::Publisher tf_baselink_map =
      node.advertise<nav_msgs::Odometry>("tf_baselink_map", 100);

  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  ros::Rate rate(60.0);
  while (node.ok())
  {
    geometry_msgs::TransformStamped transformStamped;
    try
    {
      transformStamped = tfBuffer.lookupTransform("map", "base_link",
                                                  ros::Time(0));
    }
    catch (tf2::TransformException &ex)
    {
      ROS_WARN("%s", ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }

    // geometry_msgs::Twist vel_msg;
    // geometry_msgs::Pose;
    nav_msgs::Odometry odom;

    odom.pose.pose.position.x = transformStamped.transform.translation.x;
    odom.pose.pose.position.y = transformStamped.transform.translation.y;
    odom.pose.pose.position.z = transformStamped.transform.translation.z;

    odom.pose.pose.orientation.x = transformStamped.transform.rotation.x;
    odom.pose.pose.orientation.y = transformStamped.transform.rotation.y;
    odom.pose.pose.orientation.z = transformStamped.transform.rotation.z;
    odom.pose.pose.orientation.w = transformStamped.transform.rotation.w;

    ros::Time now = ros::Time::now();

    odom.header.frame_id = "map";

    odom.child_frame_id = "base_link";
    odom.header.stamp.sec = now.sec;
    odom.header.stamp.nsec = now.nsec;
    // odom.pose.orientation.x y z w

    // vel_msg.angular.z = 4.0 * atan2(transformStamped.transform.translation.y,
    //                                 transformStamped.transform.translation.x);
    // vel_msg.linear.x = 0.5 * sqrt(pow(transformStamped.transform.translation.x, 2) +
    //                               pow(transformStamped.transform.translation.y, 2));
    tf_baselink_map.publish(odom);

    rate.sleep();
  }
  return 0;
};
