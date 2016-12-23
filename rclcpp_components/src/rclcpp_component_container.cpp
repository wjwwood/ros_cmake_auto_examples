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

#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/srv/load_node_component.hpp"
#include "rclcpp_components/utilities/create_node_instance.hpp"

using rclcpp_components::utilities::create_node_instance;

#ifdef RMW_IMPLEMENTATION_SUFFIX
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)
#else
#define STRINGIFY(s) ""
#endif
const char * executable_suffix = STRINGIFY(RMW_IMPLEMENTATION_SUFFIX);

using namespace std::string_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  if (argc != 3) {
    fprintf(stderr,
      "incorrect number of arguments, usage: 'rclcpp_component_container --name <name>'\n");
    return 1;
  }
  if ("-n"s != argv[1] && "--name"s != argv[1]) {
    fprintf(stderr,
      "expected '-n' or '--name' as the second argument, got '%s'\n", argv[1]);
    return 1;
  }

  auto node = rclcpp::Node::make_shared("node_component_container");

  rclcpp::executors::SingleThreadedExecutor exec;
  exec.add_node(node);

  std::vector<std::unique_ptr<rclcpp_components::utilities::NodeInstance>> node_instances;

  std::string service_name = argv[2] + "__load_node_component"s;
  auto server = node->create_service<rclcpp_components::srv::LoadNodeComponent>(
    service_name,
    [&exec, &node_instances](
      const std::shared_ptr<rmw_request_id_t>,
      const std::shared_ptr<rclcpp_components::srv::LoadNodeComponent::Request> request,
      std::shared_ptr<rclcpp_components::srv::LoadNodeComponent::Response> response)
  {
    try {
      auto node_instance =
        create_node_instance(request->package_name, request->node_class_name, executable_suffix);
      exec.add_node(node_instance->node);
      node_instances.emplace_back(std::move(node_instance));
    } catch (const std::exception & ex) {
      fprintf(stderr,
        "Failed to load node component '%s/%s': %s\n",
        request->package_name.c_str(), request->node_class_name.c_str(), ex.what());
      response->success = false;
      return;
    } catch (...) {
      fprintf(stderr,
        "Failed to load node component '%s/%s': Unknown exception\n",
        request->package_name.c_str(), request->node_class_name.c_str());
      response->success = false;
      return;
    }
    response->success = true;
  });

  exec.spin();

  for (auto & node_instance : node_instances) {
    exec.remove_node(node_instance->node);
  }
  node_instances.clear();
  return 0;
}
