cmake_minimum_required(VERSION 3.5)
project(ros_cmake_auto NONE)

find_package(ament_cmake REQUIRED)

ament_package(
  CONFIG_EXTRAS "ros_cmake_auto-extras.cmake"
)

install(
  DIRECTORY cmake
  DESTINATION share/${PROJECT_NAME}
)

