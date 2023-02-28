#pragma once

#include "RosTopicHandler.h"
#include "StdMsgsParsers.h"

//https://docs.ros2.org/latest/api/std_msgs/msg/Float64MultiArray.html

namespace topic_handlers{

class Float64MultiArrayHandler: public RosTopicHandler<std_msgs::msg::Float64MultiArray>{

public:
    Float64MultiArrayHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
        return RosMessageParser::Float64MultiArray::toVariantMap(*msg);
    }

    std_msgs::msg::Float64MultiArray parseMap(const QVariantMap& map) {
        return RosMessageParser::Float64MultiArray::toMessage(map);
    }
};

}
