#pragma once

#include "RosTopicHandler.h"
#include "GeometryMsgsParsers.h"

//https://docs.ros2.org/foxy/api/geometry_msgs/msg/TwistWithCovariance.html

namespace topic_handlers{

class TwistWithCovarianceHandler: public RosTopicHandler<geometry_msgs::msg::TwistWithCovariance>{

public:
    TwistWithCovarianceHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const geometry_msgs::msg::TwistWithCovariance::SharedPtr msg) final override{
        return RosMessageParser::TwistWithCovariance::toVariantMap(*msg);
    }

    geometry_msgs::msg::TwistWithCovariance parseMap(const QVariantMap& map) final override{
        return RosMessageParser::TwistWithCovariance::toMessage(map);
    }
};

}
