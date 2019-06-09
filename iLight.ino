#include <Arduino.h>

#include <CmdParser.hpp>
#include <CmdBuffer.hpp>
#include <FastLED.h>

CmdBuffer<128> cmdBuffer;
CmdParser cmdParser;

#define DEBUG 0
#define DATA 5
#define LAMP 9

#define ERROR_SERIAL_PARSER -1

#define NUM_LEDS    144
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

String IP = "0002";
int STATE = 0;
uint8_t brightness = 255;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void checkCommand(void);
void reportERROR(int err);

void SetupPurpleAndGreenPalette(void);
void FillLEDsFromPaletteColors(uint8_t colorIndex);
void ChangePalettePeriodically(void);
void SetupTotallyRandomPalette(void);
void SetupBlackAndWhiteStripedPalette(void);
void SetupBlackPalette(void);
void SetupWhitePalette(void);


void setup() {
    Serial.begin(115200);

    Serial.println("Started");

    pinMode(LAMP, OUTPUT);

    digitalWrite(LAMP, LOW);

    FastLED.addLeds<LED_TYPE, DATA, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
    FastLED.setBrightness(  BRIGHTNESS );

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

static uint8_t startIndex = 0;

void loop() {
    checkCommand();
    startIndex = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors(startIndex);

    FastLED.show();
    //FastLED.delay(1);
}

void FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;

    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;

}

void fadeIn() {
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    while (brightness != 255) {
        brightness++;
        FillLEDsFromPaletteColors(startIndex);
        FastLED.show();
        delay(10);
    }
}

void fadeOut() {
    while (brightness != 0) {
        brightness--;
        FillLEDsFromPaletteColors(startIndex);
        FastLED.show();
        delay(10);
    }
}

void SetupBlackPalette() {
    fill_solid(currentPalette, 16, CRGB::Black);
}

void SetupWarmWhitePalette() {

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].red   = 255;
        leds[i].green = 193;
        leds[i].blue  = 7; // rgb(255, 193, 7)
    }
}

void SetupWhitePalette() {
    fill_solid(currentPalette, 16, CRGB::White);
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;

    currentPalette = CRGBPalette16(
            green,  green,  black,  black,
            purple, purple, black,  black,
            green,  green,  black,  black,
            purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
        {
                CRGB::Red,
                CRGB::Gray, // 'white' is too bright compared to red and blue
                CRGB::Blue,
                CRGB::Black,

                CRGB::Red,
                CRGB::Gray,
                CRGB::Blue,
                CRGB::Black,

                CRGB::Red,
                CRGB::Red,
                CRGB::Gray,
                CRGB::Gray,
                CRGB::Blue,
                CRGB::Blue,
                CRGB::Black,
                CRGB::Black
        };

void checkCommand(void) {
    int is_received = cmdBuffer.readFromSerial(&Serial, 1000);

    if (is_received) {
        if (cmdParser.parseCmd(cmdBuffer.getStringFromBuffer()) != CMDPARSER_ERROR) {
            String current_cmd = cmdParser.getCommand();
            /*if (cmdParser.equalCommand_P(PSTR("SET"))) {
                Serial.println("SET");
                if (cmdParser.equalCommand_P(PSTR("IP_0002"))) {*/
                    if (cmdParser.equalCommand_P(PSTR("LAMP_ON"))) {
                        digitalWrite(LAMP, HIGH);
                    } else if (cmdParser.equalCommand_P(PSTR("LAMP_OFF"))) {
                        digitalWrite(LAMP, LOW);
                    } else if (cmdParser.equalCommand_P(PSTR("LED_ON"))) {
                        fadeOut();
                        currentPalette = RainbowColors_p;
                        currentBlending = LINEARBLEND;
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_OFF"))) {
                        fadeOut();
                        SetupBlackPalette();
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_0"))) {
                        fadeOut();
                        ChangePalettePeriodically();
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_1"))) {
                        fadeOut();
                        SetupBlackPalette();
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_2"))) {
                        fadeOut();
                        currentPalette = RainbowColors_p;
                        currentBlending = LINEARBLEND;
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_3"))) {
                        fadeOut();
                        currentPalette = RainbowStripeColors_p;
                        currentBlending = LINEARBLEND;
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_4"))) {
                        fadeOut();
                        SetupPurpleAndGreenPalette();
                        currentBlending = LINEARBLEND;
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_5"))) {
                        fadeOut();
                        SetupTotallyRandomPalette();
                        currentBlending = LINEARBLEND;
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_6"))) {
                        fadeOut();
                        SetupBlackAndWhiteStripedPalette();
                        currentBlending = LINEARBLEND;
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_7"))) {
                        fadeOut();
                        currentPalette = CloudColors_p;
                        currentBlending = LINEARBLEND;
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_8"))) {
                        fadeOut();
                        currentPalette = PartyColors_p;
                        currentBlending = LINEARBLEND;
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LED_9"))) {
                        fadeOut();
                        SetupWhitePalette();
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("ALL_OFF"))) {
                        fadeOut();
                        digitalWrite(LAMP, LOW);
                        SetupBlackPalette();
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("AMBIANT_LIGHTING"))) {
                        fadeOut();
                        currentPalette = RainbowColors_p;
                        currentBlending = LINEARBLEND;
                        digitalWrite(LAMP, LOW);
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("NORMAL_LIGHTING"))) {
                        fadeOut();
                        SetupWhitePalette();
                        brightness = 255;
                        fadeIn();
                    } else if (cmdParser.equalCommand_P(PSTR("LOWER_LIGHT"))) {
                        if (brightness - 15 > 0) {
                            brightness -= 15;
                        } else {
                            brightness = 0;
                        }
                    } else if (cmdParser.equalCommand_P(PSTR("HIGHER_LIGHT"))) {
                        if (brightness + 15 < 255) {
                            brightness += 15;
                        } else {
                            brightness = 255;
                        }
                    }
                /*}
            }*/

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
