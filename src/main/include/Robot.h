#pragma once

#include <string.h>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <rev/CANSparkMax.h>
#include <frc/XboxController.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/drive/MecanumDrive.h>
#include <rev/CANSparkMax.h>
#include <frc/Timer.h>
#include <frc/Watchdog.h>
#include <frc2/command/WaitCommand.h>

#include "Drive.h"
#include "Intake.h"
#include "Hanger.h"
#include "Shooter.h"
#include "Limelight.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
  void ShooterControl();
  void SimpleAuto();

  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  frc::SendableChooser<std::string> SmartTestSwitch;
  const std::string kTestDefault = "Default";
  const std::string kTestFlywheel = "Flywheel";
  const std::string kTestElevator = "Elevator";
  const std::string kTestDrivePID = "Drive PID";
  const std::string kTestAim = "Test Aim";
  std::string TestSelected;

  frc::Watchdog MyWatchdog;

  Limelight* MyLimelight;
  Drive* MyDrive;
  Intake* MyIntake;
  Hanger* MyHanger;
  Shooter* MyShooter;

  frc::XboxController* Xbox;
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX* IndexMotor;

  bool lockedOn = false;
  short increment = 0;
};
