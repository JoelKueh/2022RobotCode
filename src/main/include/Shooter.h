#pragma once

#include "WiringDiagram.h"
#include "Flywheel.h"
#include "FrcPID.h"

#include <rev/CANSparkMax.h>
#include <frc/Encoder.h>
#include <frc/DigitalInput.h>

extern WiringDiagram MyWiringDiagram;

class Shooter {
 public:
  Shooter();
  
  // EncodedMotor::PIDValues MyFlywheelValues
  // {
  //   MyFlywheelValues.kP = 6e-5, MyFlywheelValues.kI = 1e-6, MyFlywheelValues.kD = 0, MyFlywheelValues.kIz = 0,
  //   MyFlywheelValues.kFF = 0.000015, MyFlywheelValues.kMaxOutput = 1.0, MyFlywheelValues.kMinOutput = -1.0,
  //   MyFlywheelValues.setpoint = 0,
  //   MyFlywheelValues.positionTolerance = 1, MyFlywheelValues.velocityTolerance = 1
  // };
  // EncodedMotor MyFlywheel {"Fly", MyWiringDiagram.c_MyFlywheel, rev::CANSparkMax::MotorType::kBrushless, MyFlywheelValues};

  Flywheel MyFlywheel;

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
  void PutSmartDashboard();
  void DeleteSmartDashboard();
  bool FlywheelInRange();
  bool ElevatorInRange();
};
