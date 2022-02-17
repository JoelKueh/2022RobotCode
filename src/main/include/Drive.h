#pragma once

#include <frc/drive/MecanumDrive.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include "FrcPID.h"
#include "WiringDiagram.h"

class Drive : public frc::MecanumDrive {
 private:
  void InitPIDValues();

 public:
  Drive();


  FrcPID DrivePID;
  FrcPID::PIDValues DrivePIDValues;

  ctre::phoenix::motorcontrol::can::TalonSRX frontLeft {3};
  ctre::phoenix::motorcontrol::can::TalonSRX frontRight {4};
  ctre::phoenix::motorcontrol::can::TalonSRX backLeft {1};
  ctre::phoenix::motorcontrol::can::TalonSRX backRight {0};

  void RunPIDControl(double inputAngle);
  bool InRange();
};
