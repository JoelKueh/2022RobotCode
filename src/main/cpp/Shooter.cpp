// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Shooter.h"

#include <rev/CANSparkMax.h>

#include "WiringDiagram.h"
#include "EncodedMotor.h"


extern WiringDiagram MyWiringDiagram;

Shooter::Shooter() :
    Flywheel(MyWiringDiagram.c_Flywheel, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
    Elevator(MyWiringDiagram.c_Elevator, rev::CANSparkMax::MotorType::kBrushless, 22) {}

void Shooter::InitSmartDashboard()
{
    Flywheel.InitSmartDashboardPID();
    Elevator.InitSmartDashboardPID();
}