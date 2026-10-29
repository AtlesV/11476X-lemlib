
#include "main.h"
#include "info.h"

#include <string>

static rd::Console generalInfo("General Info");

void updateGeneralInfo() {
    generalInfo.clear();

    generalInfo.println("===== GENERAL INFO =====");
    generalInfo.println("-------- IMU --------");

    if (imu.is_calibrating()) {
        generalInfo.println("Status: CALIBRATING");
    } else {
        generalInfo.println("Status: CALIBRATED");
        generalInfo.println(
            "Heading: " +
            std::to_string(static_cast<int>(imu.get_heading())) + " deg"
        );
    }

    generalInfo.println("");
    generalInfo.println("===== DRIVETRAIN =====");

    struct MotorInfo {
        const char* name;
        int port;
    };

    const MotorInfo drivetrain[] = {
        {"Left Front", 1},
        {"Left Back", 2},
        {"Right Front", 4},
        {"Right Back", 5}
    };

    for (const auto& motor : drivetrain) {
        double tempC = pros::c::motor_get_temperature(motor.port);
        int tempF = static_cast<int>(tempC * 9.0 / 5.0 + 32.0);

        generalInfo.println(
            std::string(motor.name) + " P" +
            std::to_string(motor.port) + ": " +
            std::to_string(tempF) + " F"
        );
    }

    generalInfo.println("");
    generalInfo.println("===== MECHANISMS =====");

    const MotorInfo mechanisms[] = {
        {"Intake", 3},
        {"Lift 1", 6},
        {"Lift 2", 7},
        {"Claw", 1},
        {"Claw Orientation", 8}
    };

    for (const auto& motor : mechanisms) {
        double tempC = pros::c::motor_get_temperature(motor.port);
        int tempF = static_cast<int>(tempC * 9.0 / 5.0 + 32.0);

        generalInfo.println(
            std::string(motor.name) + " P" +
            std::to_string(motor.port) + ": " +
            std::to_string(tempF) + " F"
        );
    }
}
