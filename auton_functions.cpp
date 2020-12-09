#include "main.h"
#include "config.hpp"
#include "auton_functions.h"
const double WHEEL_RADIUS = 1.625;
const int DEFAULTSLEWRATEINCREMENT = 10;
const float TICKS_PER_ROTATION =  360.0;
const double CIRCUMFERENCE = 2*M_PI*WHEEL_RADIUS;
void slewRateControl(pros::Motor *motor, int targetVelocity, int increment){
  int currentVelocity = motor->get_target_velocity();
  if (targetVelocity != 0){
    if (currentVelocity != targetVelocity){
      if (targetVelocity > currentVelocity){
        currentVelocity += increment;
      } else if (targetVelocity < currentVelocity){
        currentVelocity -= increment;
      }
      if (std::abs(currentVelocity) > std::abs(targetVelocity)){
        currentVelocity = targetVelocity;
      }
    }
  } else {
    currentVelocity = targetVelocity;
  }
  motor->move_velocity(currentVelocity);
}

void base_PID(float targetdistance, int velocity){
  const double degreeGoal = (targetdistance/1.625*2*M_PI) * TICKS_PER_ROTATION;
  bool goalmet = false;
  double goal = 0.0;
  double target = 0.0;
  double kP = 0.25;
  double kI = 0.0005;
  double kD = 0.005;
  double currentPos = 0;
  double error = 0.0;
  double prevError = goal;
  double targetvelocity = 0.0;
  int maxvelocity = velocity;

  double integral = 0.0;
  double derivative = 0.0;
  error = degreeGoal;

  if(target < 0){
    maxvelocity *= -1;
  }

  target = degreeGoal;

  while(!goalmet){
    //encoders
  error = targetdistance - currentPos;
  if(error < 600){
    integral += error;
  }
  derivative = error - prevError;
  prevError = error;
  targetvelocity = kP*error  + kI*integral  + kD*derivative ;

  if(targetvelocity > maxvelocity){
    targetvelocity =  maxvelocity;
  }

  tlw.move_velocity(targetvelocity);
  trw.move_velocity(-targetvelocity);
  blw.move_velocity(targetvelocity);
  brw.move_velocity(-targetvelocity);

  /**slewRateControl(&blw, targetvelocity,DEFAULTSLEWRATEINCREMENT);
  slewRateControl(&tlw, targetvelocity,DEFAULTSLEWRATEINCREMENT);
  slewRateControl(&brw, targetvelocity,DEFAULTSLEWRATEINCREMENT);
  slewRateControl(&trw, targetvelocity,DEFAULTSLEWRATEINCREMENT);**/

  if(std::abs(error) < 2){
    goalmet = true;
  }

  pros::delay(10);
  }

  brakeMotor();


}

void turn_PID(float targetdegree){
  float turn_constant_right = 2.4;
  float turn_constant_left = 2.42;
  int maxVelocity = 70;
  double degreeGoal;
  if (targetdegree > 0){
    degreeGoal = targetdegree*turn_constant_right;
  }
  else {
degreeGoal = targetdegree*turn_constant_left;
double targetvelocity = 0;
int maxvelocity = 50; //adjust
double error= 0.0;
double currentpos = 0;

bool goalmet = false;
double previous_error = degreeGoal;
double kP = 0.75;
double kI = 0.0005;
double kD = 0.001;
double integral = 0;
double derivative = 0;
int lefttarget = 0;
int righttarget = 0;
 if(targetdegree<0){maxVelocity *= -1;}

while(!goalmet){
  error = degreeGoal - currentpos;

  if(std::abs(error) < 100){
    integral += error;
  }

  derivative = error - previous_error;
  previous_error = error;
  targetvelocity = kP*error + kI*integral + kD*derivative;

  if(std::abs(targetvelocity) > std::abs(maxvelocity)){
    targetvelocity = maxvelocity;

  }

  lefttarget = targetvelocity;
  righttarget = -1*targetvelocity;

  tlw.move_velocity(lefttarget);
  trw.move_velocity(righttarget);
  blw.move_velocity(lefttarget);
  brw.move_velocity(righttarget);
/**
 slewRateControl(&tlw, lefttarget,DEFAULTSLEWRATEINCREMENT);
  slewRateControl(&blw, lefttarget,DEFAULTSLEWRATEINCREMENT);
  slewRateControl(&trw, righttarget,DEFAULTSLEWRATEINCREMENT);
  slewRateControl(&brw, righttarget,DEFAULTSLEWRATEINCREMENT);**/

  if(std::abs(error)<4)
  {
    goalmet = true;
  }
pros::delay(10);
}
tlw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
blw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
trw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
brw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
tlw.move_velocity(0);
blw.move_velocity(0);
trw.move_velocity(0);
brw.move_velocity(0);
}
}


void brakeMotor(){
  tlw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  blw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  trw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  brw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  tlw.move_velocity(0);
  blw.move_velocity(0);
  trw.move_velocity(0);
  brw.move_velocity(0);

}

void unbrakeMotor(){
  tlw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  blw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  trw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  brw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
