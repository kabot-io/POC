#pragma once

#include "RosTopicHandler.h"
#include "GeometryMsgsParsers.h"

//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Twist.html

namespace topic_handlers{

class TwistHandler: public RosTopicHandler<geometry_msgs::msg::Twist>{

public:
    TwistHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const geometry_msgs::msg::Twist::SharedPtr msg) final override{
        return RosMessageParser::Twist::toVariantMap(*msg);
    }

    geometry_msgs::msg::Twist parseMap(const QVariantMap& map) final override{
        return RosMessageParser::Twist::toMessage(map);
    }
};

}
