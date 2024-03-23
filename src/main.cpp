// v tomot kodu jsem nejprve rozblikavala ledku
// pote jsem ji zapinala/zhasinala pomoci prikazu on/off
//----------------------------- 
#include <Arduino.h>

// #include "main.h"

//for Wemos D1 mini
#define DALI_TX_PIN  D5
#define DALI_RX_PIN  D0
#define LED_PIN      D4

bool isLedOn = false;


String slovo = ""; // Vytvoříme proměnnou pro uložení vstupu

//--------------------------------------- rozblikava ledku
// void setup() {
//   pinMode(LED_PIN, OUTPUT);
// }

// void loop() {
//   digitalWrite(LED_PIN, HIGH); // Rozsvítí LED
//   delay(500); // Počká 1 sekundu
//   digitalWrite(LED_PIN, LOW); // Zhasne LED
//   delay(500); // Počká 1 sekundu
//   // Serial.begin(115200);
// }

// ------------------------------------------------------- konec

// ------------------------------------------------- zapina se ledka podle on/off
void setup() {
pinMode(DALI_TX_PIN,OUTPUT);
digitalWrite(DALI_TX_PIN,HIGH);

pinMode(DALI_RX_PIN,INPUT);

Serial.begin(115200); // Start serial communication for debugging (optional)
pinMode(LED_PIN, OUTPUT);
digitalWrite(LED_PIN, LOW); // Turn LED off initially
printf("Hello\n");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    slovo += c; // Přidáme znak do proměnné
  }
  if(slovo.length() > 0 && slovo.endsWith("\n")){
    slovo.trim();                                  // odstraneni posledniho znaku
    printf(slovo.c_str());                         // ??????
    printf("delka = %d\n", slovo.length());        // zjistujeme delku slova
    printf("%d %d\n",slovo[0],slovo[1]);           // Vytiskne "\r\n"
    
    if (slovo.substring(0,2) == "on") {            // Porovnáme s "ON"
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED zapnuta");
    } else if (slovo.substring(0,3) == "off") {    // Porovnáme s "OFF"
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED vypnuta");
    } else {
      // Ignorujeme ostatní vstupy
    }
    slovo="";
  }
}
// -----------------------------------konec
