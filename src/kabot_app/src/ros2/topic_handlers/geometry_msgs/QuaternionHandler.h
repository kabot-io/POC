#pragma once

#include "RosTopicHandler.h"
#include "GeometryMsgsParsers.h"

//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Quaternion.html

namespace topic_handlers{

class QuaternionHandler: public RosTopicHandler<geometry_msgs::msg::Quaternion>{

public:
    QuaternionHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const geometry_msgs::msg::Quaternion::SharedPtr msg) final override{
        return RosMessageParser::Quaternion::toVariantMap(*msg);
    }

    geometry_msgs::msg::Quaternion parseMap(const QVariantMap& map) final override{
        return RosMessageParser::Quaternion::toMessage(map);
    }
};

}
