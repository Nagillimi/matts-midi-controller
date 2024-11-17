#ifndef SYNTH_H
#define SYNTH_H

#include <iostream>
#include <WString.h>
#include "synthKey.h"
#include "octaveKey.h"

class Synth {
private:
    uint8_t octaveSetting;
    uint8_t midiChannel;
    uint8_t midiLowestNote;
    uint8_t midiLowestControlChange;
    SynthKey *synthKeys[12];
    OctaveKey *octaveKeys[2];

public:
    Synth(
        String synthKeyList[12],
        uint8_t synthPinList[12],
        DirectionState octaveKeyList[2],
        uint8_t octavePinList[2]
    );
    void scan();
    void process();
    void emit();
    String print();
};

#endif // SYNTH_H
