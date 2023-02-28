#pragma once

#include "RosTopicHandler.h"
#include "StdMsgsParsers.h"

//https://docs.ros2.org/foxy/api/std_msgs/msg/Header.html

namespace topic_handlers{

class HeaderHandler: public RosTopicHandler<std_msgs::msg::Header>{

public:
    HeaderHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const std_msgs::msg::Header::SharedPtr msg) {
        return RosMessageParser::Header::toVariantMap(*msg);
    }

    std_msgs::msg::Header parseMap(const QVariantMap& map) {
        return RosMessageParser::Header::toMessage(map);
    }
};

}
