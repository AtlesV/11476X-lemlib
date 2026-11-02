#include "main.h"

ASSET(example_txt);

void middleAutonBlue() {
    // Middle autonomous routine for blue alliance
    chassis.moveToPoint(0, 24, 4000, {}, true);
    chassis.turnToHeading(180, 4000, {}, true);
    chassis.moveToPoint(0, 0, 4000);
}

void rightAutonBlue() {
    // Right autonomous routine for blue alliance
    chassis.moveToPose(24, 24, 270, 4000, {}, false);
    liftPID.move(500);
    
}

void middleAutonRed() {
    // Middle autonomous routine for red alliance
    chassis.moveToPoint(0, -24, 2000);
}

void rightAutonRed() {
    // Right autonomous routine for red alliance
    chassis.moveToPoint(0, 24, 2000);
}

void skillsAuton() {
    // Skills autonomous routine
    chassis.follow(example_txt, 15, 4000);
}
