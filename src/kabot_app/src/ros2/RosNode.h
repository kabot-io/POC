#pragma once

#include "rclcpp/rclcpp.hpp"

#include "utils.h"

class RosNode : public rclcpp::Node
{
public:
    RosNode(): Node(NODE_NAME){}
};
