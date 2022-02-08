#include "EncodedMotor.h"

#include "WiringDiagram.h"
#include <frc/smartdashboard/SmartDashboard.h>

/**
 * Constructs a SparkMax EncodedMotor
 * */
EncodedMotor::EncodedMotor(char inputName[], int canID, MotorType motorType) :
    rev::CANSparkMax(canID, motorType),
    PID (GetPIDController()),
    Encoder (GetEncoder())
{
    motorName = inputName;
}

EncodedMotor::EncodedMotor(char inputName[], int canID, MotorType motorType, int countsPerRev) :
    rev::CANSparkMax(canID, motorType),
    PID (GetPIDController()),
    Encoder (GetEncoder(rev::SparkMaxRelativeEncoder::Type::kQuadrature, countsPerRev))
{
    motorName = inputName;
}

/**
 * This function sends the PID values to the smartdashboard
 * */
void EncodedMotor::InitSmartDashboardPID()
{
    frc::SmartDashboard::PutNumber(motorName + "P Gain", kP);
    frc::SmartDashboard::PutNumber(motorName + "I Gain", kI);
    frc::SmartDashboard::PutNumber(motorName + "D Gain", kD);
    frc::SmartDashboard::PutNumber(motorName + "I Zone", kIz);
    frc::SmartDashboard::PutNumber(motorName + "Feed Forward", kFF);
    frc::SmartDashboard::PutNumber(motorName + "Max Output", kMaxOutput);
    frc::SmartDashboard::PutNumber(motorName + "Min Output", kMinOutput);

    frc::SmartDashboard::PutNumber(motorName + "SetPoint", SetPoint);
}

/**
 * Sends the Velocity to SmartDashboard
 * */
void EncodedMotor::PeriodicSmartDashboardPID()
{
    frc::SmartDashboard::PutNumber(motorName + "Velocity", Encoder.GetVelocity());
}

void EncodedMotor::PutSetpoint()
{
    frc::SmartDashboard::PutNumber(motorName + "SetPoint", SetPoint);
}

/**
 * Takes the values from the SmartDashboard and puts them into variables
 * */
void EncodedMotor::GetSmartDashboard()
{
    P = frc::SmartDashboard::GetNumber(motorName + "P Gain", 0);
    I = frc::SmartDashboard::GetNumber(motorName + "I Gain", 0);
    D = frc::SmartDashboard::GetNumber(motorName + "D Gain", 0);
    Iz = frc::SmartDashboard::GetNumber(motorName + "I Zone", 0);
    FF = frc::SmartDashboard::GetNumber(motorName + "Feed Forward", 0);
    MaxOutput = frc::SmartDashboard::GetNumber(motorName + "Max Output", 0);
    MinOutput = frc::SmartDashboard::GetNumber(motorName + "Min Output", 0);

    if(P != kP) { kP = P; PID.SetP(kP); }
    if(I != kI) { kI = I; PID.GetI(kI); }
    if(D != kD) { kD = D; PID.SetD(kD); }
    if(Iz != kIz) { kIz = Iz; PID.SetIZone(kIz); }
    if(MaxOutput != kMaxOutput || MinOutput != kMinOutput)
    {
        kMaxOutput = MaxOutput;
        kMinOutput = MinOutput;
        PID.SetOutputRange(kMinOutput, kMaxOutput);
    }
}

/**
 * Runs the PID from values taken from Smart Dashboard
 * */
void EncodedMotor::RunPIDFromSmartDashboard()
{
    SetPoint = frc::SmartDashboard::GetNumber(motorName + "SetPoint", 0);
    if(LastSetPoint != SetPoint) { PID.SetReference(SetPoint, rev::ControlType::kVelocity); }
}