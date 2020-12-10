#include "config.hpp"

const int TLW = 1;
const int BLW = 2;
const int TRW = 3;
const int BRW = 4;

const int ROLLERB = 7;
const int ROLLERT = 9;
const int INTAKEL = 5;
const int INTAKER = 8;

const char LENC_TOP = 'E';
const char LENC_BOT = 'B';
const char RENC_TOP = 'C';
const char RENC_BOT = 'D';
const char COLORARM_LIMIT_SWITCH_PORT = 'F';
const char SIDEARM_LIMIT_SWITCH_PORT = 'G';

pros::Motor tlw (TLW,pros::E_MOTOR_GEARSET_18,true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor blw (BLW, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor trw (TRW, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor brw (BRW, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);


pros::Motor rollB (ROLLERB, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rollT (ROLLERT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intakeL (INTAKEL, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intakeR (INTAKER, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Controller master(CONTROLLER_MASTER);

pros::ADIEncoder leftenc (LENC_TOP, LENC_BOT, false);
pros::ADIEncoder rightenc (RENC_TOP, RENC_BOT, true);
pros::ADIDigitalIn colorlimit_switch (COLORARM_LIMIT_SWITCH_PORT);
pros::ADIDigitalIn sidelimit_switch (SIDEARM_LIMIT_SWITCH_PORT);
bool blueSide = false;
bool close = false;
int colorautonstate = 5;
int sideautonstate = 0;
bool colorbutton_unpressed = false;
bool sidebutton_unpressed = false;
