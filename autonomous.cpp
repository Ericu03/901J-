#include "main.h"
#include "config.hpp"
#include "auton_functions.h"




void autonomous() {
base_PID(10,90);
pros::delay(10);
turn_PID(45);


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
