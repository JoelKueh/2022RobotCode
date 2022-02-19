#include "Intake.h"

Intake::Intake()
{
    out = false;
}

void Intake::Out()
{
    IntakePiston.Set(true);
}

void Intake::In()
{
    IntakePiston.Set(false);
}

void Intake::Toggle()
{
    if(out)
    {
        In();
        out = false;
    }
    else
    {
        Out();
        out = true;
    }
}

void Intake::Run(int speed)
{
    IntakeMotor.Set(speed);
}