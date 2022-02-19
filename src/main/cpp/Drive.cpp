#include "Drive.h"


Drive::Drive()
{
    // InitPIDValues();
    // DrivePID("Drive", DrivePIDValues);

    frontLeft.SetInverted(true);
    frontRight.SetInverted(true);
    backLeft.SetInverted(true);
    // backRight.SetInverted(true);

    MyMecanumDrive = new frc::MecanumDrive(frontLeft, backLeft, frontRight, backRight);
}

void Drive::RunPIDControl(double inputAngle)
{
    MyMecanumDrive->DriveCartesian(0, 0, DrivePID.Calculate(inputAngle));
}

void Drive::RunDrive(double xboxLY, double xboxLX, double xboxRX)
{
    if(xboxLY < .15 && xboxLY > -.15) { xboxLY = 0; }
    if(xboxLX < .15 && xboxLX > -.15) { xboxLX = 0; }
    if(xboxRX < .15 && xboxRX > -.15) { xboxRX = 0; }

    MyMecanumDrive->DriveCartesian(xboxLY, -xboxLX, -xboxRX);
}

void Drive::InitPIDValues()
{
    DrivePIDValues.kP = 6e-5, DrivePIDValues.kI = 1e-6, DrivePIDValues.kD = 0, DrivePIDValues.kMaxOutput = 1.0, DrivePIDValues.kMinOutput = -1.0;
    DrivePIDValues.setpoint = 0;
    DrivePIDValues.positionTolerance = 1, DrivePIDValues.velocityTolerance = 1;
}

bool Drive::InRange()
{
    return DrivePID.AtSetpoint();
}

void Drive::InitSmartDashboard()
{
    DrivePID.InitSmartDashboard();
}

void Drive::GetSmartDashboard()
{
    DrivePID.GetSmartDashboard();
}

void Drive::PutSmartDashboard()
{
    DrivePID.PutSetpoint();
    DrivePID.PeriodicSmartDashboard();
}