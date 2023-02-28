#pragma once

#include "RosTopicHandler.h"
#include "RclInterfacesParsers.h"

//https://docs.ros2.org/foxy/api/rcl_interfaces/msg/Log.html

namespace topic_handlers{

class LogHandler: public RosTopicHandler<rcl_interfaces::msg::Log>{

public:
    LogHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadOnly, 10){}

    QVariantMap parseMsg(const rcl_interfaces::msg::Log::SharedPtr msg) final override{
        return RosMessageParser::Log::toVariantMap(*msg);
    }

    rcl_interfaces::msg::Log parseMap(const QVariantMap& map) final override{
        return RosMessageParser::Log::toMessage(map);
    }
};

}
