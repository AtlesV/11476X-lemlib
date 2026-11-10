#include "main.h"
extern const lv_img_dsc_t team_logo;

extern rd::Image teamLogo;

// Create the touchscreen selector
rd::Selector selector({
    {"Middle Auton", middleAuton, ""},
    {"Right Auton", rightAuton, ""},
    {"Skills", skillsAuton, ""}
});

// initialize function. Runs on program startup
void initialize() {
    chassis.calibrate(); // calibrate sensors
	
	startPositionDisplay();
	selector.focus();

	liftPID.zero();

	if (imu.is_installed() == true && vertical_encoder.is_installed() == true) {
		ErrorLogger::info("Robot initialized");
	} else if (imu.is_installed() == false) {
		ErrorLogger::error("Imu not found");
	} else if (vertical_encoder.is_installed() == false) {
		ErrorLogger::error("Odom pod not found");
	}

	lift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	claw.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	clawOr.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	selector.run_auton();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    // loop forever
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	const std::uint32_t startTime = pros::millis();
    bool rumbled = false;
    while (true) {
        // get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX);

		// delay to save resources
		pros::delay(10);

		///
		//Lift
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			lift.move(127);
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			lift.move(-127);
		} else {
			lift.brake();
		}

		///
		//Intake/Claw
		///
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			intake.move(127);
			claw.move(127);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			intake.move(-127);
			claw.move(-127);
		} else {
			intake.brake();
			claw.brake();
		}

		///
		//Claw orientation
		///
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
			clawOr.move(127);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			clawOr.move(-127);
		} else {
			clawOr.brake();
		}

        // delay to save resources
		static uint32_t lastInfoUpdate = 0;

		if (pros::millis() - lastInfoUpdate >= 1000) {
			updateGeneralInfo();
			lastInfoUpdate = pros::millis();
		}

		if (!rumbled && pros::millis() - startTime >= 90000) {
            controller.rumble("-.-.-");
            rumbled = true;
        }
	}
}