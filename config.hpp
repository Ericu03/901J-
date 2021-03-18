#include "main.h"

extern const int TLW;
extern const int BLW;
extern const int TRW;
extern const int BRW;

extern const int INTAKEL;
extern const int INTAKER;
extern const int ROLLB;
extern const int ROLLT;

extern pros::Controller master;
extern pros::Motor tlw;
extern pros::Motor blw;
extern pros::Motor trw;
extern pros::Motor brw;


extern pros::Motor intakeL;
extern pros::Motor intakeR;
extern pros::Motor rollB;
extern pros::Motor rollT;

extern pros::ADIEncoder leftenc;
extern pros::ADIEncoder rightenc;
extern pros::ADIDigitalIn colorlimit_switch;
extern pros::ADIDigitalIn sidelimit_switch;
extern bool blueSide;
extern bool close;
extern int colorautonstate;
extern int sideautonstate;
extern bool colorbutton_unpressed;
extern bool sidebutton_unpressed;
