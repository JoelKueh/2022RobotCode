#include "Intake.h"

Intake::Intake()
{
    out = false;
}

// void Intake::Out()
// {
//     IntakePiston.Set(true);
// }

// void Intake::In()
// {
//     IntakePiston.Set(false);
// }

void Intake::Init()
{
    IntakeMotor.Set(1);
    IntakePiston.Set(frc::DoubleSolenoid::kReverse);
}

void Intake::Toggle()
{
    // if(out)
    // {
    //     In();
    //     out = false;
    // }
    // else
    // {
    //     Out();
    //     out = true;
    // }

    IntakePiston.Toggle();
}

void Intake::Run(double speed)
{
    IntakeMotor.Set(speed);
}