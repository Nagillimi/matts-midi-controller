#ifndef SYNTHKEY_H
#define SYNTHKEY_H

#include <iostream>
#include <WString.h>
#include <MIDIUSB.h>
#include "inputKey.h"

class SynthKey: public InputKey {
private:
    String note;
    uint8_t channel;
    uint8_t pitch;
    uint8_t velocity;

public:
    SynthKey(
        String const &_note,
        uint8_t const &_pin,
        uint8_t const &_pitch
    );
    
    void setChannel(uint8_t const &_channel);
    uint8_t getPitch();
    midiEventPacket_t constructEvent(uint8_t const &octaveSetting);
};

#endif // SYNTHKEY_H
