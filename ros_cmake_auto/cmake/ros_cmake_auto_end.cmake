find_package(ament_cmake_auto QUIET REQUIRED)

macro(ros_cmake_auto_end)
  ament_auto_package(${ARGN})
endmacro()
