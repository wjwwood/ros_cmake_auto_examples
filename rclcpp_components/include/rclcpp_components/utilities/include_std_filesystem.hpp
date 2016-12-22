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

#ifndef RCLCPP_COMPONENTS__UTILITIES__INCLUDE_STD_FILESYSTEM_HPP_
#define RCLCPP_COMPONENTS__UTILITIES__INCLUDE_STD_FILESYSTEM_HPP_

#if !defined(__clang__)

#include <experimental/filesystem>

#else  // !defined(__clang__)

// TODO(dirk-thomas) custom implementation until we can use libc++ 3.9
#include <string>
namespace std
{
namespace experimental
{
namespace filesystem
{

class path
{
public:
  explicit path(const std::string & p)
  : path_(p)
  {}
  bool is_absolute()
  {
    return path_[0] == '/';
  }

private:
  std::string path_;
};

}  // namespace filesystem
}  // namespace experimental
}  // namespace std

#endif  // !defined(__clang__)

#endif  // RCLCPP_COMPONENTS__UTILITIES__INCLUDE_STD_FILESYSTEM_HPP_
