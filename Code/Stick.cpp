#include "PinConfig.h"
#include "Stick.h"
#include "SysData.h"

int offsetX, offsetY;

#define LOWPASS_SIZE 20
int bufX[LOWPASS_SIZE];
int LowpassX(int val)
{
    static int writeIdx = 0;
    bufX[writeIdx] = val;
    writeIdx++;
    if (writeIdx >= LOWPASS_SIZE)
        writeIdx = 0;

    int sum = 0;
    for (int i = 0; i <= LOWPASS_SIZE; ++i)
    {
        sum += bufX[i];
    }
    return sum / LOWPASS_SIZE;
}

int bufY[LOWPASS_SIZE];
int LowpassY(int val)
{

    static int writeIdx = 0;
    bufY[writeIdx] = val;
    writeIdx++;
    if (writeIdx >= LOWPASS_SIZE)
        writeIdx = 0;

    int sum = 0;
    for (int i = 0; i <= LOWPASS_SIZE; ++i)
    {
        sum += bufY[i];
    }
    return sum / LOWPASS_SIZE;
}

double Normalize(int val)
{
    // Measurement is 0 - 4095
    // will return a value between 0.0 and 100.0
    double v = val;
    return v / 4095;
}

double ReadX()
{
    int val = analogRead(PIN_STICK_HORIZ_X);
    val = LowpassX(val);
    val -= offsetX;
    if (val < 0)
        val = 0;
    else if (val > 4095)
        val = 4095;

    return Normalize(val);
}

double ReadY()
{
    int val = analogRead(PIN_STICK_VERT_Y);
    val = LowpassY(val);
    val -= offsetY;
    if (val < 0)
        val = 0;
    else if (val > 4095)
        val = 4095;
    return Normalize(val);
}

bool ReadSel()
{
    return !digitalRead(PIN_STICK_SEL);
}

void CalibrateStickCenter()
{
    int sumX = 0;
    for (int i = 0; i <= LOWPASS_SIZE; ++i)
    {
        sumX += bufX[i];
    }
    int valMediumX = sumX / LOWPASS_SIZE;

    SaveStickCenterX(valMediumX);

    int sumY = 0;
    for (int i = 0; i <= LOWPASS_SIZE; ++i)
    {
        sumY += bufY[i];
    }
    int valMediumY = sumY / LOWPASS_SIZE;

    SaveStickCenterY(valMediumY);

    offsetX = ReadStickCenterX() - (4096 / 2);
    offsetY = ReadStickCenterY() - (4096 / 2);
}

void SetupStick()
{
    pinMode(PIN_STICK_HORIZ_X, ANALOG);
    pinMode(PIN_STICK_VERT_Y, ANALOG);
    pinMode(PIN_STICK_SEL, INPUT_PULLUP);

    offsetX = ReadStickCenterX() - (4096 / 2);
    offsetY = ReadStickCenterY() - (4096 / 2);

    for (int i = 0; i <= LOWPASS_SIZE; ++i)
    {
        bufX[i] = bufY[i] = 4096/2;
    }
}
