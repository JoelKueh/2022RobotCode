#pragma once

#include <frc/drive/MecanumDrive.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include "FrcPID.h"
#include "WiringDiagram.h"

extern WiringDiagram MyWiringDiagram;

class Drive {
 public:
  Drive();
  FrcPID::PIDValues DrivePIDValues
  {
    DrivePIDValues.kP = .05, DrivePIDValues.kI = 0, DrivePIDValues.kD = 0, DrivePIDValues.kMaxOutput = 1.0, DrivePIDValues.kMinOutput = -1.0,
    DrivePIDValues.setpoint = 0,
    DrivePIDValues.positionTolerance = 1, DrivePIDValues.velocityTolerance = 5
  };
  FrcPID DrivePID {"Drive", DrivePIDValues};

  ctre::phoenix::motorcontrol::can::WPI_TalonSRX frontLeft {MyWiringDiagram.c_FrontLeftMotor};
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX frontRight {MyWiringDiagram.c_FrontRightMotor};
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX backLeft {MyWiringDiagram.c_BackLeftMotor};
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX backRight {MyWiringDiagram.c_BackRightMotor};

  frc::MecanumDrive* MyMecanumDrive;

  void RunPIDControl(double inputAngle);
  void RunDrive(double xboxLX, double xboxLY, double xboxRX);
  bool InRange();

  void InitSmartDashboard();
  void GetSmartDashboard();

  void PutSmartDashboard();
};
