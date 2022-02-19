#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <rev/CANSparkMax.h>
#include <frc/XboxController.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/DigitalInput.h>

#include "Drive.h"
#include "WiringDiagram.h"
#include "Intake.h"
#include "Hanger.h"
#include "Shooter.h"
#include "Limelight.h"

Limelight MyLimelight;
Drive MyDrive;
WiringDiagram MyWiringDiagram;
Intake MyIntake;
Hanger MyHanger;
Shooter MyShooter;

frc::XboxController Xbox {MyWiringDiagram.c_Xbox};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX IndexMotor {MyWiringDiagram.c_IndexMotor};
frc::DigitalInput ElevatorLimit {MyWiringDiagram.c_ElevatorLimit};

short increment = 0;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  MyLimelight.LEDOff();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic()
{
  if (Xbox.GetRightBumperPressed())
  {
    MyIntake.Toggle();
  }

  if (Xbox.GetRightTriggerAxis() > .15)
  {
    MyIntake.Run(.15);
  }
  else
  {
    MyIntake.Run(0);
  }

  if (Xbox.GetLeftBumperPressed())
  {
    MyHanger.Toggle();
  }

  switch (increment)
  {
    case 0:
      MyDrive.RunDrive(Xbox.GetLeftY(), Xbox.GetLeftX(), Xbox.GetRightX());

      if(Xbox.GetYButtonPressed())
      {
        increment = 1;
        MyLimelight.LEDOn();
      }
      IndexMotor.Set(0);
      MyShooter.StopFlywheel();
      MyShooter.StopElevator();
      break;

    case 1:
      MyShooter.SpinFlywheel(4500);
      MyDrive.RunPIDControl(MyLimelight.GetX());
      MyShooter.RunElevator(MyLimelight.GetY());

      if(MyShooter.FlywheelInRange() && MyShooter.ElevatorInRange() && MyDrive.InRange())
      {
        IndexMotor.Set(.2);
      }
      else
      {
        IndexMotor.Set(0);
      }

      if(Xbox.GetYButtonPressed())
      {
        MyLimelight.LEDOff();
        increment = 0;
      }
      break;
  }
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::ResetElevator()
{

}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
