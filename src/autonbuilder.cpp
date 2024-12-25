#include "autonbuilder.hpp"

#include "main.h"  // IWYU pragma: keep

void testautonbuilder() {
	pros::Task ringsort(ringsensTask, (void*)"0");
	chassis.odom_pose_set({48_in, 21_in, 180_deg});
	left_mogo();
	left_btm_ring();
	red_ring_rush();
	mogomech.set(false);
	mid_top_ring();
	alliancestake();
	ladder();
}

void goal_rush() {
	doinker.set(true);
	chassis.pid_odom_set(62_in, 127, false);
	chassis.pid_wait();
	chassis.pid_odom_set(-24_in, 127, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(180_deg, 127);
	chassis.pid_wait();
}

void alliancestake() {
	intake.move(0);
	chassis.pid_odom_set({{{72_in, 24_in, 180_deg}, fwd, 127}, {{72_in, 0_in}, rev, 70}});
	intake.move(-127);
	chassis.pid_wait();
}

void left_mogo() {
	chassis.pid_odom_set({{48_in, 48_in}, rev, 127});
	mogomech.set(true);
	chassis.pid_wait();
}

void gr_mogo() {
	chassis.pid_odom_set({{120_in, 48_in}, rev, 127});
	mogomech.set(true);
	chassis.pid_wait();
}

void right_mogo() {
	chassis.pid_odom_set({{96_in, 48_in}, rev, 127});
	mogomech.set(true);
	chassis.pid_wait();
}

void left_corner() {
	// corner rush
}

void right_corner() {
	// corner rush
}

void red_ring_rush() {
	intake.move(-127);
	chassis.pid_odom_set({{{18_in, 61_in, 0_deg}, fwd, 127}, {{34_in, 63_in}, fwd, 60}});
	chassis.pid_wait();
}

void blue_ring_rush() {
	intake.move(-127);
	chassis.pid_odom_set({{{126_in, 61_in, 0_deg}, fwd, 127}, {{110_in, 63_in}, fwd, 60}});
	chassis.pid_wait();
}

void left_btm_ring() {
	intake.move(-127);
	chassis.pid_odom_set({{24_in, 48_in}, fwd, 127});
	chassis.pid_wait();
}

void mid_top_ring() {
	intakeLevel.set(true);
	intake.move(-127);
	chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
	pros::delay(500);
	intakeLevel.set(false);
	chassis.pid_wait();
}

void right_btm_ring() {
	intake.move(-127);
	chassis.pid_odom_set({{120_in, 48_in}, fwd, 127});
	chassis.pid_wait();
}

void ladder() {
	pros::delay(2000);
	intake.move(127);
	chassis.pid_odom_set({{72_in, 60_in}, fwd, 127});
	chassis.pid_wait();
}