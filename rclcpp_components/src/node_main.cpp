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

#include <chrono>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/srv/load_node_component.hpp"
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

using namespace std::literals;

void print_usage()
{
  fprintf(stderr, "Usage: <executable> [-r|--remote[-container] <remote container node name>]\n");
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  if (argc == 3) {
    if (
      "-r"s != argv[1] &&
      "--remote"s != argv[1] &&
      "--remote-container"s != argv[1])
    {
      fprintf(stderr, "Unknown argument '%s', expected '--remote' or similar option.\n", argv[1]);
      print_usage();
      return 1;
    }
    auto launcher_node =
      std::make_shared<rclcpp::Node>(package_name + "__"s + node_class_name + "__launcher"s);
    using rclcpp_components::srv::LoadNodeComponent;
    std::string service_name = argv[2] + "__load_node_component"s;
    auto client = launcher_node->create_client<LoadNodeComponent>(service_name);

    while (!client->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        printf("Interrupted while waiting for the '%s' service to become available. Exiting.\n",
          service_name.c_str());
        return 0;
      }
      printf("'%s' service not available after 1 second, waiting again...\n",
        service_name.c_str());
    }

    auto request = std::make_shared<LoadNodeComponent::Request>();
    request->package_name = package_name;
    request->node_class_name = node_class_name;
    printf("Launching node component '%s/%s' in remote container '%s'...\n",
      package_name, node_class_name, argv[2]);
    auto future = client->async_send_request(request);
    if (rclcpp::spin_until_future_complete(launcher_node, future) !=
      rclcpp::executor::FutureReturnCode::SUCCESS)
    {
      fprintf(stderr, "Interrupted while waiting on launch response. Exiting.\n");
      return 1;
    }
    printf("Loading was %s\n", future.get()->success ? "successful" : "unsuccessful");
  } else if (argc == 1) {
    rclcpp::executors::SingleThreadedExecutor exec;

    auto node_instance = rclcpp_components::utilities::create_node_instance(
      package_name, node_class_name, executable_suffix);
    exec.add_node(node_instance->node);
    exec.spin();
  } else {
    fprintf(stderr, "unknown number of arguments, should be either 0 or 2\n");
    print_usage();
    return 1;
  }

  return 0;
}
