#include "EncodedMotor.h"

#include "WiringDiagram.h"

#include <rev/CANSparkMax.h>
#include <frc/smartdashboard/SmartDashboard.h>

/**
 * Constructs a SparkMax EncodedMotor
 * */
EncodedMotor::EncodedMotor(int canID, MotorType motorType):
    rev::CANSparkMax(canID, motorType),
    ShooterPID (GetPIDController()),
    ShooterEncoder (GetEncoder()) {}

EncodedMotor::EncodedMotor(int canID, MotorType motorType, int countsPerRev) :
    rev::CANSparkMax(canID, motorType),
    ShooterPID (GetPIDController()),
    ShooterEncoder (GetEncoder(rev::SparkMaxRelativeEncoder::Type::kQuadrature, countsPerRev)) {}

/**
 * This function sends the PID values to the smartdashboard
 * */
void EncodedMotor::InitSmartDashboardPID()
{
    frc::SmartDashboard::PutNumber("P Gain", kP);
    frc::SmartDashboard::PutNumber("I Gain", kI);
    frc::SmartDashboard::PutNumber("D Gain", kD);
    frc::SmartDashboard::PutNumber("I Zone", kIz);
    frc::SmartDashboard::PutNumber("Feed Forward", kFF);
    frc::SmartDashboard::PutNumber("Max Output", kMaxOutput);
    frc::SmartDashboard::PutNumber("Min Output", kMinOutput);

    frc::SmartDashboard::PutNumber("SetPoint", SetPoint);
}

/**
 * Sends the Velocity to SmartDashboard
 * */
void EncodedMotor::PeriodicSmartDashboardPID()
{
    frc::SmartDashboard::PutNumber("Velocity", ShooterEncoder.GetVelocity());
}

void EncodedMotor::PutSetpoint()
{
    frc::SmartDashboard::PutNumber("SetPoint", SetPoint);
}

/**
 * Takes the values from the SmartDashboard and puts them into variables
 * */
void EncodedMotor::GetSmartDashboard()
{
    P = frc::SmartDashboard::GetNumber("P Gain", 0);
    I = frc::SmartDashboard::GetNumber("I Gain", 0);
    D = frc::SmartDashboard::GetNumber("D Gain", 0);
    Iz = frc::SmartDashboard::GetNumber("I Zone", 0);
    FF = frc::SmartDashboard::GetNumber("Feed Forward", 0);
    MaxOutput = frc::SmartDashboard::GetNumber("Max Output", 0);
    MinOutput = frc::SmartDashboard::GetNumber("Min Output", 0);

    if(P != kP) { kP = P; ShooterPID.SetP(kP); }
    if(I != kI) { kI = I; ShooterPID.GetI(kI); }
    if(D != kD) { kD = D; ShooterPID.SetD(kD); }
    if(Iz != kIz) { kIz = Iz; ShooterPID.SetIZone(kIz); }
    if(MaxOutput != kMaxOutput || MinOutput != kMinOutput)
    {
        kMaxOutput = MaxOutput;
        kMinOutput = MinOutput;
        ShooterPID.SetOutputRange(kMinOutput, kMaxOutput);
    }
}

/**
 * Runs the PID from values taken from Smart Dashboard
 * */
void EncodedMotor::RunPIDFromSmartDashboard()
{
    SetPoint = frc::SmartDashboard::GetNumber("SetPoint", 0);
    if(LastSetPoint != SetPoint) { ShooterPID.SetReference(SetPoint, rev::ControlType::kVelocity); }
}