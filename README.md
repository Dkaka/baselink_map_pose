# baselink_map_pose

This ROS package generates nav_msgs::Odometry  message of base_link against map from tf tree. For comparison with the ground truth pose from gazebo.



It is tested under Melodic and the husky robot or simulator.

Run using the command `rosrun baselink_map_pose pose_base_map`

The result topic to be subscribed is `tf_baselink_map`.

### Ground truth pose message from gazebo

One example of generating the ground truth pose of the robot is to use the p3d plugin in gazebo. For instance, by adding the following lines in the .gazebo file or urdf file for the robot:

```xml
<gazebo>
  <plugin name="ground_truth" filename="libgazebo_ros_p3d.so">
    <robotNamespace>$(arg robot_namespace)</robotNamespace>
    <frameName>map</frameName>
    <bodyName>base_link</bodyName>
    <topicName>pose_ground_truth</topicName>
    <updateRate>60.0</updateRate>
  </plugin>
</gazebo>
```

Then the ground truth message will be published at topic `pose_ground_truth`.

## Plot xy coordinates of the robot using PlotJuggler


Load in a ros bag or capture stream from PlotJuggler. Please refer to the  [PlotJuggler-GitHub](https://github.com/facontidavide/PlotJuggler) for installation and basic usage.

Use the right mouse click [PlotJuggler CheatSHeet](https://www.plotjuggler.io/cheatsheet) to load in `pose.psosition.x` and `pose.psosition.y` and other ones as shown below (legends on the top right):

![2](./image/2.png)
