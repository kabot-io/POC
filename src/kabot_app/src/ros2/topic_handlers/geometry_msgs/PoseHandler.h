#pragma once

#include "RosTopicHandler.h"
#include "GeometryMsgsParsers.h"

//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Pose.html

namespace topic_handlers{

class PoseHandler: public RosTopicHandler<geometry_msgs::msg::Pose>{

public:
    PoseHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const geometry_msgs::msg::Pose::SharedPtr msg) final override{
        return RosMessageParser::Pose::toVariantMap(*msg);
    }

    geometry_msgs::msg::Pose parseMap(const QVariantMap& map) final override{
        return RosMessageParser::Pose::toMessage(map);
    }
};

}
