#include <iostream>

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//  Action _server_ example :  https://wiki.ros.org/actionlib_tutorials/Tutorials/SimpleActionServer%28ExecuteCallbackMethod%29
//  Action client example :  https://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
    ros::init(argc, argv, "predefined_nav_goals");

    // ros::NodeHandle nh("~");
    // float param_x, param_y;
    // nh.getParam("x",param_x);
    // nh.getParam("y",param_y);
    // std::cout << "Parameters:  x=" << param_x << ", y=" << param_y << std::endl;


    //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    //wait for the action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }
    ROS_INFO("The move_base action server is up");
    
    move_base_msgs::MoveBaseGoal goal;



    //we'll send a goal to the robot to move RELATIVE TO ITS CURRENT POSE
    /*
    goal.target_pose.header.frame_id = "base_link";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = -2.0;
    goal.target_pose.pose.position.y = 0.5;
    goal.target_pose.pose.orientation.x = 0;
    goal.target_pose.pose.orientation.y = 0;
    goal.target_pose.pose.orientation.z = 0;
    goal.target_pose.pose.orientation.w = 1;
    */

    float x_array[4] = {0 ,-0.5, -1.0, -1.5} ;
    float y_array[4] = {-2 ,0.5, 1.0, 1.5} ;

    for(int ii_ = 0; ii_< 4 ;  ii_++) {           

        //we'll send a goal to the robot to move RELATIVE TO THE MAP
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        goal.target_pose.pose.position.x = x_array[ii_];
        goal.target_pose.pose.position.y = y_array[ii_];
        goal.target_pose.pose.orientation.x = 0;
        goal.target_pose.pose.orientation.y = 0;
        goal.target_pose.pose.orientation.z = 0;
        goal.target_pose.pose.orientation.w = 1;

        ROS_INFO("Sending goal");
        ac.sendGoal(goal);
        ROS_INFO("Sent goal");

        ac.waitForResult();
        ROS_INFO("Got result");

        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
            ROS_INFO("Hooray, the base moved ");
        } else {
            ROS_INFO("The base failed to move for some reason");
            // ac.getResult()
        }
    }



    return 0;
}


