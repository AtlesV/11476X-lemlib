#pragma once
#ifndef HELPERS_HPP
#define HELPERS_HPP

#include "main.h"

class LiftPID {
public:
    LiftPID(pros::Rotation& sensor, pros::MotorGroup& motors,
            double kP, double kI, double kD);

    // Move to an encoder position in degrees. This call blocks until reached
    // or until its safety timeout expires.
    void move(double targetDeg);
    void zero();

private:
    pros::Rotation& sensor;
    pros::MotorGroup& motors;
    lemlib::PID pid;
};

extern LiftPID liftPID;

#endif
