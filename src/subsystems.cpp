#include "main.h"  // IWYU pragma: keep

void setIntake() {
	if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		intake.move(127);
	} else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		intake.move(-127);
	} else {
		intake.move(0);
	}
}

void setWall() {
	wallmech.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		wallmech.move_absolute(-750, -90);
	} else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		wallmech.move_absolute(0, 90);
	} else {
		wallmech.brake();
	}
}

void setMogo() { mogomech.button_toggle(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)); }

void setRedirect() { indexer.button_toggle(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)); }

void setdoinker() { doinker.button_toggle(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)); }

bool shift() { return master.get_digital(pros::E_CONTROLLER_DIGITAL_R1); }