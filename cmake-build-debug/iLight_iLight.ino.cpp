// automatically generated by arduino-cmake
#line 1 "D:/Users/Ju'/Google Drive/Works/iLight/iLight.ino"
#include <Arduino.h>

#include <CmdParser.hpp>
#include <CmdBuffer.hpp>

#line 8 "D:/Users/Ju'/Google Drive/Works/iLight/cmake-build-debug/iLight_iLight.ino.cpp"
#include "Arduino.h"

//=== START Forward: D:/Users/Ju'/Google Drive/Works/iLight/iLight.ino
 void setup() ;
 void setup() ;
 void loop() ;
 void loop() ;
 void checkCommand(void) ;
 void checkCommand(void) ;
 void reportERROR(int err) ;
 void reportERROR(int err) ;
//=== END Forward: D:/Users/Ju'/Google Drive/Works/iLight/iLight.ino
#line 4 "D:/Users/Ju'/Google Drive/Works/iLight/iLight.ino"


CmdBuffer<128> cmdBuffer;
CmdParser cmdParser;

#define DEBUG 0
#define DATA 5
#define LED 4
#define BUTTON_ONE 3
#define BUTTON_TWO 2

#define SDATA A0

#define NUM_LEDS    14
#define BRIGHTNESS  128
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

String IP = "0002";

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void checkCommand(void);

void setup() {
    Serial.begin(115200);

    pinMode(LED, OUTPUT);
    pinMode(BUTTON_ONE, INPUT);
    pinMode(BUTTON_TWO, INPUT);

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

void loop() {

}

void checkCommand(void) {
    int is_received = cmdBuffer.readFromSerial(&Serial, 1000);

    if (is_received) {
        if (cmdParser.parseCmd(cmdBuffer.getStringFromBuffer()) != CMDPARSER_ERROR) {
            String current_cmd = cmdParser.getCommand();
            if (cmdParser.equalCommand_P(PSTR("SET"))) {
                String ip = cmdParser.getValueFromKey_P(PSTR("IP"));
                if (ip == IP) {

                }
            }

            if (cmdParser.equalCommand_P(PSTR("GET"))) {
                String ip = cmdParser.getValueFromKey_P(PSTR("IP"));
                if (ip == IP) {

                }
            }

            if (cmdParser.equalCommand_P(PSTR("DEBUG"))) {
                String ip = cmdParser.getValueFromKey_P(PSTR("IP"));
                if (ip == IP) {

                }
            }
        } else {
            reportERROR(ERROR_SERIAL_PARSER);
        }
    } else {
        //reportERROR(ERROR_SERIAL_TIMEOUT);
    }
}

void reportERROR(int err) {
    Serial.print("MASTER IP=\"0000\" FROM=\"");
    Serial.print(IP);
    Serial.print("\" ERROR=\"");
    Serial.print(err);
    Serial.println("\"");
}
