// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Hanger.h"
#include "WiringDiagram.h"

extern WiringDiagram MyWiringDiagram;

Hanger::Hanger() : HangerPiston(frc::PneumaticsModuleType::CTREPCM, MyWiringDiagram.c_HangerPiston) {}

void Hanger::Raise()
{
    HangerPiston.Set(true);
}

void Hanger::Lower()
{
    HangerPiston.Set(false);
}