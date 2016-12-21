cmake_minimum_required(VERSION 3.5)

project(rclcpp_components)

find_package(ament_cmake REQUIRED)
find_package(class_loader REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(rclcpp REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14")
  add_compile_options(-Wall -Wextra)
endif()

include_directories(include)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/LoadNodeComponent.srv"
)

macro(target)
  if(NOT target_suffix STREQUAL "")
    get_rclcpp_information("${rmw_implementation}" "rclcpp${target_suffix}")
  endif()
  add_library(rclcpp_component_container${target_suffix} src/rclcpp_component_container.cpp)
  ament_target_dependencies(${PROJECT_NAME}${target_suffix}
    "class_loader"
    "rclcpp${target_suffix}"
  )

  install(
    TARGETS rclcpp_component_container${target_suffix}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )
endmacro()

call_for_each_rmw_implementation(target GENERATE_DEFAULT)

ament_export_dependencies(ament_cmake)
ament_export_dependencies(class_loader)
ament_export_dependencies(rclcpp)

ament_export_include_directories(include)

ament_package(
  CONFIG_EXTRAS rclcpp-extras.cmake
)

# install(
#   DIRECTORY cmake
#   DESTINATION share/${PROJECT_NAME}
# )

# install(
#   DIRECTORY include/
#   DESTINATION include
# )

# install(
#   FILES src/rclcpp/node_main.cpp
#   DESTINATION src/rclcpp
# )
