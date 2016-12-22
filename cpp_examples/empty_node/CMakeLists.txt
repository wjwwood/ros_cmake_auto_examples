cmake_minimum_required(VERSION 3.5)
project(examples_empty_node)

find_package(ros_cmake_auto REQUIRED)
ros_cmake_auto_alias_to_rca()

rca_start(LANGUAGES c++ CPP_STD c++14)

rca_add_node(empty_node CLASS_NAME EmptyNode src/empty_node.cpp)

rca_end()
