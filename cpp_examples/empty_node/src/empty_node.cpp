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

class EmptyNode : public rclcpp::Node
{
public:
  EmptyNode() : rclcpp::Node("empty_node") {
    printf("In EmptyNode()!\n");
    /* Your code goes here. */
  }
};

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_REGISTER_NODE(EmptyNode)
