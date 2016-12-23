This repository contains a prototype of how I (wjwwood) imagine the ROS 2 tutorial code should work.

Repository layout:

- cpp_examples:
  - This folder contains several complete packages which demonstrate basic node's.
  - The packages in this folder would be a template for future tutorials, so they might come to live in ros2/tutorials.
- rclcpp_components:
  - This is single package which provides the "container" (similar to the Nodelet manager from ROS 1), the boiler plate node main, and tools necessary to use them.
  - It would likely come to live in ros2/rclcpp or in its own repository.
- ros_cmake_auto:
  - This is a single package which provides very automated cmake macros to minimize the user's cmake code as much as possible.
  - It provides a function for creating a node, and avoids tedious tasks like finding and using dependencies which are declared in the `package.xml`.
  - It would likely end up living in its own repository under the ros2 GitHub organization.
