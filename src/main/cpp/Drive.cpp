#include "Drive.h"

extern WiringDiagram MyWiringDiagram;

Drive::Drive() : MecanumDrive (*frontLeft, *backLeft, *frontRight, *backRight), DrivePID("Drive", DrivePIDValues)
{
    InitPIDValues();

    frontLeft = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX (MyWiringDiagram.c_FrontLeftMotor);
    frontRight = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX (MyWiringDiagram.c_FrontRightMotor);
    backLeft = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX (MyWiringDiagram.c_BackLeftMotor);
    backRight = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX (MyWiringDiagram.c_BackRightMotor);

    frontLeft->SetInverted(true);
    frontRight->SetInverted(true);
    backLeft->SetInverted(true);
    backRight->SetInverted(true);
}

void Drive::RunPIDControl()
{

}

void Drive::InitPIDValues()
{
    DrivePIDValues.kP = 6e-5, DrivePIDValues.kI = 1e-6, DrivePIDValues.kD = 0, DrivePIDValues.kMaxOutput = 1.0, DrivePIDValues.kMinOutput = -1.0;
    DrivePIDValues.setpoint = 0;
    DrivePIDValues.positionTolerance = 1, DrivePIDValues.velocityTolerance = 1;
}