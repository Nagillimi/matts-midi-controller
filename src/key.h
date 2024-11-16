#ifndef KEY_H
#define KEY_H

#include <Arduino.h>
#include "pinMap.h"

class Key {
private:
    PinMap pin;
    uint8_t signal;

public:
    Key(PinMap pin) {}
    uint8_t getSignal() {}
    PinMap getPin() {}
    void setupPin() {}
    void assignSignal() {}
    void sendSignalMIDI() {}
};

#endif // KEY_H
