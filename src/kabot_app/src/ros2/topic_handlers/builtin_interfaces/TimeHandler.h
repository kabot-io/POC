#pragma once

#include "RosTopicHandler.h"
#include "BuiltinInterfacesParsers.h"

//https://docs.ros2.org/foxy/api/builtin_interfaces/msg/Time.html

namespace topic_handlers{

class TimeHandler: public RosTopicHandler<builtin_interfaces::msg::Time>{

public:
    TimeHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const builtin_interfaces::msg::Time::SharedPtr msg) {
        return RosMessageParser::Time::toVariantMap(*msg);
    }

    builtin_interfaces::msg::Time parseMap(const QVariantMap& map) {
        return RosMessageParser::Time::toMessage(map);
    }
};

}
