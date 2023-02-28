#pragma once

#include "RosTopicHandler.h"
#include "GeometryMsgsParsers.h"

//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Vector3.html

namespace topic_handlers{

class Vector3Handler: public RosTopicHandler<geometry_msgs::msg::Vector3>{

public:
    Vector3Handler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const std::shared_ptr<geometry_msgs::msg::Vector3> msg) final override{
        return RosMessageParser::Vector3::toVariantMap(*msg);
    }

    geometry_msgs::msg::Vector3 parseMap(const QVariantMap& map) final override{
        return RosMessageParser::Vector3::toMessage(map);
    }
};

}
