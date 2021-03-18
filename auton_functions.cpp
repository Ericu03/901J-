#include "main.h"
#include "config.hpp"
#include "auton_functions.h"

const double WHEEL_RADIUS = 1.625;
const int DEFAULTSLEWRATEINCREMENT = 10;
const float TICKS_PER_ROTATION =  360.0;
const double CIRCUMFERENCE = 2*M_PI*WHEEL_RADIUS;
const double DIAMETER = 3.25;
// Increase/Decrease motor speed towards target speed by increments and move, if targetVelocity is 0 move at same speed
void slewRateControl(pros::Motor *motor, int targetVelocity, int increment){
  int currentVelocity = motor->get_target_velocity();
  if (targetVelocity != 0){
    if (currentVelocity != targetVelocity){
      if (targetVelocity > currentVelocity){
        currentVelocity += increment;
      }
      else if (targetVelocity < currentVelocity){
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

void base_PID(double targetdistance, int velocity){//target distance in inches
leftenc.reset();//reset encoder values
rightenc.reset();

double degreegoal = (targetdistance /(1.625*2*M_PI))*TICKS_PER_ROTATION;
double target = 0.0;
int vel = velocity;
double goal = 0.0;
bool goalMet = false;
int targetVelocity = 0;
double currentPos;
double error;
double integral = 0.0;
double derivative = 0.0;
double previouserror = 0.0;
target = degreegoal;
 double revolutions = 0;
double kP = 0.27;
double kI = 0.0005;
double kD = 0.005;
  if(target < 0){
  vel *= -1;
  }

    while(!goalMet){
      revolutions = rightenc.get_value();
      currentPos = revolutions;
      error = degreegoal - currentPos;

      if(std::abs(error)< 1500){
        integral = integral + error;
      }



      derivative = error - previouserror;
      previouserror = error;

      targetVelocity = kP * error + kI* integral + kD * derivative;
      if(std::abs(targetVelocity) < std::abs(vel)){
        targetVelocity = vel;
      }
    slewRateControl(&tlw, targetVelocity, DEFAULTSLEWRATEINCREMENT);
    slewRateControl(&blw, targetVelocity, DEFAULTSLEWRATEINCREMENT);
    slewRateControl(&trw, targetVelocity, DEFAULTSLEWRATEINCREMENT);
    slewRateControl(&brw, targetVelocity, DEFAULTSLEWRATEINCREMENT);

      if(std::abs(error) < 2){
        goalMet = true;
      }
      pros::delay(10);
    }
    brakeMotor();

}



void turn_PID(float targetdegree){
  rightenc.reset();
  leftenc.reset();

 float turn_constant_right = 1.5;//2.4
 float turn_constant_left = 1.52;//2.42
 int maxVelocity = 70;
 double degreeGoal;
 if (targetdegree > 0){
   degreeGoal = targetdegree*turn_constant_right;
 } else {
   degreeGoal = targetdegree*turn_constant_left;
 }
 bool goalMet = false;
 int targetVelocity = 0;
 int leftTarget = 0;
 int rightTarget = 0;
 double currentPosition = 0;
 double error = 0;
 double previous_error = degreeGoal;
 double kP = 0.75;
 double kI = 0.0005;
 double kD = 0.001;
 double integral = 0;
 double derivative = 0;
 double revolutions = 0;
 if(targetdegree<0){maxVelocity *= -1;}


 while(!goalMet){
    revolutions = leftenc.get_value();
    //revolutions = rightenc.get_value();
    currentPosition = revolutions;


   error = degreeGoal - currentPosition;
   if (std::abs(error) < 100){
     integral += error;
   }

   derivative = error - previous_error;
   previous_error = error;

   targetVelocity = kP*error + kI*integral + kD*derivative;

   if (std::abs(targetVelocity) > std::abs(maxVelocity)){
     targetVelocity = maxVelocity;
   }


     leftTarget = targetVelocity;
     rightTarget = -1*targetVelocity;
     slewRateControl(&tlw, leftTarget, DEFAULTSLEWRATEINCREMENT);
     slewRateControl(&blw, leftTarget, DEFAULTSLEWRATEINCREMENT);
     slewRateControl(&trw, rightTarget, DEFAULTSLEWRATEINCREMENT);
     slewRateControl(&brw, rightTarget, DEFAULTSLEWRATEINCREMENT);


   if (std::abs(error) < 4){
     goalMet = true;
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
