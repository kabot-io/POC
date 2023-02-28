#pragma once

#include "RosTopicHandler.h"
#include "StdMsgsParsers.h"

//https://docs.ros2.org/latest/api/std_msgs/msg/Byte.html

namespace topic_handlers{

class ByteHandler: public RosTopicHandler<std_msgs::msg::Byte>{

public:
    ByteHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const std_msgs::msg::Byte::SharedPtr msg) {
        return RosMessageParser::Byte::toVariantMap(*msg);
    }

    std_msgs::msg::Byte parseMap(const QVariantMap& map) {
        return RosMessageParser::Byte::toMessage(map);
    }
};

}
