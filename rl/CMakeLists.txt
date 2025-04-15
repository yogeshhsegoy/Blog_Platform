cmake_minimum_required(VERSION 3.8)
project(rl_maze_sim)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)

install(
  DIRECTORY launch scripts
  DESTINATION share/${PROJECT_NAME}/
)

install(
  FILES trained_dqn_model.pth
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_EXCLUDE "trained_dqn_model.pth")
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()