#include "EncodedMotor.h"

#include "WiringDiagram.h"
#include <frc/smartdashboard/SmartDashboard.h>

/**
 * Constructs a SparkMax EncodedMotor
 * */
EncodedMotor::EncodedMotor(char inputName[], int canID, MotorType motorType, PIDValues inputValues) :
    rev::CANSparkMax(canID, motorType),
    PID (GetPIDController()),
    Encoder (GetEncoder())
{
    motorName = inputName;

    inputPIDValues = inputValues;
    myPIDValues = inputValues;

    // kP = 6e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000015, kMaxOutput = 1.0, kMinOutput = -1.0;
    // P = 6e-5, I = 1e-6, D = 0, Iz = 0, FF = 0.000015, MaxOutput = 1.0, MinOutput = -1.0;
}

EncodedMotor::EncodedMotor(char inputName[], int canID, MotorType motorType, int countsPerRev, PIDValues inputValues) :
    rev::CANSparkMax(canID, motorType),
    PID (GetPIDController()),
    Encoder (GetEncoder(rev::SparkMaxRelativeEncoder::Type::kQuadrature, countsPerRev))
{
    motorName = inputName;

    inputPIDValues = inputValues;
    myPIDValues = inputValues;

    // kP = 6e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000015, kMaxOutput = 1.0, kMinOutput = -1.0;
    // P = 6e-5, I = 1e-6, D = 0, Iz = 0, FF = 0.000015, MaxOutput = 1.0, MinOutput = -1.0;
}

/**
 * This function sends the PID values to the smartdashboard
 * */
void EncodedMotor::InitSmartDashboard()
{
    frc::SmartDashboard::PutNumber(motorName + "P Gain", myPIDValues.kP);
    frc::SmartDashboard::PutNumber(motorName + "I Gain", myPIDValues.kI);
    frc::SmartDashboard::PutNumber(motorName + "D Gain", myPIDValues.kD);
    frc::SmartDashboard::PutNumber(motorName + "I Zone", myPIDValues.kIz);
    frc::SmartDashboard::PutNumber(motorName + "Feed Forward", myPIDValues.kFF);
    frc::SmartDashboard::PutNumber(motorName + "Max Output", myPIDValues.kMaxOutput);
    frc::SmartDashboard::PutNumber(motorName + "Min Output", myPIDValues.kMinOutput);

    frc::SmartDashboard::PutNumber(motorName + "SetPoint", myPIDValues.setpoint);
}

/**
 * Sends the Velocity to SmartDashboard
 * */
void EncodedMotor::PeriodicSmartDashboard()
{
    frc::SmartDashboard::PutNumber(motorName + "Velocity", Encoder.GetVelocity());
}

void EncodedMotor::PutSetpoint()
{
    frc::SmartDashboard::PutNumber(motorName + "SetPoint", myPIDValues.setpoint);
}

/**
 * Takes the values from the SmartDashboard and puts them into variables
 * */
void EncodedMotor::GetSmartDashboard()
{
    inputPIDValues.kP = frc::SmartDashboard::GetNumber(motorName + "P Gain", 0);
    inputPIDValues.kI = frc::SmartDashboard::GetNumber(motorName + "I Gain", 0);
    inputPIDValues.kD = frc::SmartDashboard::GetNumber(motorName + "D Gain", 0);
    inputPIDValues.kIz = frc::SmartDashboard::GetNumber(motorName + "I Zone", 0);
    inputPIDValues.kFF = frc::SmartDashboard::GetNumber(motorName + "Feed Forward", 0);
    inputPIDValues.kMaxOutput = frc::SmartDashboard::GetNumber(motorName + "Max Output", 0);
    inputPIDValues.kMinOutput = frc::SmartDashboard::GetNumber(motorName + "Min Output", 0);

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
void EncodedMotor::RunPIDFromSmartDashboard()
{
    inputPIDValues.setpoint = frc::SmartDashboard::GetNumber(motorName + "SetPoint", 0);
    if(inputPIDValues.setpoint != myPIDValues.setpoint) { myPIDValues.setpoint = inputPIDValues.setpoint; PID.SetReference(myPIDValues.setpoint, rev::ControlType::kVelocity); }
}