#pragma once

#include "RosTopicHandler.h"
#include "StdMsgsParsers.h"

//https://docs.ros2.org/latest/api/std_msgs/msg/Bool.html

namespace topic_handlers{

class BoolHandler: public RosTopicHandler<std_msgs::msg::Bool>{

public:
    BoolHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const std_msgs::msg::Bool::SharedPtr msg) {
        return RosMessageParser::Bool::toVariantMap(*msg);
    }

    std_msgs::msg::Bool parseMap(const QVariantMap& map) {
        return RosMessageParser::Bool::toMessage(map);
    }
};

}
