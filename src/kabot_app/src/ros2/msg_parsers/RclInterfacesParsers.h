#pragma once

#include <QVariant>
#include "ParserUtils.h"

#include "rcl_interfaces/msg/log.hpp"

namespace RosMessageParser{
using namespace ParseUtils;

namespace Log {
//https://docs.ros2.org/foxy/api/rcl_interfaces/msg/Log.html

inline QVariantMap toVariantMap(const rcl_interfaces::msg::Log& msg) {
    QVariantMap map;
    map.insert("level", toVariant(msg.level));
    map.insert("name", toVariant(msg.name));
    map.insert("msg", toVariant(msg.msg));
    return map;
}

inline rcl_interfaces::msg::Log toMessage(const QVariantMap& map) {
    rcl_interfaces::msg::Log msg;
    msg.level = toUint8("level", map);
    msg.name = toString("name", map);
    msg.msg = toString("msg", map);
    return msg;
}
}

}
