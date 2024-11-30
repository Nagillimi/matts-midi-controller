#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <WString.h>
#include "synthKey.h"
#include "octaveKey.h"
#include "controlKey.h"
#include "pot.h"
#include "constants.h"
#include "config.h"

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
    SynthKey *synthKeys[SYNTH_COUNT];
    OctaveKey *octaveKeys[OCT_COUNT];
    ControlKey *programKeys[PRG_COUNT];
    Pot *pots[POT_COUNT];
    Pot *slide;

    void emitSynthKeys(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi);
    void emitProgramKeys(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi);
    void emitPots(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi);
    void emitSlide(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi);

public:
    Controller(
        uint8_t synthPinList[SYNTH_COUNT],
        DirectionState octaveKeyList[OCT_COUNT],
        uint8_t octavePinList[OCT_COUNT],
        uint8_t programControlSettingList[PRG_COUNT],
        uint8_t programPinList[PRG_COUNT],
        uint8_t potControlSettingList[POT_COUNT],
        uint8_t potPinList[POT_COUNT],
        uint8_t volumePin
    );
    void scan();
    void process();
    void emit(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi);
    String print();
};

#endif // CONTROLLER_H
