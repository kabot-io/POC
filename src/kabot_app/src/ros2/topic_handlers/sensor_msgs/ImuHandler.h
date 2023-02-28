#pragma once

#include "RosTopicHandler.h"
#include "SensorMsgsParsers.h"

//https://docs.ros2.org/foxy/api/sensor_msgs/msg/Imu.html

namespace topic_handlers{

class ImuHandler: public RosTopicHandler<sensor_msgs::msg::Imu>{

public:
    ImuHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadOnly, 10){}

    QVariantMap parseMsg(const sensor_msgs::msg::Imu::SharedPtr msg) final override{
        return RosMessageParser::Imu::toVariantMap(*msg);
    }

    sensor_msgs::msg::Imu parseMap(const QVariantMap& map) final override{
        return RosMessageParser::Imu::toMessage(map);
    }
};

}
