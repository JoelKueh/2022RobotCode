#pragma once

#include <frc/Solenoid.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

class Intake {
 public:
  Intake();

  frc::Solenoid IntakePiston;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX IntakeMotor;

  bool out;

  void Out();
  void In();
  void Toggle();
  void Run(int speed);
};
