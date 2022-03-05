#pragma once

#include <string.h>
#include <rev/CANSparkMax.h>
#include <rev/SparkMaxPIDController.h>
#include <rev/SparkMaxRelativeEncoder.h>
#include <stdlib.h>
#include <frc/PowerDistribution.h>
#include "WiringDiagram.h"

extern WiringDiagram MyWiringDiagram;

class Flywheel {
 public:
  frc::PowerDistribution PDP {1, frc::PowerDistribution::ModuleType::kCTRE};

  rev::CANSparkMax Controller {MyWiringDiagram.c_Flywheel, rev::CANSparkMax::MotorType::kBrushless};
  
  rev::SparkMaxPIDController PID = Controller.GetPIDController();
  rev::SparkMaxRelativeEncoder Encoder = Controller.GetEncoder();

  std::string motorName = "Fly";

  struct PIDValues
  {
    double kP = 0.00015, kI = 0.000001, kD = 0.00005, kIz = 100, kFF = 0.000175, kMaxOutput = 1.0, kMinOutput = -1.0;

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

  double VoltageRatio = 12.0 / 5520.0;

  Flywheel();

  void PutSetpoint();
  void SetReference(double reference, rev::CANSparkMax::ControlType contorlType);
  void InitSmartDashboard();
  void PeriodicSmartDashboard();
  void GetSmartDashboard();
  void RunPIDFromSmartDashboard();
  void DeleteSmartDashboard();

  void VelocityFF(double setpoint);

  void InitLiveWindow();
  void StopMotor();

  bool InVelocityRange();
  bool InPositionRange();
};
