#pragma once

#include <QVariant>
#include "ParserUtils.h"

#include "GeometryMsgsParsers.h"
#include "StdMsgsParsers.h"
#include "nav_msgs/msg/odometry.hpp"

namespace RosMessageParser{
using namespace ParseUtils;

namespace Odometry {
//https://docs.ros2.org/foxy/api/nav_msgs/msg/Odometry.html

inline QVariantMap toVariantMap(const nav_msgs::msg::Odometry& msg) {
    QVariantMap map;
    map.insert("header", Header::toVariantMap(msg.header));
    map.insert("child_frame_id", toVariant(msg.child_frame_id));
    map.insert("pose", PoseWithCovariance::toVariantMap(msg.pose));
    map.insert("twist", TwistWithCovariance::toVariantMap(msg.twist));

    return map;
}

inline nav_msgs::msg::Odometry toMessage(const QVariantMap& map) {
    nav_msgs::msg::Odometry msg;
    msg.header = Header::toMessage(map["header"].toMap());
    msg.child_frame_id = toString("child_frame_id", map);
    msg.pose = PoseWithCovariance::toMessage(map["pose"].toMap());
    msg.twist = TwistWithCovariance::toMessage(map["twist"].toMap());
    return msg;
}
}

}
