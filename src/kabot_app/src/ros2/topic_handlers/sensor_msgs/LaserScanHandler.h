#pragma once

#include "RosTopicHandler.h"
#include "SensorMsgsParsers.h"

//https://docs.ros2.org/foxy/api/sensor_msgs/msg/Imu.html

namespace topic_handlers{

class LaserScanHandler: public RosTopicHandler<sensor_msgs::msg::LaserScan>{

public:
    LaserScanHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadOnly, 10){}

    QVariantMap parseMsg(const sensor_msgs::msg::LaserScan::SharedPtr msg) final override{
        return RosMessageParser::LaserScan::toVariantMap(*msg);
    }

    sensor_msgs::msg::LaserScan parseMap(const QVariantMap& map) final override{
        return RosMessageParser::LaserScan::toMessage(map);
    }
};

}
