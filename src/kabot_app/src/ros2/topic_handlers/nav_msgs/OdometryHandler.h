#pragma once

#include "RosTopicHandler.h"
#include "NavMsgsParsers.h"

//https://docs.ros2.org/foxy/api/nav_msgs/msg/Odometry.html

namespace topic_handlers{

class OdometryHandler: public RosTopicHandler<nav_msgs::msg::Odometry>{

public:
    OdometryHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const std::shared_ptr<nav_msgs::msg::Odometry> msg) final override{
        return RosMessageParser::Odometry::toVariantMap(*msg);
    }

    nav_msgs::msg::Odometry parseMap(const QVariantMap& map) final override{
        return RosMessageParser::Odometry::toMessage(map);
    }
};

}
