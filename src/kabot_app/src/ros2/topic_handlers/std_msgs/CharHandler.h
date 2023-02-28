#pragma once

#include "RosTopicHandler.h"
#include "StdMsgsParsers.h"

//https://docs.ros2.org/latest/api/std_msgs/msg/Char.html

namespace topic_handlers{

class CharHandler: public RosTopicHandler<std_msgs::msg::Char>{

public:
    CharHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const std_msgs::msg::Char::SharedPtr msg) {
        return RosMessageParser::Char::toVariantMap(*msg);
    }

    std_msgs::msg::Char parseMap(const QVariantMap& map) {
        return RosMessageParser::Char::toMessage(map);
    }
};

}
