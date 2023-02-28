#include <Arduino.h>
#include <micro_ros_platformio.h>
#include "secrets.h"

#include <ESP32_Servo.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <geometry_msgs/msg/twist.h>

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

Servo servoL;
Servo servoR; 

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Error handle loop
void error_loop() {
	while(1) {
		delay(100);
	}
}

void subscription_callback(const void * msgin)
{
	const int servoOrigin = 80; // (0-180) dla obu kol moze byc inne. Zamknac to w klase i wyczyscic to moze zacznie dzialac
	const int servoLeftRange = servoOrigin;
	const int servoRightRange =  180-servoOrigin;

	const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
	int linear_x = msg->linear.x;
	int angular_z = msg->angular.z*;
	int velocityServoL = linear_x + angular_z;
	int velocityServoR = linear_x - angular_z;

	int minServoVelocity = -100;
	int maxServoVelocity = 100;

	if(velocityServoL > 0){
		velocityServoL = map(velocityServoL, minServoVelocity, maxServoVelocity, servoOrigin, servoRightRange);
	}
	else{
		velocityServoL = map(velocityServoL, minServoVelocity, maxServoVelocity, servoLeftRange, servoOrigin);
	}

	if(velocityServoR > 0){
		velocityServoR = map(velocityServoR, minServoVelocity, maxServoVelocity, servoOrigin, servoRightRange);
	}
	else{
		velocityServoR = map(velocityServoR, minServoVelocity, maxServoVelocity, servoLeftRange, servoOrigin);
	}
	
	servoL.write(velocityServoL);
	servoR.write(velocityServoR);

	geometry_msgs__msg__Twist intMsg;
	intMsg.linear.x = velocityServoL;
	intMsg.angular.z = velocityServoR;
	RCSOFTCHECK(rcl_publish(&publisher, &intMsg, NULL)); //debug callback
}

void setup() {
	// configure serial transport
	Serial.begin(115200);

	IPAddress agent_ip(192, 168, 1, 187);
	size_t agent_port = 8888;
	set_microros_wifi_transports(ssid, psk, agent_ip, agent_port);

	allocator = rcl_get_default_allocator();

	// configure servos
	int minUs = 500;
	int maxUs = 2400;
	int leftAPin = 0;
	int rightAPin = 2;
	
	servoL.attach(leftAPin, minUs, maxUs);
	servoR.attach(rightAPin, minUs, maxUs);

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