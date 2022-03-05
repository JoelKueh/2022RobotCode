// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Shooter.h"

#include <iostream>

Shooter::Shooter()
{
    ElevatorDistancePerPulse = -1.0/22.0;
    ElevatorMaxDistance = 45.0;
    ElevatorEncoder.SetDistancePerPulse(ElevatorDistancePerPulse);
    InitPIDValues();
}

void Shooter::ZeroElevator()
{
    while(ElevatorLimit.Get())
    {
        ElevatorMotor.Set(-1);
    }
    ElevatorMotor.Set(0);
    ElevatorEncoder.Reset();
}

void Shooter::InitSmartDashboard()
{
    MyFlywheel.InitSmartDashboard();
    ElevatorPID.InitSmartDashboard();
}

void Shooter::GetSmartDashboard()
{
    MyFlywheel.GetSmartDashboard();
    ElevatorPID.GetSmartDashboard();
}

void Shooter::SpinFlywheel(double RPM)
{
    MyFlywheel.SetReference(RPM, rev::CANSparkMax::ControlType::kVelocity);
}

void Shooter::StopFlywheel()
{
    MyFlywheel.StopMotor();
}

void Shooter::RunElevator(double limelightAngle)
{
    double elevatorSetpoint = limelightAngle;
    double distance = ElevatorEncoder.GetDistance();
    double elevatorPower = ElevatorPID.Calculate(distance, elevatorSetpoint);

    if(!ElevatorLimit.Get() && elevatorPower < 0)
    {
        ElevatorMotor.Set(0);
    }
    else if(distance > ElevatorMaxDistance && elevatorPower > 0)
    {
        ElevatorMotor.Set(0);
    }
    else
    {
        ElevatorMotor.Set(elevatorPower);
    }
}

void Shooter::StopElevator()
{
    ElevatorMotor.Set(0);
}

bool Shooter::FlywheelInRange()
{
    return MyFlywheel.InVelocityRange();
}

bool Shooter::ElevatorInRange()
{
    return ElevatorPID.AtSetpoint();
}

void Shooter::InitPIDValues()
{
    // MyFlywheelValues.kP = 6e-5, MyFlywheelValues.kI = 1e-6, MyFlywheelValues.kD = 0, MyFlywheelValues.kIz = 0,
    // MyFlywheelValues.kFF = 0.000015, MyFlywheelValues.kMaxOutput = 1.0, MyFlywheelValues.kMinOutput = -1.0;
    // MyFlywheelValues.setpoint = 0;
    // MyFlywheelValues.positionTolerance = 1, MyFlywheelValues.velocityTolerance = 1;

    ElevatorValues.kP = 6e-5, ElevatorValues.kI = 1e-6, ElevatorValues.kD = 0, ElevatorValues.kMaxOutput = 1.0, ElevatorValues.kMinOutput = -1.0;
    ElevatorValues.setpoint = 0;
    ElevatorValues.positionTolerance = 1, ElevatorValues.velocityTolerance = 1;
}

void Shooter::PutSmartDashboard()
{
    // ElevatorPID.PutSetpoint();
    frc::SmartDashboard::PutNumber("EleLimit", ElevatorLimit.Get());
    frc::SmartDashboard::PutNumber("Ele Distance", ElevatorEncoder.GetDistance());
    // MyFlywheel.PutSetpoint();

    ElevatorPID.PeriodicSmartDashboard();
    MyFlywheel.PeriodicSmartDashboard();
}

void Shooter::FlywheelFF(double RPM)
{
    MyFlywheel.VelocityFF(RPM);
}

void Shooter::DeleteSmartDashboard()
{
    MyFlywheel.DeleteSmartDashboard();
}

void Shooter::FlywheelDashControl()
{
    MyFlywheel.RunPIDFromSmartDashboard();
}

void Shooter::SetElevator(double power)
{
    if(!ElevatorLimit.Get() && power < 0)
    {
        ElevatorMotor.Set(0);
    }
    else if(ElevatorEncoder.GetDistance() > 45.0 && power > 0)
    {
        ElevatorMotor.Set(0);
    }
    else
    {
        ElevatorMotor.Set(power);
    }
    frc::SmartDashboard::PutNumber("Ele Distance", ElevatorEncoder.GetDistance());
}