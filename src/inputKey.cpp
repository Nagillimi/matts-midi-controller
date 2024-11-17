#include <Arduino.h>
#include "inputKey.h"

InputKey::InputKey(uint8_t const &_pin) {
    pin = _pin;
    pinMode(pin, INPUT);
    state = _HIGH; // pup resistor
}

uint8_t InputKey::getSignal() {
    return signal;
}

ButtonState InputKey::getState() {
    return state;
}

void InputKey::measure() {
    uint8_t prevSignal = signal;
    signal = digitalRead(pin);

    if (prevSignal == HIGH) {
        if (state == LOW) {
            state = _FALLING;
            return;
        }
        state = _HIGH;
    } else {
        if (state == HIGH) {
            state = _RISING;
            return;
        }
        state = _LOW;
    }
}
