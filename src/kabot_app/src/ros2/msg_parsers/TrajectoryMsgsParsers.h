#pragma once

#include <QVariant>
#include "ParserUtils.h"

#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"

#include "BuiltinInterfacesParsers.h"
#include "StdMsgsParsers.h"

namespace RosMessageParser{
using namespace ParseUtils;

namespace JointTrajectoryPoint{
//http://docs.ros.org/en/lunar/api/trajectory_msgs/html/msg/JointTrajectoryPoint.html

inline QVariantMap toVariantMap(const trajectory_msgs::msg::JointTrajectoryPoint& msg){
    QVariantMap map;
    map.insert("positions", toVariant<double>(msg.positions));
    map.insert("velocities", toVariant<double>(msg.velocities));
    map.insert("accelerations", toVariant<double>(msg.accelerations));
    map.insert("effort", toVariant<double>(msg.effort));
    map.insert("time_from_start", RosMessageParser::Duration::toVariantMap(msg.time_from_start));
    return map;
}

inline trajectory_msgs::msg::JointTrajectoryPoint toMessage(const QVariantMap& map){
    trajectory_msgs::msg::JointTrajectoryPoint msg;
    msg.positions = toVector<double>("positions", map);
    msg.velocities = toVector<double>("velocities", map);
    msg.accelerations = toVector<double>("accelerations", map);
    msg.effort = toVector<double>("effort", map);
    msg.time_from_start = RosMessageParser::Duration::toMessage(map);
    return msg;
}
}

namespace JointTrajectory{

inline QVariantMap toVariantMap(const trajectory_msgs::msg::JointTrajectory& msg){
    QVariantMap map;
    map.insert("header", Header::toVariantMap(msg.header));
//    map.insert(toVariant<QString>("joint_names", msg.joint_names));

//    map.insert(toVariant<trajectory_msgs::msg::JointTrajectoryPoint>("points", map, JointTrajectoryPoint::toVariantMap));

    return map;
}

//std_msgs/Header header
//string[] joint_names
//trajectory_msgs/JointTrajectoryPoint[] points

inline trajectory_msgs::msg::JointTrajectory toMessage(const QVariantMap& map){
    trajectory_msgs::msg::JointTrajectory msg;
    msg.header = Header::toMessage(map);
//    msg.joint_names = toVector<std::string>("joint_names", map);

//    msg.points = toVector<trajectory_msgs::msg::JointTrajectoryPoint>();
    return msg;
}
}
}
