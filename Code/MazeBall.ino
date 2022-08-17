/*
 Name:		MazeBall.ino
 Created:	16.08.2022 19:09:59
 Author:	Thorsten
*/

#include "PinConfig.h"
#include <WiFi.h>
#include "ServoXY.h"
#include "Stick.h"

// #define DEBUG_INO
#ifndef DEBUG_INO

#ifdef DEBUG_PRINTLN
#undef DEBUG_PRINTLN
#define DEBUG_PRINTLN(a)
#undef DEBUG_PRINT
#define DEBUG_PRINT(a)
#endif

#endif

void setup() 
{
	setCpuFrequencyMhz(240);
	WiFi.mode(WIFI_OFF);
	WiFi.setSleep(true);
	Serial.begin(115200);

	SetupServoXY();
	SetupStick();

	DEBUG_PRINTLN("Setup OK");
}

void loop() 
{
	double  x = ReadX();
	double y = ReadY();
	DEBUG_PRINTLN("X: " + String(x) + "  Y: " + String(y) + "  Sel: " + String(sel));
	double angleX = x * 180;
	ServoGoToAngleX(angleX);
	double angleY = y * 180;
	ServoGoToAngleY(180 - angleY);
	DEBUG_PRINTLN("X: " + String(angleX) + "  Y: " + String(angleY));
	delay(20);

	if (ReadSel())
	{
		CalibrateStickCenter();
	}
}
