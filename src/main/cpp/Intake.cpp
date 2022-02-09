#include "Intake.h"
#include "WiringDiagram.h"

extern WiringDiagram MyWiringDiagram;


Intake::Intake() :
    IntakePiston(frc::PneumaticsModuleType::CTREPCM, MyWiringDiagram.c_IntakePiston),
    IntakeMotor(MyWiringDiagram.c_IntakeMotor) {}

void Intake::Out()
{
    IntakePiston.Set(true);
}

void Intake::In()
{
    IntakePiston.Set(false);
}

void Intake::Run(int speed)
{
    IntakeMotor.Set(speed);
}