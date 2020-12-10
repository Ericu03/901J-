#include "main.h"
#include "config.hpp"

void slewRateControl(pros::Motor *motor, int targetVelocity, int increment);
void base_PID(double targetdistance, int velocity);
void turn_PID(float targetdegree);

void brakeMotor();
void unbrakeMotor();
