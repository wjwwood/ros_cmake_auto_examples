find_package(ament_cmake_auto QUIET REQUIRED)

macro(ros_cmake_auto_start)
  cmake_parse_arguments(ARG
    ""
    "CPP_STD"
    "LANGUAGES"
    ${ARGN})
  if(ARG_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "ros_cmake_auto_start(): unknown arguments '${ARG_UNPARSED_ARGUMENTS}'")
  endif()
  # Find dependencies.
  ament_auto_find_build_dependencies()
  # Automatically generate messages.
  ament_auto_generate_code()
  # Do language specific stuff.
  foreach(LANGUAGE IN LISTS ARG_LANGUAGES)
    message(STATUS "ros_cmake_auto_start(): language '${LANGUAGE}'")
    if(
      ${LANGUAGE} STREQUAL "c++" OR
      ${LANGUAGE} STREQUAL "C++" OR
      ${LANGUAGE} STREQUAL "CPP" OR
      ${LANGUAGE} STREQUAL "cpp"
    )
      if(
        ${LANGUAGE} STREQUAL "C++" OR
        ${LANGUAGE} STREQUAL "CPP" OR
        ${LANGUAGE} STREQUAL "cpp"
      )
        message(WARNING "Use 'c++' instead of '${LANGUAGE}' in ros_cmake_auto_start().")
      endif()
      if(NOT ARG_CPP_STD)
        message(FATAL_ERROR "ros_cmake_auto_start(): if using cpp specify a CPP_STD, e.g. c++14")
      endif()
      enable_language(CXX)
      if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=${ARG_CPP_STD}")
        add_compile_options(-Wall -Wextra)
      endif()
    else()  # Language cpp
      if(ARG_CPP_STD)
        message(WARNING "ros_cmake_auto_start(): do not set CPP_STD if not using LANGUAGES cpp.")
      endif()
    endif()  # Language cpp
  endforeach()
endmacro()
