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

#include "rclcpp_components/utilities/get_node_plugins_for_package.hpp"

#include <stdexcept>
#include <string>
#include <vector>

#include "ament_index_cpp/get_resource.hpp"

#include "rclcpp_components/utilities/split.hpp"

std::vector<std::pair<std::string, std::string>>
rclcpp_components::utilities::get_node_plugins_for_package(
  const std::string & package_name,
  std::string * package_prefix)
{
  // get node plugin resource from package
  std::string content;
  std::string base_path;
  if (!ament_index_cpp::get_resource("node_plugin", package_name, content, &base_path)) {
    static const char * msg = "Could not find any 'node_plugins' in the ament index";
    fprintf(stderr, "%s for the package: %s\n", msg, package_name.c_str());
    throw std::runtime_error(msg);
  }

  if (package_prefix) {
    *package_prefix = base_path;
  }

  std::vector<std::pair<std::string, std::string>> result;
  std::vector<std::string> lines = split(content, '\n', true);
  for (const auto & line : lines) {
    std::vector<std::string> parts = rclcpp_components::utilities::split(line, ';');
    if (parts.size() != 2) {
      static const char * msg = "Invalid resource entry";
      fprintf(stderr, "%s: %s\n", msg, line.c_str());
      throw std::runtime_error(msg);
    }

    result.emplace_back(parts[0], parts[1]);
  }

  return result;
}
