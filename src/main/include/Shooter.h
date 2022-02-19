#pragma once

#include "EncodedMotor.h"
#include "WiringDiagram.h"
#include "FrcPID.h"

#include <rev/CANSparkMax.h>
#include <frc/Encoder.h>
#include <frc/DigitalInput.h>

#include "WiringDiagram.h"

extern WiringDiagram MyWiringDiagram;

class Shooter {
 public:
  Shooter();
  
  EncodedMotor::PIDValues FlywheelValues
  {
    FlywheelValues.kP = 6e-5, FlywheelValues.kI = 1e-6, FlywheelValues.kD = 0, FlywheelValues.kIz = 0,
    FlywheelValues.kFF = 0.000015, FlywheelValues.kMaxOutput = 1.0, FlywheelValues.kMinOutput = -1.0,
    FlywheelValues.setpoint = 0,
    FlywheelValues.positionTolerance = 1, FlywheelValues.velocityTolerance = 1
  };
  EncodedMotor Flywheel {"Fly", MyWiringDiagram.c_Flywheel, rev::CANSparkMax::MotorType::kBrushless, FlywheelValues};

  FrcPID::PIDValues ElevatorValues
  { 
    ElevatorValues.kP = 6e-5, ElevatorValues.kI = 1e-6, ElevatorValues.kD = 0, ElevatorValues.kMaxOutput = 1.0, ElevatorValues.kMinOutput = -1.0,
    ElevatorValues.setpoint = 0,
    ElevatorValues.positionTolerance = 1, ElevatorValues.velocityTolerance = 1
  };
  FrcPID ElevatorPID {"Ele", ElevatorValues};

  rev::CANSparkMax ElevatorMotor {MyWiringDiagram.c_Elevator, rev::CANSparkMax::MotorType::kBrushed};
  frc::Encoder ElevatorEncoder {MyWiringDiagram.c_ElevatorA, MyWiringDiagram.c_ElevatorB};
  frc::DigitalInput ElevatorLimit {MyWiringDiagram.c_ElevatorLimit};
  double ElevatorDistancePerPulse;
  double ElevatorMaxDistance;

  void InitPIDValues();
  void InitSmartDashboard();
  void GetSmartDashboard();
  void SpinFlywheel(double RPM);
  void RunElevator(double limelightAngle);
  void SetupElevatorEncoder();
  void StopFlywheel();
  void StopElevator();

  bool FlywheelInRange();
  bool ElevatorInRange();
};
