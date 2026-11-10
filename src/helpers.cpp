#include "main.h"


LiftPID::LiftPID(pros::Rotation& sensor, pros::MotorGroup& motors,
                double kP, double kI, double kD)
    : sensor(sensor), motors(motors), pid(kP, kI, kD) {}

void LiftPID::move(double targetDeg) {
    pid.reset();
    const std::uint32_t startTime = pros::millis();
    while (pros::millis() - startTime < 5000) {
        // PROS Rotation::get_position() reports centidegrees.
        double positionDeg = sensor.get_position() / 100.0;
        double error = targetDeg - positionDeg;
        if (std::abs(error) <= 3) break;
        double output = pid.update(error);
        output = std::clamp(output, -127.0, 127.0);
        motors.move(static_cast<int>(output));
        pros::delay(10);
    }
    motors.brake();
}

LiftPID liftPID(liftRotation, lift, 5, 0, 20);

void LiftPID::zero() {
    if (sensor.is_installed()) {
        ErrorLogger::error("Rotation sensor detected");
    } else {
        ErrorLogger::error("Rotation sensor not detected");
    }

    move(-1000);
    pros::delay(500);  // Duration in milliseconds
    move(0);           // Stop the lift
    sensor.reset_position();
}