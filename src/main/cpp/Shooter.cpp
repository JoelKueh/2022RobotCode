// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Shooter.h"

#include "WiringDiagram.h"
#include "EncodedMotor.h"

#include <rev/CANSparkMax.h>

extern WiringDiagram MyWiringDiagram;

Shooter::Shooter() :
    Flywheel("Fly", MyWiringDiagram.c_Flywheel, rev::CANSparkMaxLowLevel::MotorType::kBrushless, FlywheelValues),
    Elevator("Ele", MyWiringDiagram.c_Elevator, rev::CANSparkMax::MotorType::kBrushless, 22, FlywheelValues)
    {
        // TODO: Put Flywheel and Elevator Values Here
    }

void Shooter::InitSmartDashboard()
{
    Flywheel.InitSmartDashboard();
    Elevator.InitSmartDashboard();
}

void Shooter::GetSmartDashboard()
{
    Flywheel.GetSmartDashboard();
    Elevator.GetSmartDashboard();
}