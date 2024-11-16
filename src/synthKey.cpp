#include <Arduino.h>
#include "synthKey.h"

SynthKey::SynthKey(String const &_note, uint8_t const &_pin) {
    note = _note;
    pin = _pin;
    pinMode(pin, INPUT);
}

uint8_t SynthKey::getSignal() {
    return signal;
}


void SynthKey::assignSignal() {
    signal = digitalRead(pin);
}

void SynthKey::sendSignalMIDI() {
    // send signal via MIDI
}
