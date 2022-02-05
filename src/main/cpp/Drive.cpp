#include "Drive.h"

extern WiringDiagram MyWiringDiagram;

Drive::Drive() : MecanumDrive (*frontLeft, *backLeft, *frontRight, *backRight)
{
    frontLeft = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX (MyWiringDiagram.c_FrontLeftMotor);
    frontRight = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX (MyWiringDiagram.c_FrontRightMotor);
    backLeft = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX (MyWiringDiagram.c_BackLeftMotor);
    backRight = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX (MyWiringDiagram.c_BackRightMotor);

    frontLeft->SetInverted(true);
    frontRight->SetInverted(true);
    backLeft->SetInverted(true);
    backRight->SetInverted(true);
}