#include <Arduino.h>
#include <MIDIUSB.h>
#include "synth.h"

Synth::Synth(
    String synthKeyList[12],
    uint8_t synthPinList[12],
    DirectionState octaveKeyList[2],
    uint8_t octavePinList[2]
) {
    octaveSetting = 0;

    midiChannel = 0;                // MIDI channel to be used - start with 1 for MIDI.h lib or 0 for MIDIUSB lib
    midiLowestNote = 36;            // Lowest note to be used
    midiLowestControlChange = 1;    // Lowest control change to be used

    // pin setup
    uint8_t i;
    for (i = 0; i < 12; i++) {
        synthKeys[i] = new SynthKey(synthKeyList[i], synthPinList[i], midiLowestNote + i);
        synthKeys[i]->setChannel(midiChannel);
    }

    for (i = 0; i < 2; i++) {
        octaveKeys[i] = new OctaveKey(octaveKeyList[i], octavePinList[i]);
    }
}

void Synth::scan() {
    for (auto synthKey : synthKeys) {
        synthKey->measure();
    }

    for (auto octaveKey : octaveKeys) {
        octaveKey->measure();
    }
}

void Synth::process() {
    // octaveKeys
    for (auto octaveKey : octaveKeys) {
        if (octaveKey->getState() != _FALLING) {
            continue;
        }
        octaveSetting += octaveKey->getDirection() == _UP ? 1 : -1;
    }

    // programmed buttons

    // programmed pots

    // programmed linear slides
}

void Synth::emit() {
    for (auto synthKey : synthKeys) {
        MidiUSB.sendMIDI(synthKey->constructEvent(octaveSetting));
    }
}

String Synth::print() {
    for (auto synthKey : synthKeys) {
        Serial.print("[");
        Serial.print(synthKey->getPitch());
        Serial.print(", ");
        Serial.print(synthKey->getSignal());
        Serial.print(", ");
        Serial.print(synthKey->getState());
        Serial.print("]\t");
    }

    for (auto octaveKey : octaveKeys) {
        octaveKey->measure();
    }
}