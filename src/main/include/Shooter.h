#pragma once

#include "EncodedMotor.h"
#include "WiringDiagram.h"

#include <rev/CANSparkMax.h>

class Shooter {
 public:
  Shooter();

  EncodedMotor Flywheel;
  EncodedMotor::PIDValues FlywheelValues;

  EncodedMotor Elevator;
  EncodedMotor::PIDValues ElevatorValues;

  void InitSmartDashboard();
  void GetSmartDashboard();
};
