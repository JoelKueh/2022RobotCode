// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/DoubleSolenoid.h>
#include "WiringDiagram.h"

extern WiringDiagram MyWiringDiagram;

class Hanger {
 public:
  Hanger();

  void Raise();
  void Lower();
  void Toggle();
  void Init();

  bool out;

  frc::DoubleSolenoid HangerPiston {frc::PneumaticsModuleType::CTREPCM, MyWiringDiagram.c_HangerPistonIn, MyWiringDiagram.c_HangarPistonOut};
};
