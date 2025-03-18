cmake_minimum_required(VERSION 3.5)
project(service_communication)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

# Include C++ directories
include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
  ${example_interfaces_INCLUDE_DIRS}
)

# Define the executable for the service server
add_executable(add_two_ints_server src/add_two_ints_server.cpp)
ament_target_dependencies(add_two_ints_server
  rclcpp
  example_interfaces
)

# Define the executable for the first client
add_executable(add_two_ints_client src/add_two_ints_client.cpp)
ament_target_dependencies(add_two_ints_client
  rclcpp
  example_interfaces
)

# Define the executable for the second client
add_executable(add_two_ints_client2 src/add_two_ints_client2.cpp)
ament_target_dependencies(add_two_ints_client2
  rclcpp
  example_interfaces
)

# Install the executables
install(TARGETS
  add_two_ints_server
  add_two_ints_client
  add_two_ints_client2
  DESTINATION lib/${PROJECT_NAME}
)

# Install package.xml
install(DIRECTORY package.xml
  DESTINATION share/${PROJECT_NAME}/
)

# Install other files
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

# Export dependencies
ament_export_dependencies(rclcpp example_interfaces)

# Install the package manifest
ament_package()