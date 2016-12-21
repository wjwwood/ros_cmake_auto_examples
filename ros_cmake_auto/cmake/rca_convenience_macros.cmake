macro(rca_start)
  ros_cmake_auto_start(${ARGN})
endmacro()

macro(rca_add_node)
  ros_cmake_auto_add_node(${ARGN})
endmacro()

macro(rca_end)
  ros_cmake_auto_end(${ARGN})
endmacro()
