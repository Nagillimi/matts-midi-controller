#include <Arduino.h>
#include "inputKey.h"

InputKey::InputKey(uint8_t const &_pin) : Bounce(_pin, BUTTON_DEBOUNCE_MS) {
    pin = _pin;
    pinMode(pin, INPUT_PULLUP);
    signal = HIGH;
}

void InputKey::measure() {
    if (update()) {
        signal = signal == HIGH ? LOW : HIGH;
    }
}

uint8_t InputKey::getSignal() {
    return signal;
}
