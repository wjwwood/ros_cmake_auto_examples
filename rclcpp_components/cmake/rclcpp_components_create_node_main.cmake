# Copyright 2015 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


set(rclcpp_components_node_main_SRC
  "${rclcpp_components_DIR}/../../../src/rclcpp_components/node_main.cpp")

function(rclcpp_components_create_node_main
  node_executable_target_name
  node_library_target
  node_class_name
)
  if(NOT TARGET ${node_library_target})
    message(FATAL_ERROR
      "rclcpp_components_create_node_main() the first argument must be a valid target name")
  endif()
  add_executable(${node_executable_target_name} ${rclcpp_components_node_main_SRC} ${ARGN})
  target_compile_definitions(${node_executable_target_name}
    PRIVATE
      PACKAGE_NAME=${PROJECT_NAME}
      NODE_CLASS_NAME=${node_class_name}
  )
  target_link_libraries(${node_executable_target_name}
    ${node_library_target}
    ${rclcpp_components_LIBRARIES}
  )
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(${node_executable_target_name} "stdc++fs")
  endif()
  install(TARGETS ${node_executable_target_name} DESTINATION bin)
endfunction()
