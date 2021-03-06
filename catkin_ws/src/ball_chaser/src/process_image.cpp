#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;
bool ball_found = false;
enum class direction{left, forward, right, stop};
direction robot_dir = direction::stop;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv))
      ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
  int white_pixel = 255;
    
  // TODO: Loop through each pixel in the image and check if there's a bright white one
  // Then, identify if this pixel falls in the left, mid, or right side of the image
  // Depending on the white ball position, call the drive_bot function and pass velocities to it
  // Request a stop when there's no white ball seen by the camera
  ball_found = false;
  robot_dir = direction::stop;
  int one_third_image = img.width / 3;
  int two_thirds_image = 2 * img.width / 3;

  for (int h = 0; h < img.height; h++) 
  {
    for(int w = 0; w < img.width; w++)
    {
      if (img.data[3*w+h*img.step] == white_pixel && 
          img.data[3*w+h*img.step+1] == white_pixel && 
          img.data[3*w+h*img.step+2] == white_pixel)
      {
        ball_found = true;

        if (w < one_third_image)
          robot_dir = direction::left;
        else if (w < two_thirds_image)
          robot_dir = direction::forward;
        else
          robot_dir = direction::right;
      }
    }
  }

  if (ball_found == true)
  {
    switch (robot_dir)
    {
    case direction::left:
      drive_robot(0.0, 0.5);
      break;
    case direction::right:
      drive_robot(0.0, -0.5);
      break;
    case direction::forward:
      drive_robot(0.5, 0.0); 
      break;
    }
  }
  else
  {
    drive_robot(0.0, 0.0);    
  }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the
    // process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
