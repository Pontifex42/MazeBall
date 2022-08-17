#include "Preferences.h"
#include "SysData.h"

Preferences preferences;

#define SERVOX_UP_DEFAULT 500
#define SERVOX_DOWN_DEFAULT 2400

#define SERVOY_UP_DEFAULT 544
#define SERVOY_DOWN_DEFAULT 2400

#define CENTERX_DEFAULT (4096/2)
#define CENTERY_DEFAULT (4096/2)

double ReadServoXUp()
{
	preferences.begin("SERVO", true);
	double ret = preferences.getDouble("XUP", SERVOX_UP_DEFAULT);
	preferences.end();
	return ret;
}


void SaveServoXUp(double angle)
{
	preferences.begin("SERVO", false);
	preferences.putDouble("XUP", angle);
	preferences.end();
}

double ReadServoXDown()
{
	preferences.begin("SERVO", true);
	double ret = preferences.getDouble("XDOWN", SERVOX_DOWN_DEFAULT);
	preferences.end();
	return ret;
}


void SaveServoXDown(double angle)
{
	preferences.begin("SERVO", false);
	preferences.putDouble("XDOWN", angle);
	preferences.end();
}



double ReadServoYUp()
{
	preferences.begin("SERVO", true);
	double ret = preferences.getDouble("YUP", SERVOY_UP_DEFAULT);
	preferences.end();
	return ret;
}

void SaveServoYUp(double angle)
{
	preferences.begin("SERVO", false);
	preferences.putDouble("YUP", angle);
	preferences.end();
}

double ReadServoYDown()
{
	preferences.begin("SERVO", true);
	double ret = preferences.getDouble("YDOWN", SERVOY_DOWN_DEFAULT);
	preferences.end();
	return ret;
}

void SaveServoYDown(double angle)
{
	preferences.begin("SERVO", false);
	preferences.putDouble("YDOWN", angle);
	preferences.end();
}

int ReadStickCenterX()
{
	preferences.begin("STICK", true);
	int ret = preferences.getInt("CENTERX", CENTERX_DEFAULT);
	preferences.end();
	return ret;
}

void SaveStickCenterX(int val)
{
	preferences.begin("STICK", false);
	preferences.putInt("CENTERX", val);
	preferences.end();
}

int ReadStickCenterY()
{
	preferences.begin("STICK", true);
	int ret = preferences.getInt("CENTERY", CENTERY_DEFAULT);
	preferences.end();
	return ret;
}

void SaveStickCenterY(int val)
{
	preferences.begin("STICK", false);
	preferences.putInt("CENTERY", val);
	preferences.end();
}
