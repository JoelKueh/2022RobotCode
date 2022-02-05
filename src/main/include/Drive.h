#pragma once

#include <frc/drive/MecanumDrive.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include "WiringDiagram.h"

class Drive : public frc::MecanumDrive {
 public:
  Drive();

  ctre::phoenix::motorcontrol::can::WPI_VictorSPX* frontLeft;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX* frontRight;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX* backLeft;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX* backRight;

};
