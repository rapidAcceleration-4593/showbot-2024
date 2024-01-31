// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <rev/CANSparkMax.h>
#include <frc/XboxController.h>
#include "ctre/Phoenix.h"
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <iostream>
#include <rev/SparkMaxRelativeEncoder.h>



/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with tank steering.
 */
class Robot : public frc::TimedRobot {

  rev::CANSparkMax m_frontLeftDrive {3, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_frontRightDrive {4, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rearLeftDrive {5, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rearRightDrive {7, rev::CANSparkMax::MotorType::kBrushless};

  rev::CANSparkMax m_shooterLeft {2, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_shooterRight {6, rev::CANSparkMax::MotorType::kBrushless};

  frc::MotorControllerGroup m_leftSideDrive {m_frontLeftDrive, m_rearLeftDrive};
  frc::MotorControllerGroup m_rightSideDrive {m_frontRightDrive, m_rearRightDrive};

  TalonSRX m_meterWheel{1};

  frc::DifferentialDrive m_drivetrain {m_leftSideDrive, m_rightSideDrive};
 
  frc::XboxController m_driverController{0};

  rev::SparkRelativeEncoder m_leftShooterEncoder = m_shooterLeft.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);
  rev::SparkRelativeEncoder m_rightShooterEncoder = m_shooterRight.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);
  

 public:
  void RobotInit() override {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    //m_rightMotor.SetInverted(true);

    // m_rearRightDrive.Follow(m_frontRightDrive);
    // m_rearLeftDrive.Follow(m_frontLeftDrive);
  }

  void TeleopPeriodic() override {
    // Drive with arcade style
    
    m_drivetrain.ArcadeDrive(m_driverController.GetRightX(), m_driverController.GetLeftY());

    std::cout << "This is the speed left " << m_leftShooterEncoder.GetVelocity() << "This is the right side " << m_rightShooterEncoder.GetVelocity() << std::endl;

    if (m_driverController.GetAButton()){
      m_shooterRight.Set(1);
      m_shooterLeft.Set(-1);
    }

    

    else {
      m_shooterLeft.Set(0);
      m_shooterRight.Set(0);
      m_meterWheel.Set(ControlMode::PercentOutput, 0);
    }

    if (abs(-m_leftShooterEncoder.GetVelocity() + m_rightShooterEncoder.GetVelocity())/2 > 5500) {
      
      m_meterWheel.Set(ControlMode::PercentOutput, -.25);

    }
    //m_frontLeftDrive.Set(.5);
    //m_frontRightDrive.Set(.5);
    //m_rearLeftDrive.Set(.5);
    //m_rearRightDrive.Set(.5);
    //m_meterWheel.Set(ControlMode::PercentOutput, .5);
    //m_shooter1.Set(.5);
    //m_shooter2.Set(.5);
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
