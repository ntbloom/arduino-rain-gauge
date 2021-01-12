#include "temp36.hpp"

using namespace components;

Temp36::Temp36(int pin, float voltage) {
    m_pin = pin;
    m_voltage = voltage;
}

// calculate the temperature, store values in memory
void Temp36::measure() {
    int reading = analogRead(m_pin);
    float intermed = reading * m_voltage / 1024;
    float tempC = (intermed - 0.5) * 100;  // 10mv per degree with 500 mV offset
    float tempF = (tempC * 9.0 / 5.0) + 32.0;

    m_valF = (int)tempF;
    m_valC = (int)tempC;
    m_tempF = String(m_valF) + "F";
    m_tempC = String(m_valC) + "C";
}

// getter for F
int tempF() { return m_tempF; }

// getter for C
int tempC() { return m_tempC; }
