// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDCommand.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <string.h>

class FrcPID : public frc2::PIDController {
 public:

  std::string PIDName;

  struct PIDValues
  {
    double kP = 6e-5, kI = 1e-6, kD = 0, kMaxOutput = 1.0, kMinOutput = -1.0;
    double setpoint = 0;
    double positionTolerance = 1, velocityTolerance = 1;
  };

  PIDValues inputPIDValues;
  PIDValues myPIDValues;
  
  FrcPID(std::string name, PIDValues inputValues);

  void PutSetpoint();
  void InitSmartDashboard();
  void PeriodicSmartDashboard();
  void GetSmartDashboard();
  void RunPIDFromSmartDashboard();
  double ClampCalculate(double input);
  double ClampCalculateSetpoint(double input, double inputSetpoint);
};
