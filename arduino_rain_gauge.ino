/* arduino_rain_gauge.ino
 *
 * Increment rain gauge counter on click, display on screen
 *
 */

#define DEBUG false

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "src/button.hpp"
#include "src/raingauge.hpp"
#include "src/serial/static_serial_tlv.hpp"
#include "src/temp36.hpp"
#include "src/timer.hpp"

/* specify the board to be used */
#include "src/boards/mkr1000.hpp"

/* vendoring main from ArduinoCore-samd */
void initVariant() __attribute__((weak));
void initVariant() {
}
extern USBDeviceClass USBDevice;
extern "C" void __libc_init_array(void);

/* hardware-specific constants */
#define GAUGE_STD 0.11
#define GAUGE_MET 0.2794
#define TEMP_INTERVAL 3  // TODO: fix for reasonable production level

using components::Button;
using components::Raingauge;
using components::Temp36;
using tlv::StaticSerialTLV;
using utilities::Timer;

/* define variables */
bool updateFlag = true;
bool paused = false;
const char* holdMsg = "PAUSED";

/* initialize components */
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
Button* holdButton = new Button(PAUSE_PIN, 50, HIGH);
Temp36* tempSensor = new Temp36(TEMP_PIN, TEMP_VOLTAGE);
Timer* tempTimer = new Timer(TEMP_INTERVAL);
Raingauge* rainGauge = new Raingauge(RAIN_PIN, 50, GAUGE_MET, GAUGE_STD);
StaticSerialTLV* serialTLV = new StaticSerialTLV();

/* set up LEDs */
void prepLED() {
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
}

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

/* increment the rain counters */
void handleRainGauge() {
    rainGauge->addCount();
    serialTLV->sendRainEvent();
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
        serialTLV->sendUnpause();
        updateLCD();
        digitalWrite(LED_RED, 0);
    } else {
        // pause the screen
        paused = true;
        serialTLV->sendPause();
        lcd.clear();
        digitalWrite(LED_RED, 1);
        lcd.print("PAUSED");
    }
}

/* take temperature measurement and update LCD */
void handleMeasureTemp() {
    digitalWrite(LED_BLUE, 1);
    // don't measure if any buttons are open which could distort measurement
    while (holdButton->isOpen() || rainGauge->isOpen()) {
        return;
    }
    tempSensor->measure();
    tempSensor->sendTLVPacket();
    updateLCD();
    digitalWrite(LED_BLUE, 0);
}

/*
 *
 * write our own main() for better control
 *
 */

/* drop-in replacement for `setup()` from arduino core */
void customSetup() {
    delay(1000);  // wait for serial connection to pick up first
    prepLED();
    if (DEBUG) pinMode(DEBUG_TIMER_PIN, OUTPUT);
    prepLCD();
    tempSensor->measure();  // doesn't matter if the reading is incorrect, we just need a reference
                            // point for memory allocation
    serialTLV->sendHardReset();
}

/* drop-in replacement for `loop()` in arduino code */
void customLoop() {
    if (!paused) {
        if (rainGauge->isPressed()) handleRainGauge();
        if (tempTimer->ready()) handleMeasureTemp();
    }
    if (holdButton->isPressed()) handlePause();
    digitalWrite(LED_GREEN, (millis() / 5000) % 2);  // blink the LED every 5 seconds
    handleUpdateLCD();
}

/* vendored setup for samd chip */
void arduinoCoreSamdMain() {
    init();
    __libc_init_array();
    initVariant();
    delay(1);
#if defined(USBCON)
    USBDevice.init();
    USBDevice.attach();
#endif
}

int main() {
    arduinoCoreSamdMain();
    customSetup();

    /* the main loop */
    for (;;) {
        if (DEBUG) digitalWrite(DEBUG_TIMER_PIN, HIGH);
        customLoop();
        if (DEBUG) digitalWrite(DEBUG_TIMER_PIN, LOW);
        if (serialEventRun) serialEventRun();
    }
    return 0;
}
