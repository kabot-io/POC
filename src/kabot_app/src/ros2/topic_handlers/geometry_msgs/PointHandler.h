#pragma once

#include "RosTopicHandler.h"
#include "GeometryMsgsParsers.h"

//https://docs.ros2.org/foxy/api/geometry_msgs/msg/Point.html

namespace topic_handlers{

class PointHandler: public RosTopicHandler<geometry_msgs::msg::Point>{

public:
    PointHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const geometry_msgs::msg::Point::SharedPtr msg) final override{
        return RosMessageParser::Point::toVariantMap(*msg);
    }

    geometry_msgs::msg::Point parseMap(const QVariantMap& map) final override{
        return RosMessageParser::Point::toMessage(map);
    }
};

}
