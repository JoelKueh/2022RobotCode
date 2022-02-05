#pragma once

#include "EncodedMotor.h"
#include "WiringDiagram.h"

#include <rev/CANSparkMax.h>

class Shooter {
 public:
  Shooter();

  EncodedMotor Flywheel;
  EncodedMotor Elevator;

  void InitSmartDashboard();
};
