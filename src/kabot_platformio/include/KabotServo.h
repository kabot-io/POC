#pragma once

#include <Arduino.h>
#include <micro_ros_platformio.h>
#include <ESP32_Servo.h>

#include <geometry_msgs/msg/twist.h>

enum ServoSide{
	Left,
	Right
};

struct KabotServo{
	KabotServo(int pin, int min, int max, int servoOrigin, ServoSide side){
		m_servo.attach(pin, min, max);
		m_servoOrigin = servoOrigin;
		m_servoLeftRange = servoOrigin;
		m_servoRightRange =  180-servoOrigin;
	}

	void move(const geometry_msgs__msg__Twist *msg){
		int servoVelocity;
		if(m_side == ServoSide::Left){
			servoVelocity = msg->linear.x + msg->angular.z;
        }
        else{
			servoVelocity = msg->linear.x - msg->angular.z;
            servoVelocity *= -1;
        }

        if(servoVelocity > 0){
            servoVelocity = map(servoVelocity, m_minServoVelocity, m_minServoVelocity, m_servoOrigin, m_servoRightRange);
        }
        else{
            servoVelocity = map(servoVelocity, m_minServoVelocity, m_maxServoVelocity, m_servoLeftRange, m_servoOrigin);
        }

		m_servo.write(servoVelocity);
	}

private:
	Servo m_servo;
	ServoSide m_side;

	int m_servoOrigin;
	int m_servoLeftRange;
	int m_servoRightRange;

	const int m_minServoVelocity = -100;
	const int m_maxServoVelocity = 100;
};