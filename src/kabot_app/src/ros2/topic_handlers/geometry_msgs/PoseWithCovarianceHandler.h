#pragma once

#include "RosTopicHandler.h"
#include "GeometryMsgsParsers.h"

//https://docs.ros2.org/foxy/api/geometry_msgs/msg/PoseWithCovariance.html

namespace topic_handlers{

class PoseWithCovarianceHandler: public RosTopicHandler<geometry_msgs::msg::PoseWithCovariance>{

public:
    PoseWithCovarianceHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const geometry_msgs::msg::PoseWithCovariance::SharedPtr msg) final override{
        return RosMessageParser::PoseWithCovariance::toVariantMap(*msg);
    }

    geometry_msgs::msg::PoseWithCovariance parseMap(const QVariantMap& map) final override{
        return RosMessageParser::PoseWithCovariance::toMessage(map);
    }
};

}
