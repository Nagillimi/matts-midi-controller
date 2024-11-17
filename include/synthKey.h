#ifndef SYNTHKEY_H
#define SYNTHKEY_H

#include <iostream>
#include <WString.h>
#include "inputKey.h"

class SynthKey: public InputKey {
private:
    String note;
    uint8_t pitch;

public:
    SynthKey(
        String const &_note,
        uint8_t const &_pin,
        uint8_t const &_pitch
    );
    
    uint8_t getPitch();
    void setPitch(uint8_t _pitch);
};

#endif // SYNTHKEY_H
