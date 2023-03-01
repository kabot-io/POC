#include <Arduino.h>
#include <micro_ros_platformio.h>

#include "secrets.h"

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include "KabotServo.h"

#if !defined(MICRO_ROS_TRANSPORT_ARDUINO_WIFI)
#error This example is only avaliable for Arduino framework with wifi transport.
#endif

rcl_publisher_t publisher;
rcl_subscription_t subscriber;
geometry_msgs__msg__Twist msg;

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Error handle loop
void error_loop() {
	while(1) {
		delay(100);
	}
}

KabotServo leftServo(0, 500, 2400, 80, ServoSide::Left);
KabotServo rightServo(0, 500, 2400, 80, ServoSide::Right);

void subscription_callback(const void * msgin)
{
	const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
	leftServo.move(msg);
	rightServo.move(msg);
	RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL)); //debug callback
}

void setup() {
	// configure serial transport
	Serial.begin(115200);

	IPAddress agent_ip(192, 168, 1, 187);
	size_t agent_port = 8888;
	set_microros_wifi_transports(ssid, psk, agent_ip, agent_port);

	allocator = rcl_get_default_allocator();

	// create init_options
	RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

	// create node
	RCCHECK(rclc_node_init_default(&node, "kabot", "", &support));

	// create publisher
	RCCHECK(rclc_publisher_init_default(
		&publisher,
		&node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
		"/cmd_vel_callback"));

	// create subscriber
	RCCHECK(rclc_subscription_init_default(
		&subscriber,
		&node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
		"/cmd_vel"));

	// create executor
	RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
	RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA));
}

void loop() {
	delay(100);
	RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}