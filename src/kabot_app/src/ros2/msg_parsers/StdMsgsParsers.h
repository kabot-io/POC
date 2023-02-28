#pragma once

#include <QVariant>
#include "ParserUtils.h"

#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/byte.hpp"
#include "std_msgs/msg/char.hpp"
#include "std_msgs/msg/color_rgba.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "std_msgs/msg/header.hpp"

#include "BuiltinInterfacesParsers.h"

namespace RosMessageParser{
using namespace ParseUtils;

namespace Bool{
//https://docs.ros2.org/latest/api/std_msgs/msg/Bool.html

inline QVariantMap toVariantMap(const std_msgs::msg::Bool& msg){
    QVariantMap map;
    map.insert("data", toVariant(msg.data));
    return map;
}

inline std_msgs::msg::Bool toMessage(const QVariantMap& map){
    std_msgs::msg::Bool msg;
    msg.data = toBool("data", map);
    return msg;
}
}

namespace Byte{
//https://docs.ros2.org/latest/api/std_msgs/msg/Byte.html

inline QVariantMap toVariantMap(const std_msgs::msg::Byte& msg){
    QVariantMap map;
    map.insert("data", toVariant(msg.data));
    return map;
}

inline std_msgs::msg::Byte toMessage(const QVariantMap& map){
    std_msgs::msg::Byte msg;
    msg.data = toBool("data", map);
    return msg;
}
}

namespace Char{
//https://docs.ros2.org/latest/api/std_msgs/msg/Char.html

inline QVariantMap toVariantMap(const std_msgs::msg::Char& msg){
    QVariantMap map;
    map.insert("data", toVariant(msg.data));
    return map;
}

inline std_msgs::msg::Char toMessage(const QVariantMap& map){
    std_msgs::msg::Char msg;
    msg.data = toBool("data", map);
    return msg;
}
}

namespace ColorRGBA{
//https://docs.ros2.org/latest/api/std_msgs/msg/ColorRGBA.html

inline QVariantMap toVariantMap(const std_msgs::msg::ColorRGBA& msg){
    QVariantMap map;
    map.insert("r", toVariant(msg.r));
    map.insert("g", toVariant(msg.g));
    map.insert("b", toVariant(msg.b));
    map.insert("a", toVariant(msg.a));
    return map;
}

inline std_msgs::msg::ColorRGBA toMessage(const QVariantMap& map){
    std_msgs::msg::ColorRGBA msg;
    msg.r = toFloat("r", map);
    msg.g = toFloat("g", map);
    msg.b = toFloat("b", map);
    msg.a = toFloat("a", map);
    return msg;
}
}

namespace Float64MultiArray{
//https://docs.ros2.org/latest/api/std_msgs/msg/Float64MultiArray.html

inline QVariantMap toVariantMap(const std_msgs::msg::Float64MultiArray& msg){
    QVariantMap map;
    map.insert("data", toVariant(msg.data));
    return map;
}

inline std_msgs::msg::Float64MultiArray toMessage(const QVariantMap& map){
    std_msgs::msg::Float64MultiArray msg;
    msg.data = toVector<double>("data", map);
    return msg;
}
}

namespace Header{
//https://docs.ros2.org/foxy/api/std_msgs/msg/Header.html

inline QVariantMap toVariantMap(const std_msgs::msg::Header& msg){
    QVariantMap map;
    map.insert("stamp", Time::toVariantMap(msg.stamp));
    map.insert("frame_id", toVariant(msg.frame_id));
    return map;
}

inline std_msgs::msg::Header toMessage(const QVariantMap& map){
    std_msgs::msg::Header msg;
    msg.stamp = Time::toMessage(map["stamp"].toMap());
    msg.frame_id = toString("frame_id", map);
    return msg;
}
}

}
