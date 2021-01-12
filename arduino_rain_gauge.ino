/* arduino_rain_gauge.ino
 *
 * Increment rain gauge counter on click, display on screen
 *
 */

#include <LiquidCrystal.h>

#include "src/button.hpp"
#include "src/temp36.hpp"

#define RESET_PIN 6
#define PAUSE_PIN 8
#define RAIN_PIN 9
#define TEMP_PIN A4

#define GAUGE_STD 0.11
#define GAUGE_MET 0.2794
#define BRIGHTNESS 0

using namespace components;

/* define variables */
float rain_std = 0.0;
float rain_met = 0.0;
bool updateFlag = true;
String inches, millimeters;
bool paused = false;
const char* holdMsg = "PAUSED";

/* initialize components */
Button resetButton = Button(RESET_PIN, 50, HIGH);
Button rainGauge = Button(RAIN_PIN, 50, HIGH);
Button hold = Button(PAUSE_PIN, 50, HIGH);
Temp36 temp = Temp36(TEMP_PIN, 5.0);

const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// set up the LCD screen
void prepLCD() {
    analogWrite(A3, BRIGHTNESS);
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print(0);
}

// update the LCD screen if there were any changes
void handleUpdateLCD() {
    if (updateFlag) {
        lcd.clear();
        inches = String(rain_std) + "\"";
        millimeters = String(rain_met) + "mm";
        lcd.print(inches);
        lcd.setCursor(0, 1);
        lcd.print(millimeters);
        updateFlag = false;
    }
}

// reset rain counters to zero
void handleReset() {
    rain_std = 0;
    rain_met = 0;
    updateLCD();
}

// increment the rain counters
void handleRainGauge() {
    rain_std += GAUGE_STD;
    rain_met += GAUGE_MET;
    updateLCD();
}

// flag the LCD screen to update
void updateLCD() {
    if (!updateFlag) {
        updateFlag = true;
    }
}

// don't increment counters on click, display pause message on screen
void handlePause() {
    if (paused) {
        paused = false;
        updateLCD();
    } else {
        paused = true;
        lcd.clear();
        lcd.print("PAUSED");
    }
}

/*  Begin the main loop  */

void setup() { prepLCD(); }

void loop() {
    if (!paused) {
        if (resetButton.isPressed()) handleReset();
        if (rainGauge.isPressed()) handleRainGauge();
    }
    if (hold.isPressed()) handlePause();
    handleUpdateLCD();
}
