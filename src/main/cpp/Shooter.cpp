// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Shooter.h"

Shooter::Shooter()
{
    ElevatorDistancePerPulse = 1/22;
    ElevatorMaxDistance = 25;
    InitPIDValues();
}

void Shooter::SetupElevatorEncoder()
{
    ElevatorEncoder.SetDistancePerPulse(ElevatorDistancePerPulse);
    while(!ElevatorLimit.Get())
    {
        ElevatorMotor.Set(-.15);
    }
    ElevatorEncoder.Reset();
}

void Shooter::InitSmartDashboard()
{
    Flywheel.InitSmartDashboard();
}

void Shooter::GetSmartDashboard()
{
    Flywheel.GetSmartDashboard();
}

void Shooter::SpinFlywheel(double RPM)
{
    Flywheel.SetReference(RPM, rev::CANSparkMax::ControlType::kVelocity);
}

void Shooter::StopFlywheel()
{
    Flywheel.StopMotor();
}

void Shooter::RunElevator(double limelightAngle)
{
    double elevatorSetpoint = limelightAngle;
    double distance = ElevatorEncoder.GetDistance();
    double elevatorPower = ElevatorPID.Calculate(distance, elevatorSetpoint);
    if(distance < 1 && elevatorPower < 0)
    {
        ElevatorMotor.Set(0);
    }
    else
    {
        ElevatorMotor.Set(elevatorPower);
    }

    if(distance > ElevatorMaxDistance && elevatorPower > 0)
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
    return Flywheel.InVelocityRange();
}

bool Shooter::ElevatorInRange()
{
    return ElevatorPID.AtSetpoint();
}

void Shooter::InitPIDValues()
{
    FlywheelValues.kP = 6e-5, FlywheelValues.kI = 1e-6, FlywheelValues.kD = 0, FlywheelValues.kIz = 0,
    FlywheelValues.kFF = 0.000015, FlywheelValues.kMaxOutput = 1.0, FlywheelValues.kMinOutput = -1.0;
    FlywheelValues.setpoint = 0;
    FlywheelValues.positionTolerance = 1, FlywheelValues.velocityTolerance = 1;

    ElevatorValues.kP = 6e-5, ElevatorValues.kI = 1e-6, ElevatorValues.kD = 0, ElevatorValues.kMaxOutput = 1.0, ElevatorValues.kMinOutput = -1.0;
    ElevatorValues.setpoint = 0;
    ElevatorValues.positionTolerance = 1, ElevatorValues.velocityTolerance = 1;
}