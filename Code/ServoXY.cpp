#include "PinConfig.h"
#include <ESP32Servo.h>
#include "ServoXY.h"
#include "SysData.h"

//#define DEBUG_SERVOXY

#ifndef DEBUG_SERVOXY

#ifdef DEBUG_PRINTLN
#undef DEBUG_PRINTLN
#define DEBUG_PRINTLN(a)
#undef DEBUG_PRINT
#define DEBUG_PRINT(a)
#endif

#endif


#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Servo ServoX;
Servo ServoY;

//------------------------------------------------------------------------------
void MoveSmooth(int current, int target)
{
	// SG90 runs 120 deg./s = 0,12 deg/ms.
	// 5 deg / 0.12 deg/ms = 42 ms
	// hopefully, using 60 ms makes movement slower
	// should be a multiply of 20, cause stepper PWM signal works at 50Hz
#define ANGLE_PER_STEP 5
#define SG90_DELAY 20
	int steps = abs((current - target) / ANGLE_PER_STEP);
	int increment = (current < target) ? ANGLE_PER_STEP : -ANGLE_PER_STEP;
		
	for (int i = 0; i < steps; ++i) // smooth movement
	{
		current += increment;
		ServoX.write(current);
		delay(SG90_DELAY);
	}
	if (target != current)
	{
		ServoX.write(target);
		delay(SG90_DELAY);
	}
}

void ServoGoToAngleX(double angle)
{
	DEBUG_PRINTLN("ServoGoToAngleX " + String(angle));
	//	Datasheet claims a speed of 60 degrees within 100ms
	ServoX.write(angle); // not waiting for finishing movement
}

void ServoGoToAngleY(double  angle)
{
	DEBUG_PRINTLN("ServoGoToAngleY " + String(angle));
	//	Datasheet claims a speed of 60 degrees within 100ms
	ServoY.write(angle); // not waiting for finishing movement
}

void DeactivateServos()
{
	 pinMode(PIN_SERVO_X, INPUT);
	 pinMode(PIN_SERVO_Y, INPUT);
}

void ReactivateServos()
{
	pinMode(PIN_SERVO_X, OUTPUT);
	pinMode(PIN_SERVO_Y, OUTPUT);
}

double minUsX, maxUsX, minUsY, maxUsY;

void SetupServoXY()
{
	maxUsX = ReadServoXDown();
	minUsX = ReadServoXUp();
	maxUsY = ReadServoYDown();
	minUsY = ReadServoYUp();
	DEBUG_PRINTLN("minUsX" + String(minUsX) + "  maxUsX" + String(maxUsX) + "  minUsY" + String(minUsY) + "  maxUsY" + String(maxUsY));
	pinMode(PIN_SERVO_X, OUTPUT);
	pinMode(PIN_SERVO_Y, OUTPUT);

	ESP32PWM::allocateTimer(0);
	ServoX.setPeriodHertz(50); // standard 50 hz servo
	ServoX.attach(PIN_SERVO_X, minUsX, maxUsX);

	ServoY.setPeriodHertz(50); // standard 50 hz servo
	ServoY.attach(PIN_SERVO_Y, minUsY, maxUsY);
}


