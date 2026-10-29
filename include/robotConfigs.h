#ifndef _PROS_ROBOT_CONFIG_H_
#define _PROS_ROBOT_CONFIG_H_

#include "main.h"
#include "lemlib/api.hpp"

extern pros::MotorGroup left_motor_group;
extern pros::MotorGroup right_motor_group;
extern lemlib::Chassis chassis;
extern pros::Imu imu;

extern pros::Motor intake;
extern pros::Motor lift1;
extern pros::Motor lift2;
extern pros::Motor claw;
extern pros::Motor clawOr;

extern pros::Rotation liftRotation;

extern pros::MotorGroup lift;

#endif  // _PROS_ROBOT_CONFIG_H_
