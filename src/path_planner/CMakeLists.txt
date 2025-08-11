cmake_minimum_required(VERSION 3.8)
project(path_planner)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(include)
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(include ${OpenCV_INCLUDE_DIRS})

add_executable(map src/map.cpp)
ament_target_dependencies(map
  rclcpp
  nav_msgs
  geometry_msgs
)

install(TARGETS map
  DESTINATION lib/${PROJECT_NAME})

target_include_directories(map PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(map PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_link_libraries(map ${OpenCV_LIBS})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
