#pragma once

#include <frc/drive/MecanumDrive.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include "FrcPID.h"
#include "WiringDiagram.h"

class Drive : public frc::MecanumDrive {
 private:
  void InitPIDValues();

 public:
  Drive();

  FrcPID DrivePID;
  FrcPID::PIDValues DrivePIDValues;

  ctre::phoenix::motorcontrol::can::WPI_VictorSPX* frontLeft;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX* frontRight;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX* backLeft;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX* backRight;

  void RunPIDControl(double inputAngle);
  bool InRange();
};
