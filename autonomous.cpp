#include "main.h"
#include "config.hpp"
#include "auton_functions.h"




void autonomous() {




tlw.move_velocity(100);
blw.move_velocity(100);
pros::delay(1000);
rollB.move_velocity(500);
rollT.move_velocity(500);
pros::delay(750);
rollB.move_velocity(0);
rollT.move_velocity(0);
pros::delay(300);
base_PID(-15,40);
pros::delay(400);
base_PID(5,40);
pros::delay(200);
turn_PID(90);
pros::delay(800);
tlw.move_velocity(-100);
blw.move_velocity(-100);
trw.move_velocity(100);
brw.move_velocity(100);
pros::delay(750);
tlw.move_velocity(0);
blw.move_velocity(0);
trw.move_velocity(0);
brw.move_velocity(0);
intakeL.move_velocity(500);
intakeR.move_velocity(500);
pros::delay(300);
base_PID(95,80);//~114"
pros::delay(200);
intakeL.move_velocity(0);
intakeR.move_velocity(0);
pros::delay(500);
//intakeL.move_velocity(-600);
//intakeR.move_velocity(-600);
pros::delay(225);
intakeL.move_velocity(0);
intakeR.move_velocity(0);
turn_PID(90);
pros::delay(300);
tlw.move_velocity(-125);
blw.move_velocity(-125);
trw.move_velocity(125);
brw.move_velocity(125);
pros::delay(1000);
rollB.move_velocity(300);
pros::delay(175);
rollB.move_velocity(0);
intakeL.move_velocity(500);
intakeR.move_velocity(500);
base_PID(93,80);
pros::delay(300);
intakeL.move_velocity(0);
intakeR.move_velocity(0);
turn_PID(-35);
pros::delay(300);
intakeL.move_velocity(500);
intakeR.move_velocity(500);
pros::delay(300);
intakeL.move_velocity(0);
intakeR.move_velocity(0);
tlw.move_velocity(125);
trw.move_velocity(-125);
blw.move_velocity(125);
brw.move_velocity(-125);
pros::delay(1600);
rollT.move_velocity(600);
rollB.move_velocity(600);
pros::delay(1250);
tlw.move_velocity(0);
blw.move_velocity(0);
trw.move_velocity(0);
brw.move_velocity(0);
rollB.move_velocity(0);
rollT.move_velocity(0);
pros::delay(300);
base_PID(-20,60);
pros::delay(425);
turn_PID(133);//135
pros::delay(200);
intakeL.move_velocity(500);
intakeR.move_velocity(500);
base_PID(42,80);
pros::delay(300);
turn_PID(90);
pros::delay(500);
intakeL.move_velocity(0);
intakeR.move_velocity(0);
tlw.move_velocity(200);
blw.move_velocity(200);
trw.move_velocity(-200);
brw.move_velocity(-200);

pros::delay(1700);
intakeL.move_velocity(0);
intakeR.move_velocity(0);
base_PID(-10,90);
pros::delay(200);
tlw.move_velocity(150);
blw.move_velocity(150);
trw.move_velocity(-150);
brw.move_velocity(-150);
pros::delay(150);
trw.move_velocity(0);
brw.move_velocity(0);
intakeL.move_velocity(600);
intakeR.move_velocity(600);
rollT.move_velocity(600);
rollB.move_velocity(600);








/**

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
}**/

}


/**leftenc.reset();
rightenc.reset();
while(true){
	printf("Left %f\n",(double)leftenc.get_value());
	printf("Right %f\n",(double)rightenc.get_value());
	pros::delay(5);
}**/
