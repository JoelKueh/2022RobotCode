#pragma once

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/smartdashboard/SmartDashboard.h>

class Limelight {
 public:
  Limelight();

  void LEDOn();
  void LEDOff();
  double GetX();
  double GetY();
};
