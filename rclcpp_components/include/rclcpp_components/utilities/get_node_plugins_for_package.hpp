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

#ifndef RCLCPP_COMPONENTS__UTILITIES__GET_NODE_PLUGINS_FOR_PACKAGE_HPP_
#define RCLCPP_COMPONENTS__UTILITIES__GET_NODE_PLUGINS_FOR_PACKAGE_HPP_

#include <string>
#include <vector>

namespace rclcpp_components
{
namespace utilities
{

std::vector<std::pair<std::string, std::string>>
get_node_plugins_for_package(
  const std::string & package_name,
  std::string * package_prefix = nullptr);

}  // namespace utilities
}  // namespace rclcpp_components

#endif  // RCLCPP_COMPONENTS__UTILITIES__GET_NODE_PLUGINS_FOR_PACKAGE_HPP_
