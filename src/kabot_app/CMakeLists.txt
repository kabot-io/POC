cmake_minimum_required(VERSION 3.5)
project(kabot_app)

set (CMAKE_CXX_STANDARD 17)
if(NOT WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -fPIC")
endif()

IF (NOT DEFINED BUILD_VERSION)
	SET(BUILD_VERSION "not set")
ENDIF()
ADD_DEFINITIONS(-DBUILD_VERSION="${BUILD_VERSION}")

find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rmw_implementation REQUIRED)
find_package(rosidl_generator_cpp REQUIRED)
find_package(rosidl_typesupport_cpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)

find_package(Qt5 COMPONENTS Widgets WebSockets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (QML_DIRS "")
list(APPEND QML_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/qml/)
set(QML_IMPORT_PATH ${QML_DIRS} CACHE STRING "Qt Creator extra qml import paths" FORCE)

include_directories(
    ${rclcpp_INCLUDE_DIRS}
    ${std_msgs_INCLUDE_DIRS}
    ${geometry_msgs_INCLUDE_DIRS}
    ${nav2_msgs_INCLUDE_DIRS}
    ${sensor_msgs_INCLUDE_DIRS}
    ${trajectory_msgs_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Quick_INCLUDE_DIRS}
    ${Qt5WebSockets}
    "src/"
    "src/ros2/"
    "src/ros2/msg_parsers/"
    "src/ros2/topic_handlers/"
    "src/ros2/topic_handlers/builtin_interfaces"
    "src/ros2/topic_handlers/geometry_msgs"
    "src/ros2/topic_handlers/nav_msgs"
    "src/ros2/topic_handlers/rcl_interfaces"
    "src/ros2/topic_handlers/sensors_msgs"
    "src/ros2/topic_handlers/std_msgs"
    "src/ros2/topic_handlers/trajectory_msgs"
)

file(GLOB SOURCE_FILES
    "src/*.cpp"
    "src/*.h"
    "src/qml/cpp_backends/*.cpp"
    "src/qml/cpp_backends/*.h"
    "src/ros2/*.cpp"
    "src/ros2/*.h"
    "src/ros2/msg_parsers/*.cpp"
    "src/ros2/msg_parsers/*.h"
    "src/ros2/topic_handlers/*.cpp"
    "src/ros2/topic_handlers/*.h"
    "src/ros2/topic_handlers/builtin_interfaces/*.cpp"
    "src/ros2/topic_handlers/builtin_interfaces/*.h"
    "src/ros2/topic_handlers/geometry_msgs/*.cpp"
    "src/ros2/topic_handlers/geometry_msgs/*.h"
    "src/ros2/topic_handlers/nav_msgs/*.cpp"
    "src/ros2/topic_handlers/nav_msgs/*.h"
    "src/ros2/topic_handlers/rcl_interfaces/*.cpp"
    "src/ros2/topic_handlers/rcl_interfaces/*.h"
    "src/ros2/topic_handlers/sensor_msgs/*.cpp"
    "src/ros2/topic_handlers/sensor_msgs/*.h"
    "src/ros2/topic_handlers/std_msgs/*.cpp"
    "src/ros2/topic_handlers/std_msgs/*.h"
    "src/ros2/topic_handlers/trajectory_msgs/*.cpp"
    "src/ros2/topic_handlers/trajectory_msgs/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} "src/main.qrc" "src/qml/qml.qrc")

ament_target_dependencies(${PROJECT_NAME}
    geometry_msgs
    nav2_msgs
    rclcpp
    rmw_implementation
    rosidl_typesupport_cpp
    sensor_msgs
    std_msgs
    trajectory_msgs
    rosidl_generator_cpp
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
    Qt5::WebSockets
    Qt5::Widgets
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})
#install(TARGETS ${PROJECT_NAME} DESTINATION bin)

ament_package()
