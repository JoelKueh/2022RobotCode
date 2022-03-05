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
    double output = DrivePID.ClampCalculate(inputAngle);
    if(output > 0)
    {
        output = output + .05;
    }
    else if(output < 0)
    {
        output = output - .05;
    }

    MyMecanumDrive->DriveCartesian(0, 0, output);
}

void Drive::RunDrive(double xboxLY, double xboxLX, double xboxRX)
{
    if(xboxLY < .15 && xboxLY > -.15) { xboxLY = 0; }
    if(xboxLX < .15 && xboxLX > -.15) { xboxLX = 0; }
    if(xboxRX < .15 && xboxRX > -.15) { xboxRX = 0; }

    MyMecanumDrive->DriveCartesian(xboxLY, -xboxLX, -xboxRX);
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