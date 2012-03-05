// Author: Rob Janssen & the two stooges

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>

#include <amigo_arm_navigation/grasp_precomputeAction.h>

using namespace std;

typedef actionlib::SimpleActionClient<amigo_arm_navigation::grasp_precomputeAction> Client;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "test_grasp");
  Client client("grasp_precompute", true); // true -> don't need ros::spin()
  client.waitForServer();
  amigo_arm_navigation::grasp_precomputeGoal goal;

  ros::Time::waitForValid(ros::WallDuration(2));

  goal.goal.header.stamp=ros::Time::now();
  goal.goal.header.frame_id = "base_link";
  goal.goal.pose.position.x = 0.2;
  goal.goal.pose.position.y = -0.2;
  goal.goal.pose.position.z = 1.0;

  goal.goal.pose.orientation.x = 0;
  goal.goal.pose.orientation.y = 0;
  goal.goal.pose.orientation.z = 0;
  goal.goal.pose.orientation.w = 1;

  client.sendGoal(goal);
  ROS_INFO("Waiting..");
  client.waitForResult(ros::Duration(20));
  ROS_INFO("Done..");
  if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      printf("Grasp precompute successful\n");
  else
	  printf("Grasp precompute unsuccesfull\n");

  return 0;
}
