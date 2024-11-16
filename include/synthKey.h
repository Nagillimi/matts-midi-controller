#ifndef SYNTHKEY_H
#define SYNTHKEY_H

#include <iostream>
#include <WString.h>

class SynthKey {
private:
    String note;
    uint8_t pin;
    uint8_t signal;

public:
    SynthKey(String const &_note, uint8_t const &_pin);
    uint8_t getSignal();
    void assignSignal();
    void sendSignalMIDI();
};

#endif // SYNTHKEY_H
