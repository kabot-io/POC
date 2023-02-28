#pragma once

#include "RosTopicHandler.h"
#include "TrajectoryMsgsParsers.h"

// http://docs.ros.org/en/lunar/api/trajectory_msgs/html/msg/JointTrajectoryPoint.html

namespace topic_handlers{

class JointTrajectoryHandler: public RosTopicHandler<trajectory_msgs::msg::JointTrajectory>{

public:
    JointTrajectoryHandler(std::shared_ptr<rclcpp::Node> node, const QString topicName): RosTopicHandler(node, topicName, TopicPermissions::ReadWrite, 10){}

    QVariantMap parseMsg(const trajectory_msgs::msg::JointTrajectory::SharedPtr msg) {
        return RosMessageParser::JointTrajectory::toVariantMap(*msg);
    }

    trajectory_msgs::msg::JointTrajectory parseMap(const QVariantMap& map) {
        return RosMessageParser::JointTrajectory::toMessage(map);
    }
};

}
