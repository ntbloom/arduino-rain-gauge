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

/* specify the board to be used */
#include "boards/mkr1000.hpp"

/* hardware-specific constants */
#define GAUGE_STD 0.11
#define GAUGE_MET 0.2794
#define TEMP_INTERVAL 3  // TODO: make this way shorter

using components::Button;
using components::Raingauge;
using components::Temp36;
using utilities::Timer;

/* define variables */
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
    analogWrite(A3, 0);
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
void handleRainGauge() {
    rainGauge->addCount();
    updateLCD();
}

/* flag the LCD screen to update */
void updateLCD() {
    if (!updateFlag) {
        updateFlag = true;
    }
}

/* don't increment counters on click, display pause message on screen */
void handlePause() {
    if (paused) {
        // unpause the screen
        paused = false;
        updateLCD();
    } else {
        // pause the screen
        paused = true;
        lcd.clear();
        lcd.print("PAUSED");
    }
}

/* take temperature measurement and update LCD */
void handleMeasureTemp() {
    tempSensor->measure();
    updateLCD();
}

/*  Begin setup and main loop */
void setup() {
    prepLCD();
    tempSensor->measure();
    delay(1000);
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
