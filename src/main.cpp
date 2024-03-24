// V tomto kodu chci nastavit intenzitu svetla a posouvani jasu podle talcitek u (up) a d (down), takze od 0 do 255, pak se to opakuje
// co dale? nefunguje fade; osetreni zhasnuti svetel; postupne rozsvicovani; infromace o stavu svetel?; komunikace s jednotlivym panelem;
// dale skupiny, adreovani, konfigurace,  mode reset,
// blikanim budu snizovat intenzitu
// asi vzdy musim davat BroadcastOnOff(on) ?????
// zjistit jak funguje fce Fade
//-----------------------------
#include <Arduino.h>
#include "dali.h"
#include "main.h"


#define ON 1
#define OFF 0

bool isLedOn = false;
bool BL = 0;             // promenna pro svetlo, jestli je zapnuta nebo vypnuta
bool svetlo=0;           // promenna pro svetla
bool svetlo_stav=0;      // promenna pro stav svetla
unsigned long cas=0;     // promenna pro zapamatovani stavu casu
unsigned long cas_svetlo=0;
int jas = 100;           // promenna pro jas
//------
int prolinani = 50;
int max_h = 100;

String comMsg = ""; // Vytvoříme proměnnou pro uložení vstupu


// help for serial terminal
void PrintHelp() {
    Serial.println();
    Serial.println("Help");
    Serial.println("------------------");
    Serial.println("on/off : broadcast on/off");
    Serial.println("sAAon/sAAoff : short address on/off, where AA is a short address (dec)");
    Serial.println("sAAdapcDDD : short address DAPC, where AA is a short address (dec) and DDD is DAPC level (dec)");
    Serial.println("gAAon/gAAoff : group address on/off, where AA is a group address (dec)");
    Serial.println("gAAdapcDDD : group address DAPC, where AA is a group address (dec) and DDD is DAPC level (dec)");
    Serial.println("maxDDD : set max level DDD (dec)");
    Serial.println("fadeDDD : set Fade Time DDD (dec)");
    Serial.println("dimingB : set Diming Curve (bin), where 0 = logaritmic diming curve, 1 = linear diming curve");
    Serial.println("power_onDDD : set Power On level DDD (dec)");
    Serial.println("init_all : assign short adresses to all devices");
    Serial.println("init_all_fromDD : assign short adresses to all devices, where DD is the lowest address (dec)");
    Serial.println("init_unsigned_fromDD : assign short adresses to unsigned devices, where DD is the lowest address (dec)");
    Serial.println("add_grDD_fromAA_toAA : add short adresses from AA (dec) to AA (dec) to group DD (dec)");
    Serial.println("reset_all : reset all devices");
    Serial.println("clear_all : clear short adresses from all devices");
    Serial.println("0xHHHH : direct command, where HHHH is command code (hex)");
    Serial.println();
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    pinMode(DALI_TX_PIN, OUTPUT);
    digitalWrite(DALI_TX_PIN, HIGH);

    pinMode(DALI_RX_PIN, INPUT);

    Serial.begin(115200);
    //delayMilisec(500);
    Serial.println(" ");
    Serial.println("Welcome to DALI Control Software");
    Serial.println("Running ...");
    // PrintHelp();
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    comMsg += c; // Přidáme znak do proměnné
  }

// osetreni vstupu -----------------------------------------------------
  if(comMsg.length() > 0 && comMsg.endsWith("\n")){
    comMsg.trim();                                  // odstraneni posledniho znaku
    printf("%s\n",comMsg.c_str());
    printf("delka = %d\n", comMsg.length());        // zjistujeme delku slova
    printf("%d %d\n",comMsg[0],comMsg[1]);           // Vytiskne "\r\n"
//----------------------------------------------------------------------

    // handle string from serial
    if (comMsg == "help") {
        PrintHelp();
    }

    if (comMsg == "on") {
      BroadcastOnOff(ON);
    //   svetlo = 1;
    //   BL = 1;
    //   cas = millis();     // nastaveni na aktualni hodnotu v ms
    //   cas_svetlo = millis();
    } // broadcast, 100%

    if (comMsg == "off") {
      BroadcastOnOff(OFF);
    //   digitalWrite(LED_PIN, HIGH); // Zhasne LED
    //   svetlo = 0;
    //   BL=0;
    } // broadcast, 0%

    if (comMsg.startsWith("max")) // broadcast set max level
        {
            int maxLevel = comMsg.substring(3, 6).toInt();
            Serial.print("Max Level ");
            Serial.println(maxLevel);
            SetMaxLevel(maxLevel);
            // SetMaxLevel(max_h);
            BroadcastOnOff(ON);
    };// broadcast set max level

    if (comMsg.startsWith("fade")) // broadcast set fade time
    {
        int fadeTime = comMsg.substring(4, 7).toInt();
        Serial.print("Fade Time ");
        Serial.println(fadeTime);
        SetFadeTime(fadeTime);
        // SetFadeTime(prolinani);
        // BroadcastOnOff(ON);
    };// broadcast set Fade Time


    // if (comMsg == "p") {        // zvysuji fade o +50
    //     prolinani+=50;
    //     printf("fade=%d\n",prolinani);
    //     SetFadeTime(prolinani);
    //     BroadcastOnOff(ON);
    // }
    // if (comMsg == "s") {        // zvysuji fade o +50
    //     prolinani+=50;
    //     printf("fade=%d\n",prolinani);
    //     SetFadeTime(prolinani);
    //     BroadcastOnOff(ON);
    // }

    if (comMsg == "u") {        // zvysuji jas o +50
        jas+=50;
        printf("jas=%d\n",jas);
        SetMaxLevel(jas);
        BroadcastOnOff(ON);
    }

    if (comMsg == "d") {       // snizuji jas o -50
        jas-=50;
        printf("jas=%d\n",jas);
        SetMaxLevel(jas);
        BroadcastOnOff(ON);
    }


    if (comMsg.startsWith("power_on")) // broadcast Power On level
        {
            int powerOnLevel = comMsg.substring(8, 11).toInt();
            Serial.print("Power On Level ");
            Serial.println(powerOnLevel);
            SetPowerOnLevel(powerOnLevel);
            BroadcastOnOff(ON);
        };// broadcast Power On level

    comMsg="";
  }

//-------------------------------------------Blikani--------------------------------------------------

//   if(BL){                // mame blikat
//     if(millis()>cas){
//       digitalWrite(LED_PIN, !digitalRead(LED_PIN));    // kdyz tam bylo low tak dam high a obracene
//       cas=millis()+100;
//     }
//   }
//   if(svetlo){          // blikani svetel
//     if(millis()>cas_svetlo){
//         if(svetlo_stav){
//             BroadcastOnOff(OFF);
//         }
//         else {
//             BroadcastOnOff(ON);
//         }
//         svetlo_stav=!svetlo_stav;
//         cas_svetlo=millis()+1000;
//     }
//   }
}
// -----------------------------------konec

