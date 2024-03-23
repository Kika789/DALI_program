#pragma once


void delayMilisec(unsigned long t);
void delayMicrosec(unsigned int t);
void PrintHelp();
// void setup();
// void loop();
void BroadcastOnOff(bool state);
void ShortOnOff(int shortAddress, bool state);
void GroupOnOff(int groupAddress, bool state);
void ShortDAPC(int shortAddress, int value);
void GroupDAPC(int groupAddress, int value);
void SetMaxLevel(int maxLevel);
void SetFadeTime(int fadeTime);
void SetPowerOnLevel(int powerOnLevel);
void SetDimingCurve(int value);
void DaliInit(bool unsignedDevice, uint8_t ShortAddr);
void DaliReset();
void DaliClear();
bool SearchAndCompare(long SearchAddr);
void DaliTransmitCMD(uint8_t Part1, uint8_t Part2);