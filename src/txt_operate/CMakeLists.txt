cmake_minimum_required(VERSION 3.0.2)
project(txt_operate)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  perception_msgs
)

catkin_package(


)


include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)


add_executable(data_record src/data_record.cpp)
target_link_libraries(data_record ${catkin_LIBRARIES})
