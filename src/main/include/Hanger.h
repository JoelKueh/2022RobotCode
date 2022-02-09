// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Solenoid.h>

class Hanger {
 public:
  Hanger();

  void Raise();
  void Lower();

  frc::Solenoid HangerPiston;
};
