#pragma once

#include "EZ-Template/api.hpp"  // IWYU pragma: keep
#include "api.h"  // IWYU pragma: keep

// Motors, sensors, etc
inline pros::MotorGroup intake({-6, 4});
inline pros::Motor wallmech(21);
inline ez::Piston mogomech('G');
inline ez::Piston indexer('A');
inline ez::Piston intakeLevel('B');
inline ez::Piston doinker('C');
inline pros::Optical ringsens(8);
// inline pros::adi::DigitalIn limit_switch('A');

// Functions
void setIntake();
void setWall();
void setMogo();
void setRedirect();
void setdoinker();
bool shift();