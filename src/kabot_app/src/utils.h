#pragma once

#include <QString>

#include "rclcpp/rclcpp.hpp"

constexpr auto NODE_NAME = "hmi_node";

namespace logger {

constexpr bool DEBUG_MODE = false;

inline void info(const QString& className, const QString& log){
    if(DEBUG_MODE){
        RCLCPP_INFO(rclcpp::get_logger(NODE_NAME), QString("[%1]: %2").arg(className, log).toStdString());
    }
    else{
        RCLCPP_INFO(rclcpp::get_logger(NODE_NAME), log.toStdString());
    }
}

inline void warning(const QString& className, const QString& log){
    if(DEBUG_MODE){
        RCLCPP_WARN(rclcpp::get_logger(NODE_NAME), QString("[%1]: %2").arg(className, log).toStdString());
    }
    else{
        RCLCPP_WARN(rclcpp::get_logger(NODE_NAME), log.toStdString());
    }
}

inline void error(const QString& className, const QString& log){
    if(DEBUG_MODE){
        RCLCPP_ERROR(rclcpp::get_logger(NODE_NAME), QString("[%1]: %2").arg(className, log).toStdString());
    }
    else{
        RCLCPP_ERROR(rclcpp::get_logger(NODE_NAME), log.toStdString());
    }
}

}
