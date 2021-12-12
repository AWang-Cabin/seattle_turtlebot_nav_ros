cmake_minimum_required(VERSION 3.10.2)
project(seattle_gazebo)

find_package(catkin REQUIRED
    COMPONENTS
        roscpp
        message_generation
        std_msgs
        geometry_msgs
        nav_msgs
        )

find_package(lcm REQUIRED)


generate_messages(DEPENDENCIES std_msgs geometry_msgs)

catkin_package(
    CATKIN_DEPENDS
      roscpp
      message_runtime
      std_msgs
      geometry_msgs
        nav_msgs
)

include_directories(
        "include/"
         ${catkin_INCLUDE_DIRS}
)

add_executable(goalPublisher src/goalPublisher.cpp)
target_link_libraries(goalPublisher ${catkin_LIBRARIES} lcm)

add_executable(roboStatePublisher src/roboStatePublisher.cpp)
target_link_libraries(roboStatePublisher ${catkin_LIBRARIES} lcm)

