#pragma once

#include <QVariant>

#include "ParserUtils.h"

#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

#include "GeometryMsgsParsers.h"
#include "SensorMsgsParsers.h"
#include "StdMsgsParsers.h"

namespace RosMessageParser{
using namespace ParseUtils;

namespace Image{
//https://docs.ros2.org/foxy/api/sensor_msgs/msg/Image.html

inline QVariantMap toVariantMap(const sensor_msgs::msg::Image& msg){
    QVariantMap map;
    map.insert("header", Header::toVariantMap(msg.header));
    map.insert("height", toVariant(msg.height));
    map.insert("width", toVariant(msg.width));
    map.insert("encoding", toVariant(msg.encoding));
    map.insert("is_bigedian", toVariant(msg.is_bigendian));
    map.insert("step", toVariant(msg.step));
    map.insert("data", "web socket server not connected");
    return map;
}

inline sensor_msgs::msg::Image toMessage(const QVariantMap& map){
    sensor_msgs::msg::Image msg;
    msg.header = Header::toMessage(map["header"].toMap());
    msg.height = toUint32("height", map);
    msg.width = toUint32("width", map);
    msg.encoding = toString("encoding", map);
    msg.is_bigendian = toUint8("is_bigedian", map);
    msg.step = toUint32("step", map);
    msg.data = toVector<uint8_t>("data", map);
    return msg;
}
}

namespace  Imu{
//https://docs.ros2.org/foxy/api/sensor_msgs/msg/Imu.html

inline QVariantMap toVariantMap(const sensor_msgs::msg::Imu& msg){
    QVariantMap map;
    map.insert("header", Header::toVariantMap(msg.header));
    map.insert("orientation", Quaternion::toVariantMap(msg.orientation));
    map.insert("orientation_covariance", toVariant<double, 9>(msg.orientation_covariance));
    map.insert("angular_velocity", Vector3::toVariantMap(msg.angular_velocity));
    map.insert("angular_velocity_covariance", toVariant<double, 9>(msg.angular_velocity_covariance));
    map.insert("linear_acceleration", Vector3::toVariantMap(msg.linear_acceleration));
    map.insert("linear_acceleration_covariance", toVariant<double, 9>(msg.linear_acceleration_covariance));
    return map;
}

inline sensor_msgs::msg::Imu toMessage(const QVariantMap& map){
    sensor_msgs::msg::Imu msg;
    msg.header = Header::toMessage(map["header"].toMap());
    msg.orientation = Quaternion::toMessage(map["orientation"].toMap());
    msg.orientation_covariance = toArray<double, 9>("orientation_covariance", map);
    msg.angular_velocity = Vector3::toMessage(map["angular_velocity"].toMap());
    msg.angular_velocity_covariance = toArray<double, 9>("angular_velocity_covariance", map);
    msg.angular_velocity = Vector3::toMessage(map["linear_acceleration"].toMap());
    msg.angular_velocity_covariance = toArray<double, 9>("linear_acceleration_covariance", map);
    return msg;
}
}

namespace  LaserScan{
//https://docs.ros2.org/foxy/api/sensor_msgs/msg/LaserScan.html

inline QVariantMap toVariantMap(const sensor_msgs::msg::LaserScan& msg){
    QVariantMap map;
    map.insert("header", Header::toVariantMap(msg.header));
    map.insert("angle_min", toVariant(msg.angle_min));
    map.insert("angle_max", toVariant(msg.angle_max));
    map.insert("angle_increment", toVariant(msg.angle_increment));
    map.insert("time_increment", toVariant(msg.time_increment));
    map.insert("scan_time", toVariant(msg.scan_time));
    map.insert("range_min", toVariant(msg.range_min));
    map.insert("range_max", toVariant(msg.range_max));
    map.insert("ranges", toVariant<float>(msg.ranges));
    map.insert("intensities", toVariant<float>(msg.intensities));
    return map;
}

inline sensor_msgs::msg::LaserScan toMessage(const QVariantMap& map){
    sensor_msgs::msg::LaserScan msg;
    msg.header = Header::toMessage(map["header"].toMap());
    msg.angle_min = toFloat("angle_min", map);
    msg.angle_max = toFloat("angle_max", map);
    msg.angle_increment = toFloat("angle_increment", map);
    msg.time_increment = toFloat("time_increment", map);
    msg.scan_time = toFloat("scan_time", map);
    msg.range_min = toFloat("range_min", map);
    msg.range_max = toFloat("range_max", map);
    msg.ranges = toVector<float>("ranges", map);
    msg.intensities = toVector<float>("intensities", map);
    return msg;
}
}

}
