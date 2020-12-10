#include "main.h"
#include "config.hpp"
#include "auton_functions.h"

void blueleft(){
base_PID(10, 30);
pros::delay(300);
base_PID(0,0);
//turn_PID(90);


tlw.move_velocity(0);
trw.move_velocity(0);
}
void blueright(){
	intakeL.move_velocity(600);
	intakeR.move_velocity(600);
	base_PID(5.0,50);
	pros::delay(300);
	turn_PID(45);
	pros::delay(100);
	base_PID(3.0,30);
	intakeL.move_velocity(400);
	intakeR.move_velocity(400);
	rollT.move_velocity(550);
	rollB.move_velocity(550);
	pros::delay(50);
}

void redleft(){
intakeL.move_velocity(600);
intakeR.move_velocity(600);
pros::delay(500);
intakeL.move_velocity(0);
intakeR.move_velocity(0);
}

void redright(){
newturn_PID(90);

pros::delay(10);
}

void autonomous() {
intakeL.move_velocity(100);
if(sideautonstate == 2 && colorautonstate ==2){
	blueleft();
}
if(sideautonstate == 1 && colorautonstate == 2){
	blueright();
}
if(sideautonstate ==  2 && colorautonstate == 1){
	redleft();

}
if(sideautonstate == 1 && colorautonstate == 1){
	redright();
}

}


/**leftenc.reset();
rightenc.reset();
while(true){
	printf("Left %f\n",(double)leftenc.get_value());
	printf("Right %f\n",(double)rightenc.get_value());
	pros::delay(5);
}**/
