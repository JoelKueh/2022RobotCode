// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Hanger.h"

Hanger::Hanger()
{
    out = false;
}

void Hanger::Raise()
{
    HangerPiston.Set(true);
}

void Hanger::Lower()
{
    HangerPiston.Set(false);
}

void Hanger::Toggle()
{
    if (out)
    {
        Raise();
    }
    else
    {
        Lower();
    }
}