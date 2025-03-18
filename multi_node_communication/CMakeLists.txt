cmake_minimum_required(VERSION 3.5)
project(multi_node_communication)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Include C++ directories
include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
  ${std_msgs_INCLUDE_DIRS}
)

# Add executable for each node
add_executable(node1 src/node1.cpp)
add_executable(node2 src/node2.cpp)
add_executable(node3 src/node3.cpp)

# Install executables
install(TARGETS node1 node2 node3
  DESTINATION lib/${PROJECT_NAME})

# Dependencies
ament_target_dependencies(node1 rclcpp std_msgs)
ament_target_dependencies(node2 rclcpp std_msgs)
ament_target_dependencies(node3 rclcpp std_msgs)

# Install launch file
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/)

# Export include directory
ament_export_include_directories(include)
ament_export_libraries(node1 node2 node3)

# Install package
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
