// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

class WiringDiagram {
 public:
  WiringDiagram();

  const int c_Flywheel = 1; // CAN
  const int c_Elevator = 2; // CAN
  const int c_ElevatorA = 0; // PWM
  const int c_ElevatorB = 1; // PWM
  const int c_ElevatorLimit = 2; // PWM
  const int c_IndexMotor = 1; // CAN
  
  const int c_FrontLeftMotor = 3; // CAN
  const int c_FrontRightMotor = 2; // CAN
  const int c_BackLeftMotor = 1; // CAN
  const int c_BackRightMotor = 0; // CAN

  const int c_IntakeMotor = 0; // CAN
  const int c_PCMID = 0; // CAN
  const int c_IntakePiston = 0; // CAN

  const int c_HangerPiston = 1; // CAN

  const int c_Xbox = 0; // Xbox
};
