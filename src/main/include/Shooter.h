#pragma once

#include "EncodedMotor.h"
#include "WiringDiagram.h"
#include "FrcPID.h"

#include <rev/CANSparkMax.h>
#include <frc/Encoder.h>
#include <frc/DigitalInput.h>

class Shooter {
 public:
  Shooter();

  EncodedMotor Flywheel;
  EncodedMotor::PIDValues FlywheelValues;

  FrcPID ElevatorPID;
  FrcPID::PIDValues ElevatorValues;

  rev::CANSparkMax ElevatorMotor;
  frc::Encoder ElevatorEncoder;
  frc::DigitalInput ElevatorLimit;
  double ElevatorDistancePerPulse;
  double ElevatorMaxDistance;


  void InitPIDValues();
  void InitSmartDashboard();
  void GetSmartDashboard();
  void SpinFlywheel(double RPM);
  void RunElevator(double limelightAngle);
  void SetupElevatorEncoder();

  bool FlywheelInRange();
  bool ElevatorInRange();
};
