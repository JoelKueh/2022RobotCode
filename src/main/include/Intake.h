#pragma once

#include <frc/DoubleSolenoid.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include "WiringDiagram.h"

extern WiringDiagram MyWiringDiagram;

class Intake {
 public:
  Intake();

  frc::DoubleSolenoid IntakePiston {frc::PneumaticsModuleType::CTREPCM, MyWiringDiagram.c_IntakePistonIn, MyWiringDiagram.c_IntakePistonOut};
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX IntakeMotor {MyWiringDiagram.c_IntakeMotor};

  bool out;

  void Out();
  void In();
  void Toggle();
  void Init();
  void Run(double speed);
};
