#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <WString.h>
#include "synthKey.h"
#include "octaveKey.h"
#include "controlKey.h"
#include "pot.h"
#include "constants.h"

// MIDI device layer
#ifndef TEENSY
#include <MIDIUSB.h>
#else
#include <MIDI.h>
#endif

// TODO: if supporting only Teensy controller type, inherit MIDI here
class Controller {
private:
    int8_t octaveSetting;
    uint8_t midiChannel;
    uint8_t midiLowestControlChange;
    SynthKey *synthKeys[12];
    OctaveKey *octaveKeys[2];
    ControlKey *programKeys[4];
    Pot *pots[4];

    void emitSynthKeys(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi);
    void emitProgramKeys(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi);
    void emitPots(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi);

public:
    Controller(
        uint8_t synthPinList[12],
        DirectionState octaveKeyList[2],
        uint8_t octavePinList[2],
        uint8_t programControlSettingList[4],
        uint8_t programPinList[4],
        uint8_t potControlSettingList[4],
        uint8_t potPinList[4]
    );
    void scan();
    void process();
    void emit(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi);
    String print();
};

#endif // CONTROLLER_H
