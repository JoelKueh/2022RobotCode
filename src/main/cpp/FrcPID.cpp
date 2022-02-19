#include "FrcPID.h"

FrcPID::FrcPID(std::string name, PIDValues inputValues) : PIDController(myPIDValues.kP, myPIDValues.kI, myPIDValues.kD)
{
    PIDName = name;
    inputPIDValues = inputValues;
    myPIDValues = inputValues;

    SetTolerance(myPIDValues.positionTolerance, myPIDValues.velocityTolerance);
}

void FrcPID::InitSmartDashboard()
{
    frc::SmartDashboard::PutNumber(PIDName + " P Gain", myPIDValues.kP);
    frc::SmartDashboard::PutNumber(PIDName + " I Gain", myPIDValues.kI);
    frc::SmartDashboard::PutNumber(PIDName + " D Gain", myPIDValues.kD);
    frc::SmartDashboard::PutNumber(PIDName + " Max Output", myPIDValues.kMaxOutput);
    frc::SmartDashboard::PutNumber(PIDName + " Min Output", myPIDValues.kMinOutput);

    frc::SmartDashboard::PutNumber(PIDName + " SetPoint", myPIDValues.setpoint);
    frc::SmartDashboard::PutNumber(PIDName + " P_Tolerance", myPIDValues.positionTolerance);
    frc::SmartDashboard::PutNumber(PIDName + " V_Toleracne", myPIDValues.velocityTolerance);
}

/**
 * Sends the Velocity to SmartDashboard
 * */
void FrcPID::PeriodicSmartDashboard()
{
    
}

void FrcPID::PutSetpoint()
{
    frc::SmartDashboard::PutNumber(PIDName + " SetPoint", myPIDValues.setpoint);
}

/**
 * Takes the values from the SmartDashboard and puts them into variables
 * */
void FrcPID::GetSmartDashboard()
{
    inputPIDValues.kP = frc::SmartDashboard::GetNumber(PIDName + " P Gain", 0);
    inputPIDValues.kI = frc::SmartDashboard::GetNumber(PIDName + " I Gain", 0);
    inputPIDValues.kD = frc::SmartDashboard::GetNumber(PIDName + " D Gain", 0);
    inputPIDValues.kMaxOutput = frc::SmartDashboard::GetNumber(PIDName + " Max Output", 0);
    inputPIDValues.kMinOutput = frc::SmartDashboard::GetNumber(PIDName + " Min Output", 0);

    if(inputPIDValues.kP != myPIDValues.kP) { myPIDValues.kP = inputPIDValues.kP; SetP(myPIDValues.kP); }
    if(inputPIDValues.kI != myPIDValues.kI) { myPIDValues.kI = inputPIDValues.kI; SetI(myPIDValues.kI); }
    if(inputPIDValues.kD != myPIDValues.kD) { myPIDValues.kD = inputPIDValues.kD; SetD(myPIDValues.kD); }
    if(inputPIDValues.kMaxOutput != myPIDValues.kMaxOutput || inputPIDValues.kMinOutput != myPIDValues.kMinOutput)
    {
        myPIDValues.kMaxOutput = inputPIDValues.kMaxOutput;
        myPIDValues.kMinOutput = inputPIDValues.kMinOutput;
    }
}

/**
 * Runs the PID from values taken from Smart Dashboard
 * */
void FrcPID::RunPIDFromSmartDashboard()
{
    inputPIDValues.setpoint = frc::SmartDashboard::GetNumber(PIDName + " Setpoint", 0);
    if(myPIDValues.setpoint != inputPIDValues.setpoint) { myPIDValues.setpoint = inputPIDValues.setpoint; SetSetpoint(myPIDValues.setpoint); }
}

double FrcPID::ClampCalcualte(double input)
{
    double output = Calculate(input);
    if(output > myPIDValues.kMaxOutput) { output = myPIDValues.kMaxOutput; }
    if(output < myPIDValues.kMinOutput) { output = myPIDValues.kMinOutput; }
    return output;
}

double FrcPID::ClampCalculateSetpoint(double input, double inputSetpoint)
{
    myPIDValues.setpoint = inputSetpoint;
    frc::SmartDashboard::PutNumber(PIDName + " Setpoint", myPIDValues.setpoint);

    double output = Calculate(input, myPIDValues.setpoint);
    if(output > myPIDValues.kMaxOutput) { output = myPIDValues.kMaxOutput; }
    if(output < myPIDValues.kMinOutput) { output = myPIDValues.kMinOutput; }
    return output;
}