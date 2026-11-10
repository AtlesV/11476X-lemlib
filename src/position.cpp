#include "main.h"
#include "position.h"

// Create the RoboDash console widget
namespace {
    rd::Console positionConsole("Position");

    void positionTask(void*) {
        while (true) {
            // Get the robot's current position
            lemlib::Pose pose = chassis.getPose();

            // Refresh the console
            positionConsole.clear();

            positionConsole.println("===== ROBOT POSITION =====");
            positionConsole.println("");

            positionConsole.printf("X: %.2f\n", pose.x);
            positionConsole.printf("Y: %.2f\n", pose.y);
            positionConsole.printf("Theta: %.2f deg\n", pose.theta);

            positionConsole.println("");
            positionConsole.println("==========================");

            // Update every 100 milliseconds
            pros::delay(100);
        }
    }
}

void startPositionDisplay() {
    // Start the position display task
    static pros::Task task(positionTask);
}