# Kabot - lowering entry barrier to ROS2

The Kabot robot is a hardware and software solution that lowers the entry barrier to Robot Operating System 2 (ROS2) and provides an expandable platform for makers, students and educators. One of the main obstacles in the adoption of ROS2 by beginners is the high knowledge barrier needed to setup and start tinkering - Kabot mission is to bring batteries included in a box. Think of using Arduino instead of setting up whole toolchain and build system.

The robot is a simple differential drive robot with expansion port for connecting external sensors and actuators, and instead of classic internal odometry sensors uses external camera to track itself in the world. Main goals are to create as simple (thus cost effective) hardware, move as much of heavy lifting as possible to the host PC instead of the robot itself and provide user with simple software environment.

## Hardware
All of the structural parts are designed for FDM printing. Wheels, base, cell holder - PLA will do. For the tires, standard O-Ring seals are used, as they are easily available for a cost next to nothing.

Kabot has two actuators - MG90S servos in a continous rotation version. This way, no on-board H-Bridge is needed, just one GPIO per motor and 5V power. Those servos also come with horns that can be used to attach wheels securely. 

All the electrons needed to keep the robot running are supplied via single 18650 Li-Ion cell. Charging, battery protection, and switching on and off is provided via IPS5306 - chinesium powerbank IC. Power for the charger is supplied via USB-C connector. This converter provides 5V for the servos and expansion port, and LDO provides 3.3V for the SoC and expansion port.

The main board is based around ESP32-S3 chip, sporting 16MB of flash and 8MB of RAM. Why ESP32-S3 instead of base ESP32? S3 has built-in USB peripheral, that hosts USB-JTAG and USB-CDC out of the box, so flashing, GDB and Serial.println() works without any external hardware. Furthermore, S3 is a little beefier, and has reconfigurable GPIO matrix, which will ease development of add-on boards. Most of the communication and other internal peripherals can be configured to use any pin of the package. 


## Installation

To run the robots, you need to install ROS2 Foxy. ROS2 is a software framework designed for robotic systems development. It provides a set of libraries and tools to help developers create robust and complex robot applications.

To install ROS2 Foxy, please follow the instructions provided on the official ROS2 website: https://docs.ros.org/en/foxy/Installation.html


## License

[Hardware: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/)

[Software: Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0)