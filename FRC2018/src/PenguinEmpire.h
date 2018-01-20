/*
 * PenguinEmpire.h
 * Created 2018-01-07
 *
 * Last update: 2018-01-16
 */

#ifndef SRC_PENGUINEMPIRE_H_
#define SRC_PENGUINEMPIRE_H_

#include "WPILib.h"
#include "MyJoystick.h"
#include "AHRS.h"

class Robot : public IterativeRobot {
public:
// Components and Systems
	Joystick left, right, handheld; // Joysticks
	MyJoystick m_left, m_right, m_handheld;
	Spark l1, l2, r1, r2; // Drive motor controllers
	AHRS *ahrs;

// Values and Structures
	bool leftswitch;
	bool leftscale;
	bool controlOverride;
	bool gyroTurning;

	enum FieldPosition { // Used for autonomous
		Left,
		Center,
		Right
	} fpos;

	enum StepType { // Used for autonomous
		reset,
		encodermove,
		gyroturn
	};

	struct Step {
		Robot *robot;
		StepType type;
		bool complete, setup;
		std::vector<double> params;
		Step(Robot *r, StepType steptype, std::vector<double> parameters);
		~Step();
		void Run();
	};

	std::vector<Step> autosteps;
	int numsteps, curstep;

// Stages

	// Setup
	Robot();
	~Robot();
	void RobotInit();

	// Autonomous
	void AutonomousInit();
	void AutonomousPeriodic();
	void CheckSide();
	void CheckPos();
	void LeftAuto();
	void CenterAuto();
	void RightAuto();

	// Teleoperated
	void TeleopInit();
	void TeleopPeriodic();
	void SetLeftSpeed(float speed);
	void SetRightSpeed(float speed);
	void StopMotors();
	void TankDrive();
	void GyroTurn(bool btn, float speed, double angle);
	void GyroTurn(int pov, float speed);

	// Test
	void TestInit();
	void TestPeriodic();

};

#endif /* SRC_PENGUINEMPIRE_H_ */
