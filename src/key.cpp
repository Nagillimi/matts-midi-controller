#include "key.h"

class Key {
private:
    PinMap pin;
    uint8_t signal;

public:
    Key(PinMap pin) {
        this->pin = pin;
    }

    uint8_t getSignal() {
        return this->signal;
    }

    PinMap getPin() {
        return this->pin;
    }

    void setupPin() {
        pinMode(this->pin, INPUT);
    }

    void assignSignal() {
        this->signal = digitalRead(this->pin);
    }

    void sendSignalMIDI() {
        // send signal over MIDI

    }
};
