find_package(rclcpp_components QUIET REQUIRED)

macro(ros_cmake_auto_add_node target_name)
  cmake_parse_arguments(ARG
    "EXCLUDE_FROM_ALL;NO_TARGET_LINK_LIBRARIES"
    "CLASS_NAME;NODE_LIBRARY_TARGET_NAME"
    ""
    ${ARGN})
  if(ARG_EXCLUDE_FROM_ALL)
    set(ros_cmake_auto_add_node_EXCLUDE_FROM_ALL "EXCLUDE_FROM_ALL")
  else()
    set(ros_cmake_auto_add_node_EXCLUDE_FROM_ALL "")
  endif()
  if(ARG_NO_TARGET_LINK_LIBRARIES)
    set(ros_cmake_auto_add_node_NO_TARGET_LINK_LIBRARIES "NO_TARGET_LINK_LIBRARIES")
  else()
    set(ros_cmake_auto_add_node_NO_TARGET_LINK_LIBRARIES "")
  endif()
  if(NOT ARG_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "ros_cmake_auto_add_library() called without any source files")
  endif()
  if(NOT ARG_NODE_LIBRARY_TARGET_NAME)
    set(ARG_NODE_LIBRARY_TARGET_NAME ${target_name}_nodeplugin)
  endif()
  if(NOT ARG_CLASS_NAME)
    message(FATAL_ERROR "ros_cmake_auto_add_node() called without CLASS_NAME set")
  endif()
  ament_auto_add_library(${ARG_NODE_LIBRARY_TARGET_NAME} SHARED
    ${ARG_UNPARSED_ARGUMENTS}
    ${ros_cmake_auto_add_node_EXCLUDE_FROM_ALL}
    ${ros_cmake_auto_add_node_NO_TARGET_LINK_LIBRARIES})
  rclcpp_register_node_plugins(${ARG_NODE_LIBRARY_TARGET_NAME} ${ARG_CLASS_NAME})
  rclcpp_components_create_node_main(${target_name}
    ${ARG_NODE_LIBRARY_TARGET_NAME}
    ${ros_cmake_auto_add_node_EXCLUDE_FROM_ALL})
endmacro()
