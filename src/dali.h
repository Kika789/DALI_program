#pragma once

//for Wemos D1 mini
#define DALI_TX_PIN  D5
#define DALI_RX_PIN  D0
#define LED_PIN      D4


#define BROADCAST_DP 0b11111110
#define BROADCAST_C 0b11111111
#define ON_DP
#define OFF_DP 0b00000000
#define ON_C 0b00000101
#define OFF_C 0b00000000
#define QUERY_STATUS 0b10010000
#define RESET 0b00100000

#define INITIALISE          0xA5
#define RANDOMISE           0xA7
#define SEARCHADDRH         0xB1
#define SEARCHADDRM         0xB3
#define SEARCHADDRL         0xB5
#define PRG_SHORT_ADDR      0xB7
#define COMPARE             0xA9
#define WITHDRAW            0xAB
#define TERMINATE           0xA1

#define START_SHORT_ADDR    0

#define DOWN                0b00000010
#define UP                  0b00000001

// transfer rate is 1200 bps ~ 833.33us, half the speed will be 416.66 microseconds.
#define DALI_HALF_BIT_TIME        416 // microseconds
#define DALI_TWO_PACKET_DELAY      10 // miliseconds
#define DALI_RESPONSE_DELAY_COUNT  15 // maximal number of halfbites

#define DALI_ANALOG_LEVEL   650

void delayMilisec(unsigned long t);
void delayMicrosec(unsigned int t);
void PrintHelp();
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