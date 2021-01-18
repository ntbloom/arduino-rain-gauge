/* arduino_rain_gauge.ino
 *
 * Increment rain gauge counter on click, display on screen
 *
 */

#include <LiquidCrystal.h>

#include "src/button.hpp"
#include "src/raingauge.hpp"
#include "src/temp36.hpp"
#include "src/timer.hpp"

/* pins */
#define RESET_PIN 6
#define PAUSE_PIN 8
#define RAIN_PIN 9
#define TEMP_PIN A4
#define LCD_RS_PIN 12
#define LCD_EN_PIN 11
#define LCD_D4_PIN 2
#define LCD_D5_PIN 3
#define LCD_D6_PIN 4
#define LCD_D7_PIN 5

/* hardware-specific constants */
#define GAUGE_STD 0.11
#define GAUGE_MET 0.2794
#define BRIGHTNESS 0
#define TEMP_INTERVAL 10
#define TEMP_VOLTAGE 3.274

using components::Button;
using components::Raingauge;
using components::Temp36;
using utilities::Timer;

/* define variables */  // TODO: change all these to pointers where appropriate
bool updateFlag = true;
bool paused = false;
const char* holdMsg = "PAUSED";

/* initialize components */
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
Button* resetButton = new Button(RESET_PIN, 50, HIGH);
Button* holdButton = new Button(PAUSE_PIN, 50, HIGH);
Temp36* tempSensor = new Temp36(TEMP_PIN, TEMP_VOLTAGE);
Timer* tempTimer = new Timer(TEMP_INTERVAL);

Raingauge* rainGauge = new Raingauge(RAIN_PIN, 50, GAUGE_MET, GAUGE_STD);

/* set up the LCD screen */
void prepLCD() {
    analogWrite(A3, BRIGHTNESS);
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print(0);
}

/* update the LCD screen if there were any changes */
void handleUpdateLCD() {
    if (!updateFlag) {
        return;
    } else {
        lcd.clear();

        lcd.print(rainGauge->inches());
        lcd.setCursor(8, 0);
        lcd.print(tempSensor->tempF());

        lcd.setCursor(0, 1);
        lcd.print(rainGauge->millimeters());
        lcd.setCursor(8, 1);
        lcd.print(tempSensor->tempC());

        updateFlag = false;
    }
}

/* reset rain counters to zero */
void handleReset() {
    rainGauge->resetCount();
    updateLCD();
}

/* increment the rain counters */
void handleRainGauge() { updateLCD(); }

/* flag the LCD screen to update */
void updateLCD() {
    if (!updateFlag) {
        updateFlag = true;
    }
}

/* don't increment counters on click, display pause message on screen */
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

/* take temperature measurement and update LCD */
void handleMeasureTemp() {
    tempSensor->measure();
    updateFlag = true;
}

/*  Begin the main loop  */

void setup() {
    prepLCD();
    tempSensor->measure();
}

void loop() {
    if (!paused) {
        if (resetButton->isPressed()) handleReset();
        if (rainGauge->isPressed()) handleRainGauge();
        if (tempTimer->ready()) handleMeasureTemp();
    }
    if (holdButton->isPressed()) handlePause();

    handleUpdateLCD();
}
