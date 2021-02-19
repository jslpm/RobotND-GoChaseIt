# Project 2 - Go Chase It!

This repo contains the second project of the Robotics Software Engineer Nanodegree Program from Udacity. The program shows a robot which can follow a white ball by analysis of an image from a mounted camera using Gazebo and ROS.

## Dependencies for Running
* cmake >= 3.11
  * Linux: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
* gazebo simulator >= 11.0.0
  * Linux: [gazebo download](http://gazebosim.org/download)
* ROS >= Noetic Ninjemys
  *  Linux: [Ubuntu install of ROS Noetic](http://wiki.ros.org/noetic/Installation/Ubuntu)

## Basic Running Instructions

1. Clone this repo.
2. Open top level directory: `cd RobotND-GoChaseIt/catkin_ws`
3. Execute in terminal: `source devel/setup.bash`
4. In terminal, launch Gazebo simulator and Rviz: `roslaunch my_robot world.launch`
5. In a new terminal, launch `drive_bot` and `process_image`: `roslaunch ball_chaser ball_chaser.launch`
6. Move the white ball in front of the robot to perform following in Gazebo simulator.

## Summary of Tasks

In this project, you should create two ROS packages inside your catkin_ws/src: the drive_bot and the ball_chaser. Here are the steps to design the robot, house it inside your world, and program it to chase white-colored balls:

1. `drive_bot`:
    * Create a `my_robot` ROS package to hold your robot, the white ball, and the world.
    * Design a differential drive robot with the Unified Robot Description Format. Add two sensors to your robot: a lidar and a camera. Add Gazebo plugins for your robot’s differential drive, lidar, and camera. The robot you design should be significantly different from the one presented in the project lesson. Implement significant changes such as adjusting the color, wheel radius, and chassis dimensions.
    * House your robot inside the world you built in the **Build My World** project.
    * Add a white-colored ball to your Gazebo world and save a new copy of this world.
    * The `world.launch` file should launch your world with the white-colored ball and your robot.

 2. `ball_chaser`:
    * Create a `ball_chaser` ROS package to hold your C++ nodes.
    * Write a `drive_bot` C++ node that will provide a `ball_chaser/command_robot` service to drive the robot by controlling its linear x and angular z velocities. The service should publish to the wheel joints and return back the requested velocities.
    * Write a `process_image` C++ node that reads your robot’s camera image, analyzes it to determine the presence and position of a white ball. If a white ball exists in the image, your node should request a service via a client to drive the robot towards it.
    * The `ball_chaser.launch` should run both the `drive_bot` and the `process_image nodes`.

