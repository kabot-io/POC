#pragma once

#include <QVariant>
#include "ParserUtils.h"

#include "builtin_interfaces/msg/duration.hpp"
#include "builtin_interfaces/msg/time.hpp"


namespace RosMessageParser{
using namespace ParseUtils;

namespace Duration{
//https://docs.ros2.org/foxy/api/builtin_interfaces/msg/Duration.html

inline QVariantMap toVariantMap(const builtin_interfaces::msg::Duration& msg){
    QVariantMap map;
    map.insert("sec", toVariant(msg.sec));
    map.insert("nanosec", toVariant(msg.nanosec));
    return map;
}

inline builtin_interfaces::msg::Duration toMessage(const QVariantMap& map){
    builtin_interfaces::msg::Duration msg;
    msg.sec = toUint32("sec", map);
    msg.nanosec = toUint32("nanosec", map);
    return msg;
}
}

namespace Time{
//https://docs.ros2.org/foxy/api/builtin_interfaces/msg/Time.html

inline QVariantMap toVariantMap(const builtin_interfaces::msg::Time& msg){
    QVariantMap map;
    map.insert("sec", toVariant(msg.sec));
    map.insert("nanosec", toVariant(msg.nanosec));
    return map;
}

inline builtin_interfaces::msg::Time toMessage(const QVariantMap& map){
    builtin_interfaces::msg::Time msg;
    msg.sec = toUint32("sec", map);
    msg.nanosec = toUint32("nanosec", map);
    return msg;
}
}

}
