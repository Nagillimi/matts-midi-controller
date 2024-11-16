#ifndef KEYS_H
#define KEYS_H

#include <Arduino.h>
#include "key.h"

class Keys {
private:
    Key keys[12];

public:
    void setupPins() {}
    void assignSignals() {}
    String printSignals() {}
    void sendSignalsMIDI() {}
};

#endif // KEYS_H
