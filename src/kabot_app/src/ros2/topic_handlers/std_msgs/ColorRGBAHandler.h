#pragma once

#include "RosTopicHandler.h"
#include "StdMsgsParsers.h"

//https://docs.ros2.org/latest/api/std_msgs/msg/ColorRGBA.html

namespace topic_handlers{

class ColorRGBAHandler: public RosTopicHandler<std_msgs::msg::ColorRGBA>{

public:
    ColorRGBAHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const std_msgs::msg::ColorRGBA::SharedPtr msg) {
        return RosMessageParser::ColorRGBA::toVariantMap(*msg);
    }

    std_msgs::msg::ColorRGBA parseMap(const QVariantMap& map) {
        return RosMessageParser::ColorRGBA::toMessage(map);
    }
};

}
