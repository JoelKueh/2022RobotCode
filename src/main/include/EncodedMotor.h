#pragma once

#include <string.h>
#include <rev/CANSparkMax.h>
#include "WiringDiagram.h"

class EncodedMotor : public rev::CANSparkMax {
 private:
  rev::SparkMaxPIDController PID;
  rev::SparkMaxRelativeEncoder Encoder;

  
  double kP = 6e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000015, kMaxOutput = 1.0, kMinOutput = -1.0;
  double P = 6e-5, I = 1e-6, D = 0, Iz = 0, FF = 0.000015, MaxOutput = 1.0, MinOutput = -1.0;
  const double MaxRPM = 5700;

  double SetPoint = 0;
  double LastSetPoint = 0;

  std::string motorName;

 public:
  EncodedMotor(char inputName[], int canID, rev::CANSparkMax::MotorType motorType);
  EncodedMotor(char inputName[], int canID, rev::CANSparkMax::MotorType motorType, int countsPerRev);

  void PutSetpoint();
  void InitSmartDashboardPID();
  void PeriodicSmartDashboardPID();
  void GetSmartDashboard();
  void RunPIDFromSmartDashboard();
};
