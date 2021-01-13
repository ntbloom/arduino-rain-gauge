#include "temp36.hpp"

using namespace components;

Temp36::Temp36(int pin, float voltage) {
    m_pin = pin;
    m_voltage = voltage;
}

// calculate the temperature, store values in memory
void Temp36::measure() {
    analogReadResolution(12);
    int reading = analogRead(m_pin);
    float intermed = reading * m_voltage / 4096;
    float tempC = (intermed - 0.5) * 100;  // 10mv per degree with 500 mV offset
    float tempF = (tempC * 9.0 / 5.0) + 32.0;

    m_valF = (int)tempF;
    m_valC = (int)tempC;
    m_tempF = String(m_valF) + "F";
    m_tempC = String(m_valC) + "C";
}

// getter for F, as string
String Temp36::tempF() { return m_tempF; }

// getter for C, as string
String Temp36::tempC() { return m_tempC; }

