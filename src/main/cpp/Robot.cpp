#include "Robot.h"

#include <fmt/core.h>

#include "WiringDiagram.h"
WiringDiagram MyWiringDiagram;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  frc::SmartDashboard::PutNumber("Ele Temp", 0);

  MyLimelight = new Limelight();
  MyDrive = new Drive();
  MyIntake = new Intake();
  MyHanger = new Hanger();
  MyShooter = new Shooter();

  Xbox = new frc::XboxController(MyWiringDiagram.c_Xbox);
  IndexMotor = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX(MyWiringDiagram.c_IndexMotor);
  IndexMotor->SetInverted(true);

  MyLimelight->LEDOff();
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  MyShooter->ZeroElevator();

  MyHanger->Init();
  MyIntake->Init();

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

void Robot::TeleopInit()
{
  MyHanger->Init();
  MyIntake->Init();

  MyLimelight->LEDOff();
  MyShooter->ZeroElevator();
  MyShooter->InitSmartDashboard();
  MyDrive->InitSmartDashboard();
}

void Robot::TeleopPeriodic()
{
  MyShooter->GetSmartDashboard();
  MyShooter->PutSmartDashboard();
  MyDrive->GetSmartDashboard();

  // if(Xbox->GetRightBumperPressed())
  // {
  //   MyIntake->Toggle();
  // }

  if(Xbox->GetRightTriggerAxis() > .15)
  {
    MyIntake->Run(.9);
  }
  else
  {
    MyIntake->Run(0);
  }

  if(Xbox->GetLeftBumperPressed())
  {
    MyHanger->Toggle();
  }

  FourShots();
  ShooterControl();
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::FourShots()
{
  switch (Xbox->GetPOV())
  {
    case 0: flyRPM = 5500; eleSetpoint = 0; break;
    case 90: flyRPM = 3200; eleSetpoint = 10; break;
    case 180: flyRPM = 4150; eleSetpoint = 20; break;
    case 270: flyRPM = 5500; eleSetpoint = 30; break;
  }
}

void Robot::ShooterControl()
{
  switch (increment)
  {
    case 0:
      lockedOn = false;
      frc::SmartDashboard::PutBoolean("Shoot?", lockedOn);
      frc::SmartDashboard::PutNumber("XboxRX", Xbox->GetRightX());

      MyDrive->RunDrive(Xbox->GetLeftY(), Xbox->GetLeftX(), Xbox->GetRightX());

      if(Xbox->GetYButtonPressed())
      {
        increment = 1;
        MyLimelight->LEDOn();
      }
      IndexMotor->Set(0);
      MyShooter->StopFlywheel();
      MyShooter->StopElevator();

      break;
    case 1:
      frc::SmartDashboard::PutBoolean("Shoot?", lockedOn);

      // flyRPM = frc::SmartDashboard::GetNumber("Fly SetPoint", 0);
      MyShooter->SpinFlywheel(flyRPM);
      MyDrive->RunPIDControl(MyLimelight->GetX());
      // eleSetpoint = frc::SmartDashboard::GetNumber("Ele Temp", 0);
      MyShooter->RunElevator(eleSetpoint);

      MyLimelight->GetX();
      MyLimelight->GetY();

      if(MyShooter->FlywheelInRange() && MyShooter->ElevatorInRange() && MyDrive->InRange())
      {
        lockedOn = true;
      }
      else
      {
        lockedOn = false;
      }

      if(Xbox->GetXButton())
      {
        IndexMotor->Set(.5);
      }
      else
      {
        IndexMotor->Set(0);
      }

      if(Xbox->GetYButtonPressed())
      {
        MyLimelight->LEDOff();
        increment = 0;
      }
      break;
  }
}

void Robot::SimpleAuto()
{
  // MyWatchdog.Disable();
  // MyDrive->RunDrive(0, .45, 0);
  // MyIntake->Run(1);
  // sleep(1);
  // MyDrive->RunDrive(0, 0, 0);
  // sleep(1);
  // MyIntake->Run(0);
  // MyDrive->RunDrive(0, 0, -.3);
  // sleep(1);
  // MyDrive->RunDrive(0, 0, 0);

  // double flyRPM = 0;
  // double eleSetpoint = 0;

  // MyShooter->FlywheelFF(flyRPM);
  // MyDrive->RunPIDControl(MyLimelight->GetX());
  // MyShooter->RunElevator(eleSetpoint);

  // MyLimelight->GetX();
  // MyLimelight->GetY();

  // if(MyShooter->FlywheelInRange() && MyShooter->ElevatorInRange() && MyDrive->InRange())
  // {
  //   lockedOn = true;
  // }
  // else
  // {
  //   lockedOn = false;
  // }

  // if(Xbox->GetXButton())
  // {
  //   IndexMotor->Set(.5);
  // }
  // else
  // {
  //   IndexMotor->Set(0);
  // }

  // if(Xbox->GetYButtonPressed())
  // {
  //   MyLimelight->LEDOff();
  //   increment = 0;
  // } 
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif