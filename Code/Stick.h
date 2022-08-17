#pragma once

void SetupStick();
double  ReadX();
double ReadY();
bool ReadSel(); // 'Sel' is the switch of the joystick

void CalibrateStickCenter();