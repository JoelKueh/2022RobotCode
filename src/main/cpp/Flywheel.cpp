#include "Flywheel.h"

#include <frc/smartdashboard/SmartDashboard.h>

/**
 * Constructs a SparkMax Flywheel
 * */
Flywheel::Flywheel() = default;

void Flywheel::SetReference(double reference, rev::CANSparkMax::ControlType controlType)
{
    PID.SetReference(reference, controlType);

    myPIDValues.setpoint = reference;
    inputPIDValues.setpoint = reference;
}

/**
 * This function sends the PID values to the smartdashboard
 * */
void Flywheel::InitSmartDashboard()
{
    frc::SmartDashboard::PutNumber(motorName + " P Gain", myPIDValues.kP);
    frc::SmartDashboard::PutNumber(motorName + " I Gain", myPIDValues.kI);
    frc::SmartDashboard::PutNumber(motorName + " D Gain", myPIDValues.kD);
    frc::SmartDashboard::PutNumber(motorName + " I Zone", myPIDValues.kIz);
    frc::SmartDashboard::PutNumber(motorName + " Feed Forward", myPIDValues.kFF);
    frc::SmartDashboard::PutNumber(motorName + " Max Output", myPIDValues.kMaxOutput);
    frc::SmartDashboard::PutNumber(motorName + " Min Output", myPIDValues.kMinOutput);
 
    frc::SmartDashboard::PutNumber(motorName + " SetPoint", myPIDValues.setpoint);
}

/**
 * Sends the Velocity to SmartDashboard
 * */
void Flywheel::PeriodicSmartDashboard()
{
    frc::SmartDashboard::PutNumber(motorName + " Velocity", Encoder.GetVelocity());
}

void Flywheel::PutSetpoint()
{
    frc::SmartDashboard::PutNumber(motorName + " SetPoint", myPIDValues.setpoint);
}

/**
 * Takes the values from the SmartDashboard and puts them into variables
 * */
void Flywheel::GetSmartDashboard()
{
    inputPIDValues.kP = frc::SmartDashboard::GetNumber(motorName + " P Gain", 0);
    inputPIDValues.kI = frc::SmartDashboard::GetNumber(motorName + " I Gain", 0);
    inputPIDValues.kD = frc::SmartDashboard::GetNumber(motorName + " D Gain", 0);
    inputPIDValues.kIz = frc::SmartDashboard::GetNumber(motorName + " I Zone", 0);
    inputPIDValues.kFF = frc::SmartDashboard::GetNumber(motorName + " Feed Forward", 0);
    inputPIDValues.kMaxOutput = frc::SmartDashboard::GetNumber(motorName + " Max Output", 0);
    inputPIDValues.kMinOutput = frc::SmartDashboard::GetNumber(motorName + " Min Output", 0);

    if(inputPIDValues.kP != myPIDValues.kP) { myPIDValues.kP = inputPIDValues.kP; PID.SetP(myPIDValues.kP); }
    if(inputPIDValues.kI != myPIDValues.kI) { myPIDValues.kI = inputPIDValues.kI; PID.SetI(myPIDValues.kI); }
    if(inputPIDValues.kD != myPIDValues.kD) { myPIDValues.kD = inputPIDValues.kD; PID.SetD(myPIDValues.kD); }
    if(inputPIDValues.kIz != myPIDValues.kIz) { myPIDValues.kIz = inputPIDValues.kIz; PID.SetIZone(myPIDValues.kIz); }
    if(inputPIDValues.kMaxOutput != myPIDValues.kMaxOutput || inputPIDValues.kMinOutput != myPIDValues.kMinOutput)
    {
        myPIDValues.kMaxOutput = inputPIDValues.kMaxOutput;
        myPIDValues.kMinOutput = inputPIDValues.kMinOutput;
        PID.SetOutputRange(myPIDValues.kMinOutput, myPIDValues.kMaxOutput);
    }
}

/**
 * Runs the PID from values taken from Smart Dashboard
 * */
void Flywheel::RunPIDFromSmartDashboard()
{
    inputPIDValues.setpoint = frc::SmartDashboard::GetNumber(motorName + " SetPoint", 0);
    if(inputPIDValues.setpoint != myPIDValues.setpoint) { myPIDValues.setpoint = inputPIDValues.setpoint; PID.SetReference(myPIDValues.setpoint, rev::ControlType::kVelocity); }
}

bool Flywheel::InVelocityRange()
{
    if(Encoder.GetVelocity() < myPIDValues.setpoint + myPIDValues.velocityTolerance && Encoder.GetVelocity() > myPIDValues.setpoint - myPIDValues.velocityTolerance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Flywheel::InPositionRange()
{
    if(Encoder.GetPosition() < myPIDValues.setpoint + myPIDValues.positionTolerance && Encoder.GetVelocity() > myPIDValues.setpoint - myPIDValues.positionTolerance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Flywheel::StopMotor()
{
    Controller.StopMotor();
}

void Flywheel::DeleteSmartDashboard()
{
    // frc::SmartDashboard::Delete(motorName + " P Gain");
    // frc::SmartDashboard::Delete(motorName + " I Gain");
    // frc::SmartDashboard::Delete(motorName + " D Gain");
    // frc::SmartDashboard::Delete(motorName + " I Zone");
    // frc::SmartDashboard::Delete(motorName + " Feed Forward");
    // frc::SmartDashboard::Delete(motorName + " Max Output");
    // frc::SmartDashboard::Delete(motorName + " Min Output");
 
    // frc::SmartDashboard::Delete(motorName + " SetPoint");
    frc::SmartDashboard::Delete(motorName + " Velocity");
}