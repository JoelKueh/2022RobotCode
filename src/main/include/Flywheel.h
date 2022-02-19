#pragma once

#include <string.h>
#include <rev/CANSparkMax.h>
#include <rev/SparkMaxPIDController.h>
#include <rev/SparkMaxRelativeEncoder.h>
#include <stdlib.h>
#include "WiringDiagram.h"

extern WiringDiagram MyWiringDiagram;

class Flywheel {
 public:
  rev::CANSparkMax Controller {MyWiringDiagram.c_Flywheel, rev::CANSparkMax::MotorType::kBrushless};
  
  rev::SparkMaxPIDController PID = Controller.GetPIDController();
  rev::SparkMaxRelativeEncoder Encoder = Controller.GetEncoder();

  std::string motorName = "Fly";
  
  struct PIDValues
  {
    double kP = 6e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000015, kMaxOutput = 1.0, kMinOutput = -1.0;

    double setpoint = 0;
    double positionTolerance = 1, velocityTolerance = 100;
  };

  PIDValues myPIDValues;
  PIDValues inputPIDValues;

  // double kP = 6e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000015, kMaxOutput = 1.0, kMinOutput = -1.0;
  // double P = 6e-5, I = 1e-6, D = 0, Iz = 0, FF = 0.000015, MaxOutput = 1.0, MinOutput = -1.0;
  // const double MaxRPM = 5700;

  // double SetPoint = 0;
  // double LastSetPoint = 0;

  Flywheel();

  void PutSetpoint();
  void SetReference(double reference, rev::CANSparkMax::ControlType contorlType);
  void InitSmartDashboard();
  void PeriodicSmartDashboard();
  void GetSmartDashboard();
  void RunPIDFromSmartDashboard();
  void DeleteSmartDashboard();

  void InitLiveWindow();
  void StopMotor();

  bool InVelocityRange();
  bool InPositionRange();
};
