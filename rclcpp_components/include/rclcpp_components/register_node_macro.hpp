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

#ifndef RCLCPP_COMPONENTS__REGISTER_NODE_MACRO_HPP_
#define RCLCPP_COMPONENTS__REGISTER_NODE_MACRO_HPP_

#include "rclcpp/rclcpp.hpp"

#include "class_loader/class_loader_register_macro.h"

#define RCLCPP_REGISTER_NODE(NodeT) CLASS_LOADER_REGISTER_CLASS(NodeT, rclcpp::Node)

#endif  // RCLCPP_COMPONENTS__REGISTER_NODE_MACRO_HPP_
