#pragma once

#include "BuiltinInterfacesParsers.h"
#include "RosTopicHandler.h"

//https://docs.ros2.org/foxy/api/builtin_interfaces/msg/Duration.html

namespace topic_handlers{

class DurationHandler: public RosTopicHandler<builtin_interfaces::msg::Duration>{

public:
    DurationHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const builtin_interfaces::msg::Duration::SharedPtr msg) {
        return RosMessageParser::Duration::toVariantMap(*msg);
    }

    builtin_interfaces::msg::Duration parseMap(const QVariantMap& map) {
        return RosMessageParser::Duration::toMessage(map);
    }
};

}
