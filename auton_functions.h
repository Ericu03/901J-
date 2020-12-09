#include "main.h"
#include "config.hpp"

void slewRateControl(pros::Motor *motor, int targetVelocity, int increment);
void base_PID(float targetdistance, int velocity);
void turn_PID(float targetdegree);
void newbase_PID(int distance, int max_velocity);
void newturn_PID(float targetDegree);
void brakeMotor();
void unbrakeMotor();
