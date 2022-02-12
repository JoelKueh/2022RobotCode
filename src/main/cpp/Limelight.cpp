// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Limelight.h"

Limelight::Limelight()
{
    LEDOff();
}

double Limelight::GetX()
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);
}

double Limelight::GetY()
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);
}

void Limelight::LEDOff()
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode",1);
}

void Limelight::LEDOn()
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode",3);
}