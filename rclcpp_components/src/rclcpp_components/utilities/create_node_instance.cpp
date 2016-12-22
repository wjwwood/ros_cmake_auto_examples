// Leave this out of the library for now since it uses rclcpp directly and
// therefore require a version of this library for each rmw impl.

// // Copyright 2016 Open Source Robotics Foundation, Inc.
// //
// // Licensed under the Apache License, Version 2.0 (the "License");
// // you may not use this file except in compliance with the License.
// // You may obtain a copy of the License at
// //
// //     http://www.apache.org/licenses/LICENSE-2.0
// //
// // Unless required by applicable law or agreed to in writing, software
// // distributed under the License is distributed on an "AS IS" BASIS,
// // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// // See the License for the specific language governing permissions and
// // limitations under the License.

// #include "rclcpp_components/utilities/create_node_instance.hpp"

// #include <memory>
// #include <string>
// #include <vector>

// #include "class_loader/class_loader.h"
// #include "rclcpp/rclcpp.hpp"

// #include "rclcpp_components/utilities/get_node_plugins_for_package.hpp"
// // TODO(wjwwood): replace this with #include <experimental/filesystem>
// #include "rclcpp_components/utilities/include_std_filesystem.hpp"
// #include "rclcpp_components/utilities/node_instance.hpp"

// namespace fs = std::experimental::filesystem;
// using rclcpp_components::utilities::get_node_plugins_for_package;

// std::unique_ptr<rclcpp_components::utilities::NodeInstance>
// rclcpp_components::utilities::create_node_instance(
//   const std::string & package_name,
//   const std::string & node_class_name,
//   const std::string & executable_suffix)
// {
//   // get node plugins for package
//   std::string base_path;
//   std::vector<std::pair<std::string, std::string>> node_plugins =
//     get_node_plugins_for_package(package_name, &base_path);

//   // look for the specific node class in the plugins provided by the package
//   std::string plugin_name = node_class_name + executable_suffix;
//   for (const auto & node_plugin_pair : node_plugins) {
//     const std::string & node_plugin_name = node_plugin_pair.first;
//     const std::string & node_plugin_library_path = node_plugin_pair.second;

//     // match plugin name with the same rmw suffix as this executable
//     if (node_plugin_name != plugin_name) {
//       // continue looking if it doesn't match
//       continue;
//     }

//     // make sure the node plugins library path is absolute
//     std::string absolute_library_path = node_plugin_library_path;
//     if (!fs::path(absolute_library_path).is_absolute()) {
//       absolute_library_path = base_path + "/" + absolute_library_path;
//     }
//     // load node plugin library
//     printf("Load library %s\n", absolute_library_path.c_str());
//     auto loader = std::make_shared<class_loader::ClassLoader>(absolute_library_path);
//     // search for the desired node class within the plugin library
//     auto class_names = loader->getAvailableClasses<rclcpp::Node>();
//     for (auto class_name : class_names) {
//       if (node_class_name == class_name) {
//         printf("Instantiate class %s\n", class_name.c_str());
//         auto node = loader->createInstance<rclcpp::Node>(class_name);
//         return std::unique_ptr<NodeInstance>(new NodeInstance({node, loader}));
//       }
//     }

//     // no matching class found in loader
//     throw std::runtime_error(
//       std::string("Failed to find class with the requested plugin name '") +
//       plugin_name + "' in the loaded library");
//   }
//   throw std::runtime_error(
//     std::string("Failed to find plugin name '") +
//     plugin_name + "' in prefix '" + base_path + "'");
// }
