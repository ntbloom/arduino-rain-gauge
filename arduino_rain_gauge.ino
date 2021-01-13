/* arduino_rain_gauge.ino
 *
 * Increment rain gauge counter on click, display on screen
 *
 */

#include <LiquidCrystal.h>

#include "src/button.hpp"
#include "src/temp36.hpp"

/* pins */
#define RESET_PIN 6
#define PAUSE_PIN 8
#define RAIN_PIN 9
#define TEMP_PIN A4
#define TEMP_VOLTAGE 3.274

/* hardware-specific constants */
#define GAUGE_STD 0.11
#define GAUGE_MET 0.2794
#define BRIGHTNESS 0

/* math constants */
#define MINUTE_MS 60000

using namespace components;

/* define variables */  // TODO: change all these to pointers where appropriate
float rainStd = 0.0;
float rainMet = 0.0;
bool updateFlag = true;
String inches, millimeters;
bool paused = false;
const char* holdMsg = "PAUSED";
String tempF;
String tempC;
unsigned long count;

/* initialize components */
Button resetButton = Button(RESET_PIN, 50, HIGH);
Button rainGauge = Button(RAIN_PIN, 50, HIGH);
Button holdButton = Button(PAUSE_PIN, 50, HIGH);
Temp36 tempSensor = Temp36(TEMP_PIN, TEMP_VOLTAGE);

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
    if (!updateFlag) {
        return;
    } else {
        inches = String(rainStd) + "\"";
        millimeters = String(rainMet) + "mm";
        tempF = tempSensor.tempF();
        tempC = tempSensor.tempC();

        lcd.clear();

        lcd.print(inches);
        lcd.setCursor(8, 0);
        lcd.print(tempF);

        lcd.setCursor(0, 1);
        lcd.print(millimeters);
        lcd.setCursor(8, 1);
        lcd.print(tempC);

        updateFlag = false;
    }
}

// reset rain counters to zero
void handleReset() {
    rainStd = 0;
    rainMet = 0;
    updateLCD();
}

// increment the rain counters
void handleRainGauge() {
    rainStd += GAUGE_STD;
    rainMet += GAUGE_MET;
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

void setup() {
    prepLCD();
    tempSensor.measure();
}

void loop() {
    if (!paused) {
        if (resetButton.isPressed()) handleReset();
        if (rainGauge.isPressed()) handleRainGauge();
    }

    if (holdButton.isPressed()) handlePause();

    if ((millis() - count) > (MINUTE_MS)) {
        tempSensor.measure();
        count = millis();
        updateFlag = true;
    }

    handleUpdateLCD();
}
