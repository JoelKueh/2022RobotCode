#include "Robot.h"

#include <fmt/core.h>

#include "WiringDiagram.h"
WiringDiagram MyWiringDiagram;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  MyLimelight = new Limelight();
  MyDrive = new Drive();
  MyIntake = new Intake();
  MyHanger = new Hanger();
  MyShooter = new Shooter();

  Xbox = new frc::XboxController(MyWiringDiagram.c_Xbox);
  IndexMotor = new ctre::phoenix::motorcontrol::can::WPI_VictorSPX(MyWiringDiagram.c_IndexMotor);
  IndexMotor->SetInverted(true);

  // MyShooter->SetupElevatorEncoder();

  MyLimelight->LEDOff();
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

void Robot::TeleopInit()
{
  StupidTestInit();
}

void Robot::TeleopPeriodic()
{
  MyLimelight->LEDOn();

  RealTeleopPeriodic();
  
  // StuipdTestPeriodic();
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit()
{

}

void Robot::TestPeriodic()
{

}

void Robot::RealTeleopPeriodic()
{
  if (Xbox->GetRightBumperPressed())
  {
    MyIntake->Toggle();
  }

  if (Xbox->GetRightTriggerAxis() > .15)
  {
    MyIntake->Run(.15);
  }
  else
  {
    MyIntake->Run(0);
  }

  if (Xbox->GetLeftBumperPressed())
  {
    MyHanger->Toggle();
  }

  switch (increment)
  {
    case 0:
      lockedOn = false;
      frc::SmartDashboard::PutBoolean("Shoot?", lockedOn);

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

      MyShooter->SpinFlywheel(5700);
      // MyDrive->RunPIDControl(MyLimelight->GetX());
      // MyShooter->RunElevator(MyLimelight->GetY());

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

void Robot::StupidTestInit()
{
  SmartTestSwitch.SetDefaultOption(kTestDefault, kTestDefault);
  SmartTestSwitch.AddOption(kTestFlywheel, kTestFlywheel);
  SmartTestSwitch.AddOption(kTestElevator, kTestElevator);
  SmartTestSwitch.AddOption(kTestDrivePID, kTestDrivePID);
  SmartTestSwitch.AddOption(kTestAim, kTestAim);
  frc::SmartDashboard::PutData("Test Modes", &SmartTestSwitch);

  MyDrive->InitSmartDashboard();
  MyShooter->InitSmartDashboard();
}

void Robot::StuipdTestPeriodic()
{
  TestSelected = SmartTestSwitch.GetSelected();

  MyDrive->GetSmartDashboard();
  MyShooter->GetSmartDashboard();

  MyDrive->PutSmartDashboard();
  MyShooter->PutSmartDashboard();

  if (TestSelected == kTestFlywheel)
  {
    IndexMotor->Set(.25);
    MyShooter->SpinFlywheel(5200);
  }
  else
  {
    IndexMotor->Set(0);
    MyShooter->StopFlywheel();
    
    MyShooter->DeleteSmartDashboard();
  }
  
  if (TestSelected == kTestElevator)
  {
    MyShooter->RunElevator(MyLimelight->GetY());
  }
  else
  {
    MyShooter->StopElevator();
  }
  
  if (TestSelected == kTestDrivePID)
  {
    MyDrive->RunPIDControl(MyLimelight->GetY());
  }
  else
  {
    MyDrive->RunDrive(Xbox->GetLeftY(), Xbox->GetLeftX(), Xbox->GetRightX());
  }

  if (TestSelected == kTestAim)
  {

  }
  else
  {

  }
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
