#pragma once

#include <QVariant>
#include "ParserUtils.h"

#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_with_covariance.hpp"
#include "geometry_msgs/msg/quaternion.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/twist_with_covariance.hpp"

namespace RosMessageParser{
using namespace ParseUtils;

namespace Point {
//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Point.html

inline QVariantMap toVariantMap(const geometry_msgs::msg::Point& msg){
    QVariantMap map;
    map.insert("x", msg.x);
    map.insert("y", msg.y);
    map.insert("z", msg.z);
    return map;
}

inline geometry_msgs::msg::Point toMessage(const QVariantMap& map){
    geometry_msgs::msg::Point msg;
    msg.x = toDouble("x", map);
    msg.y = toDouble("y", map);
    msg.z = toDouble("z", map);
    return msg;
}
}

namespace Vector3{
//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Vector3.html

inline QVariantMap toVariantMap(const geometry_msgs::msg::Vector3& msg){
    QVariantMap map;
    map.insert("x", msg.x);
    map.insert("y", msg.y);
    map.insert("z", msg.z);
    return map;
}

inline geometry_msgs::msg::Vector3 toMessage(const QVariantMap& map){
    geometry_msgs::msg::Vector3 msg;
    msg.x = toDouble("x", map);
    msg.y = toDouble("y", map);
    msg.z = toDouble("z", map);
    return msg;
}
}

namespace Quaternion{
//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Quaternion.html

inline QVariantMap toVariantMap(const geometry_msgs::msg::Quaternion& msg){
    QVariantMap map;
    map.insert("x", msg.x);
    map.insert("y", msg.y);
    map.insert("z", msg.z);
    map.insert("w", msg.w);
    return map;
}

inline geometry_msgs::msg::Quaternion toMessage(const QVariantMap& map){
    geometry_msgs::msg::Quaternion msg;
    msg.x = toDouble("x", map);
    msg.y = toDouble("y", map);
    msg.z = toDouble("z", map);
    msg.w = toDouble("w", map);
    return msg;
}
}

namespace Pose {
//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Pose.html

inline QVariantMap toVariantMap(const geometry_msgs::msg::Pose& msg){
    QVariantMap map;
    map.insert("position", Point::toVariantMap(msg.position));
    map.insert("orientation", Quaternion::toVariantMap(msg.orientation));
    return map;
}

inline geometry_msgs::msg::Pose toMessage(const QVariantMap& map){
    geometry_msgs::msg::Pose msg;
    msg.position =  Point::toMessage(map["twist"].toMap());
    msg.orientation = Quaternion::toMessage(map["covariance"].toMap());
    return msg;
}
}

namespace PoseWithCovariance {
//https://docs.ros2.org/foxy/api/geometry_msgs/msg/PoseWithCovariance.html

inline QVariantMap toVariantMap(const geometry_msgs::msg::PoseWithCovariance& msg){
    QVariantMap map;
    map.insert("pose", Pose::toVariantMap(msg.pose));
    map.insert("covariance", toVariant<double, 36>(msg.covariance));
    return map;
}

inline geometry_msgs::msg::PoseWithCovariance toMessage(const QVariantMap& map){
    geometry_msgs::msg::PoseWithCovariance msg;
    msg.pose =  Pose::toMessage(map["pose"].toMap());
    msg.covariance = toArray<double,36>("covariance", map);
    return msg;
}
}

namespace Twist{
//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Twist.html

inline QVariantMap toVariantMap(const geometry_msgs::msg::Twist& msg){
    QVariantMap map;
    map.insert("linear", Vector3::toVariantMap(msg.linear));
    map.insert("angular", Vector3::toVariantMap(msg.angular));
    return map;
}

inline geometry_msgs::msg::Twist toMessage(const QVariantMap& map){
    geometry_msgs::msg::Twist msg;
    msg.linear =  Vector3::toMessage(map["linear"].toMap());
    msg.angular = Vector3::toMessage(map["angular"].toMap());
    return msg;
}
}

namespace TwistWithCovariance {
//https://docs.ros2.org/foxy/api/geometry_msgs/msg/TwistWithCovariance.html

inline QVariantMap toVariantMap(const geometry_msgs::msg::TwistWithCovariance& msg){
    QVariantMap map;
    map.insert("twist", Twist::toVariantMap(msg.twist));
    map.insert("covariance", toVariant<double, 36>(msg.covariance));
    return map;
}

inline geometry_msgs::msg::TwistWithCovariance toMessage(const QVariantMap& map){
    geometry_msgs::msg::TwistWithCovariance msg;
    msg.twist =  Twist::toMessage(map["twist"].toMap());
    msg.covariance = toArray<double,36>("covariance", map);
    return msg;
}
}

}
