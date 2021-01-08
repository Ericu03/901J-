#include "main.h"
#include "config.hpp"
#include "auton_functions.h"

const double WHEEL_RADIUS = 1.625;
const int DEFAULTSLEWRATEINCREMENT = 10;
const float TICKS_PER_ROTATION =  360.0;
const double CIRCUMFERENCE = 2*M_PI*WHEEL_RADIUS;

// Increase/Decrease motor speed towards target speed by increments and move, if targetVelocity is 0 move at same speed
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

void base_PID(double targetdistance, int velocity){
  leftenc.reset();
 rightenc.reset();
 const double degreeGoal = TICKS_PER_ROTATION*(targetdistance/(1.625*2*M_PI)); // Ticks of rotation needed
 bool goalmet = false;
 double goal = 0.0;
 double target = 0.0;
 double targetvelocity = 0;
 double currentPos = 0;
 int error = 0;
 double prevError = goal;
 double kP = 0.15;
 double kI = 0.0005;
 double kD = 0.005;

 int maxvelocity = velocity;

 double integral = 0.0;
 double derivative = 0.0;
// Rotation ticks away from goal


 target = degreeGoal;

 while(!goalmet){
 currentPos = ((tlw.get_position() + trw.get_position()) / 2);
 //currentPos = leftenc.get_value();
 //currentPos = targetdistance- ((leftenc.get_value() + rightenc.get_value()) /2);
 error = target - currentPos;
 if(std::abs(error) < 600){
   integral = integral + error;
}
else{
  integral = 0;
}
 derivative = error - prevError;
 prevError = error;
targetvelocity = kP*error + kI*integral  + kD*derivative ;

 if(std::abs(targetvelocity) > std::abs(maxvelocity)){
   targetvelocity =  maxvelocity;
 }

 tlw.move_velocity(targetvelocity);
 trw.move_velocity(-targetvelocity);
 blw.move_velocity(targetvelocity);
 brw.move_velocity(targetvelocity);

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

void move_straight_rel_test(double xCoord, int maxVel, int multi){
  leftenc.reset();
  rightenc.reset();

  if(multi == 1){
    intakeL.move_velocity(-100);
    intakeR.move_velocity(100);
  } else{
    intakeL.move_velocity(0);
    intakeR.move_velocity(0);
  }
 const double degreeGoal = (xCoord/(1.375*2*M_PI))*TICKS_PER_ROTATION;
 int maxVelocity = maxVel;
 bool isX = false;
 double target = 0.0;
 double goal = 0.0;
 bool goalMet = false; bool oneTime = true;
 int targetVelocity = 0;
 double currentPosition = 0;
 double error = 0;
 double previous_error = goal;
 double kP = 0.27;
 double kI = 0.0005;
 double kD = 0.005;
 double integral = 0;
 double derivative = 0;

 target = degreeGoal;

 if (target < 0) {maxVelocity *= -1;}

 while(!goalMet){

   //currentPosition = (leftenc.get());
   error = target - currentPosition;

   if (std::abs(error) < 600){
     integral += error;
   }

   derivative = error - previous_error;
   previous_error = error;

   targetVelocity = kP*error + kI*integral + kD*derivative;

   if (abs(targetVelocity) > abs(maxVelocity)){
     targetVelocity = maxVelocity;
   }

   tlw.move_velocity(targetVelocity);
   blw.move_velocity(targetVelocity);
   trw.move_velocity(-targetVelocity);
   brw.move_velocity(-targetVelocity);

   if (std::abs(error) < 2){
     goalMet = true;
   }

   pros::delay(10);
 }

 brakeMotor();
 intakeL.move_velocity(0);
 intakeR.move_velocity(0);
}
void turn_PID(float targetdegree){
  leftenc.reset();
  rightenc.reset();
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
  currentpos = leftenc.get_value();
  error = degreeGoal - currentpos;

  if(std::abs(error) < 100){
    integral += error;
  }

  derivative = error - previous_error;
  previous_error = error;
  targetvelocity = kP*error + kI*integral + kD*derivative;

  if(targetvelocity > maxvelocity){
    targetvelocity = maxvelocity;

  }
  tlw.move_velocity(lefttarget);
  blw.move_velocity(lefttarget);
  trw.move_velocity(righttarget);
  brw.move_velocity(righttarget);
  /**slewRateControl(&tlw, lefttarget,DEFAULTSLEWRATEINCREMENT);
  slewRateControl(&blw, lefttarget,DEFAULTSLEWRATEINCREMENT);
  slewRateControl(&trw, righttarget,DEFAULTSLEWRATEINCREMENT);
  slewRateControl(&brw, righttarget,DEFAULTSLEWRATEINCREMENT);
**/


}
pros::delay(10);
}
brakeMotor();
}



void brakeMotor(){
  tlw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  blw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  trw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  brw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  tlw.move_velocity(0);
  trw.move_velocity(0);
  blw.move_velocity(0);
  brw.move_velocity(0);
}
void unbrakeMotor(){
  tlw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  blw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  trw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  brw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
