#pragma once

#include <frc/Solenoid.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

class Intake {
 public:
  Intake();

  frc::Solenoid IntakePiston;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX IntakeMotor;

  void Out();
  void In();
  void Run(int speed);
};
