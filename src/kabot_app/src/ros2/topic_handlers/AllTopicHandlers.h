#pragma once

#include <memory>
#include <QPair>

#include "geometry_msgs/PointHandler.h"
#include "geometry_msgs/PoseHandler.h"
#include "geometry_msgs/PoseWithCovarianceHandler.h"
#include "geometry_msgs/QuaternionHandler.h"
#include "geometry_msgs/TwistHandler.h"
#include "geometry_msgs/TwistWithCovarianceHandler.h"
#include "geometry_msgs/Vector3Handler.h"

#include "rcl_interfaces/LogHandler.h"

#include "sensor_msgs/ImageHandler.h"
#include "sensor_msgs/ImuHandler.h"

#include "std_msgs/BoolHandler.h"
#include "std_msgs/ByteHandler.h"
#include "std_msgs/Float64MultiArrayHandler.h"

#include "trajectory_msgs/JointTrajectory.h"

#include "nav_msgs/OdometryHandler.h"

namespace topic_handlers{

inline QPair<std::shared_ptr<IRosTopicHandlerSend>, std::shared_ptr<IRosTopicHandlerReceive>> getHandlerForTopic(std::shared_ptr<rclcpp::Node> node, const QString& topic, const QString& topicType){    
    if(topicType == QString("geometry_msgs/msg/Point")){
        auto handler = std::make_shared<PointHandler>(node, topic);
        return qMakePair(handler, handler);
    }
    else if(topicType == QString("geometry_msgs/msg/Pose")){
        auto handler = std::make_shared<PoseHandler>(node, topic);
        return qMakePair(handler, handler);
    }
    else if(topicType == QString("geometry_msgs/msg/PoseWithCovariance")){
        auto handler = std::make_shared<PoseWithCovarianceHandler>(node, topic);
        return qMakePair(handler, handler);
    }
    else if(topicType == QString("geometry_msgs/msg/Quaternion")){
        auto handler = std::make_shared<QuaternionHandler>(node, topic);
        return qMakePair(handler, handler);
    }
    else if(topicType == QString("geometry_msgs/msg/Twist")){
        auto handler = std::make_shared<TwistHandler>(node, topic);
        return qMakePair(handler, handler);
    }
    else if(topicType == QString("geometry_msgs/msg/TwistWithCovariance")){
        auto handler = std::make_shared<TwistWithCovarianceHandler>(node, topic);
        return qMakePair(handler, handler);
    }
    else if(topicType == QString("geometry_msgs/msg/Vector3")){
        auto handler = std::make_shared<Vector3Handler>(node, topic);
        return qMakePair(handler, handler);
    }

    else if(topicType == QString("sensor_msgs/msg/Image")){
        auto handler = std::make_shared<ImageHandler>(node, topic);
        return qMakePair(handler, handler);
    }
    else if(topicType == QString("sensor_msgs/msg/Imu")){
        auto handler = std::make_shared<ImuHandler>(node, topic);
        return qMakePair(handler, handler);
    }

    else if(topicType == QString("std_msgs/msg/Float64MultiArray")){
        auto handler = std::make_shared<Float64MultiArrayHandler>(node, topic);
        return qMakePair(handler, handler);
    }

    else if(topicType == QString("trajectory_msgs/msg/JointTrajectory")){
        auto handler = std::make_shared<JointTrajectoryHandler>(node, topic);
        return qMakePair(handler, handler);
    }

    else if(topicType == QString("rcl_interfaces/msg/Log")){
        auto handler = std::make_shared<LogHandler>(node, topic);
        return qMakePair(handler, handler);
    }

    else if(topicType == QString("nav_msgs/msg/Odometry")){
        auto handler = std::make_shared<OdometryHandler>(node, topic);
        return qMakePair(handler, handler);
    }
    return qMakePair(nullptr, nullptr);
}

}
