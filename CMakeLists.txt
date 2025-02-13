cmake_minimum_required(VERSION 3.5)
project(rob_nav2)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(plansys2_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(plansys2_domain_expert REQUIRED)
find_package(plansys2_executor REQUIRED)
find_package(plansys2_planner REQUIRED)
find_package(plansys2_problem_expert REQUIRED)
find_package(plansys2_pddl_parser REQUIRED)
find_package(xacro REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(dependencies
    rclcpp
    rclcpp_action
    plansys2_msgs
    nav2_msgs
    plansys2_domain_expert
    plansys2_executor
    plansys2_planner
    plansys2_problem_expert
    plansys2_pddl_parser
)

add_executable(move_action_node src/move_action_node.cpp)
ament_target_dependencies(move_action_node ${dependencies})

add_executable(inspect_action_node src/inspect_action_node.cpp)
ament_target_dependencies(inspect_action_node ${dependencies})

 add_executable(find_lower_action_node src/find_lower_action_node.cpp)
 ament_target_dependencies(find_lower_action_node ${dependencies})

add_executable(planner_controller_node src/planner_controller_node.cpp)
ament_target_dependencies(planner_controller_node ${dependencies})

install(DIRECTORY urdf worlds DESTINATION share/${PROJECT_NAME})

install(DIRECTORY launch pddl params DESTINATION share/${PROJECT_NAME})

install(TARGETS
  move_action_node
  inspect_action_node
  find_lower_action_node
  planner_controller_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
endif()

ament_export_dependencies(${dependencies})

ament_package()
