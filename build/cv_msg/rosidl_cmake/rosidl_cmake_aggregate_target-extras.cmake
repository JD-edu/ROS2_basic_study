# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target cv_msg::cv_msg
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${cv_msg_TARGETS}.
if(cv_msg_TARGETS AND NOT TARGET cv_msg::cv_msg)
  add_library(cv_msg::cv_msg INTERFACE IMPORTED)
  set_target_properties(cv_msg::cv_msg PROPERTIES
    INTERFACE_LINK_LIBRARIES "${cv_msg_TARGETS}")
endif()
