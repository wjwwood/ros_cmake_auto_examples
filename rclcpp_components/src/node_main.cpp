// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/utilities/create_node_instance.hpp"

#ifndef PACKAGE_NAME
#error "PACKAGE_NAME must be defined"
#endif
#ifndef NODE_CLASS_NAME
#error "NODE_CLASS_NAME must be defined"
#endif
#ifndef RMW_IMPLEMENTATION_SUFFIX
#define RMW_IMPLEMENTATION_SUFFIX
#endif

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

const char * package_name = STRINGIFY(PACKAGE_NAME);
const char * node_class_name = STRINGIFY(NODE_CLASS_NAME);
const char * executable_suffix = STRINGIFY(RMW_IMPLEMENTATION_SUFFIX);

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exec;

  auto node_instance = rclcpp_components::utilities::create_node_instance(
    package_name, node_class_name, executable_suffix);
  exec.add_node(node_instance->node);
  exec.spin();
  return 0;
}
