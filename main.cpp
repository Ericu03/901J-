#include "main.h"
#include "config.hpp"
#include "auton_functions.h"
#include "okapi/api.hpp"

#define E 2.71828182845904523536;
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
/*void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
*/
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


 //void initialize() {



//}
	//pros::c::lcd_print(0, "CurrentSide: %d", )
	//pros::lcd::set_text(1, "Hello PROS User!");

	//pros::lcd::register_btn1_cb(on_center_button);








/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {


	/*  if(sidelimit_switch.get_new_press() && sidebutton_unpressed){
			sideautonstate++;
			if(sideautonstate == 5){
				sideautonstate = 0;
				sidebutton_unpressed = false;
				}
		}

		if(!sidelimit_switch.get_new_press()){
			sidebutton_unpressed = true;
		}

	}*/
	}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */









void opcontrol() {



	tlw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	blw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	trw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	brw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);


	while (true) {
  	//std::cout <<"Left:" << leftenc.get_value();
		//std::cout <<"Right" << rightenc.get_value();
		double power = 220*master.get_analog(ANALOG_LEFT_Y)/127;
		double turn = 140*master.get_analog(ANALOG_RIGHT_X)/127;
		int l = (int)(pow(((power + turn)/200.0),2.0)*170.0);
	  int r = (int) (pow(((power - turn)/200.0),2.0)*170.0);




		if(power+turn < 0){
			l *= -1;
		}
		if(power-turn >0){
			r *=-1;
		}

		tlw.move_velocity(l);
		blw.move_velocity(l);
		trw.move_velocity(r);
		brw.move_velocity(r);


/**
	double power = master.get_analog(ANALOG_RIGHT_X)/127;
	double turn = master.get_analog(ANALOG_LEFT_Y)/127;

	int l = (pow(2.71828182845904523536, (power+turn))/0.3);
	int r = (pow(2.71828182845904523536, (power-turn))/0.3);

	if(power+turn <0){
		l *= -1;
		//power *= -1;
		//turn *= -1;
	}
	if(power-turn > 0){
		r *= -1;

	}
**/
/**
double power = master.get_analog(ANALOG_RIGHT_X)/127;
double turn = master.get_analog(ANALOG_LEFT_Y)/127;

int l = (int)(600/1+100(pow(2.71828182845904523536,((power+turn))));
int r = (int)(600/1+100(pow(2.71828182845904523536,(power-turn)));
**/



//brake

	if(master.get_digital(DIGITAL_X) != 0){
		tlw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		trw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		blw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		brw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		tlw.move_velocity(0);
		trw.move_velocity(0);
		blw.move_velocity(0);
		brw.move_velocity(0);

	}
	else{
		tlw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		trw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		blw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		brw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	}

	if(master.get_digital(DIGITAL_L1)){
			intakeL.move_voltage(14000);
			intakeR.move_voltage(14000);
		}
	else if(master.get_digital(DIGITAL_L2)){
			intakeL.move_voltage(-12000);
			intakeR.move_voltage(-12000);
		}
	else{
			intakeL.move_velocity(0);
			intakeR.move_velocity(0);
			intakeL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			intakeR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

		}
		if(master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_R2)){
					intakeL.move_voltage(12000);
					intakeR.move_voltage(12000);
					rollB.move_voltage(11000);
					pros::delay(8);
					if(!(master.get_digital(DIGITAL_L1)&&master.get_digital(DIGITAL_R2))){
						pros::delay(75);
						rollB.move_voltage(-10000);
						rollT.move_voltage(-10000);
						pros::delay(200);
						rollB.move_voltage(0);
						rollT.move_voltage(0);
					}
				}




/**if((master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_R2)) != true){
	rollB.move_voltage(-10000);
	rollT.move_voltage(-10000);
	pros::delay(100);
	rollB.move_voltage(0);
	rollT.move_voltage(0);
}**/


	else if(master.get_digital(DIGITAL_R1)){
			rollB.move_voltage(14000);
			rollT.move_voltage(12000);
		}
	else if(master.get_digital(DIGITAL_R2)){
			rollB.move_voltage(-10000);
			rollT.move_voltage(-10000);
		}
	else{
			rollB.move_velocity(0);
			rollT.move_velocity(0);
			rollB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			rollT.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

		}


pros::delay(10);
	}
}
