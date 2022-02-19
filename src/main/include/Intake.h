#pragma once

#include <frc/Solenoid.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include "WiringDiagram.h"

extern WiringDiagram MyWiringDiagram;

class Intake {
 public:
  Intake();

  frc::Solenoid IntakePiston {frc::PneumaticsModuleType::CTREPCM, MyWiringDiagram.c_IntakePiston};
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX IntakeMotor {MyWiringDiagram.c_IntakeMotor};

  

  bool out;

  void Out();
  void In();
  void Toggle();
  void Run(int speed);
};
