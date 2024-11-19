#include "controller.h"

Controller::Controller(
    String synthKeyList[12],
    uint8_t synthPinList[12],
    DirectionState octaveKeyList[2],
    uint8_t octavePinList[2],
    uint8_t programControlSettingList[4],
    uint8_t programPinList[4],
    uint8_t potControlSettingList[4],
    uint8_t potPinList[4]
) {
    octaveSetting = 0;

    // MIDI channel to be used - start with 1 for MIDI.h lib or 0 for MIDIUSB lib
#ifdef TEENSY
    midiChannel = 1;
#else
    midiChannel = 0;
#endif

    midiLowestControlChange = 1;

    // pin setup
    uint8_t i;
    for (i = 0; i < 12; i++) {
        synthKeys[i] = new SynthKey(synthKeyList[i], synthPinList[i], MIDDLE_C + i);
    }
  
    for (i = 0; i < 2; i++) {
        octaveKeys[i] = new OctaveKey(octaveKeyList[i], octavePinList[i]);
    }

    for (i = 0; i < 4; i++) {
        programKeys[i] = new ControlKey(programPinList[i], programControlSettingList[i]);
    }

    for (i = 0; i < 4; i++) {
        pots[i] = new Pot(potPinList[i], potControlSettingList[i]);
    }
}

void Controller::scan() {
    for (auto synthKey : synthKeys) {
        synthKey->measure();
    }

    for (auto octaveKey : octaveKeys) {
        octaveKey->measure();
    }

    for (auto programKey : programKeys) {
        programKey->measure();
    }

    for (auto pot : pots) {
        pot->measure();
    }
}

void Controller::process() {
    // apply octave setting
    for (auto octaveKey : octaveKeys) {
        // guard for only button press events
        if (!octaveKey->fallingEdge()) {
            continue;
        }
        octaveSetting += octaveKey->getDirection() == UP ? 1 : -1;
    }

    // clamp
    octaveSetting = octaveSetting > MAX_OCTAVE_SETTING
        ? MAX_OCTAVE_SETTING
        : octaveSetting < MIN_OCTAVE_SETTING
            ? MIN_OCTAVE_SETTING
            : octaveSetting;
}

void Controller::emit(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi) {
    emitSynthKeys(midi);
    emitProgramKeys(midi);
    emitPots(midi);

    // ignore incoming MIDI messages
#ifdef TEENSY
    while (midi.read());
#else
    while(MidiUSB.read());
#endif
}

void Controller::emitSynthKeys(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi) {
    for (auto synthKey : synthKeys) {
        bool isPressed = synthKey->fallingEdge();
        bool isReleased = synthKey->risingEdge();

        // guard non rising/falling events (sustain notes)
        if (!isPressed || !isReleased) {
            continue;
        }

        const uint8_t correctedPitch = synthKey->getPitch() + 12 * octaveSetting;
#ifdef TEENSY
        isPressed
            ? midi.sendNoteOn(correctedPitch, 99, midiChannel)
            : midi.sendNoteOff(correctedPitch, 0, midiChannel);
#else
        const uint8_t header = isPressed ? 0x09 : 0x08;
        const uint8_t byte1 = isPressed ? 0x90 : 0x80;
        const uint8_t velocity = isPressed ? 127 : 0;

        midiEventPacket_t event = {
            (uint8_t)(header),
            (uint8_t)(byte1 | channel),
            (uint8_t)(correctedPitch),
            (uint8_t)(velocity)
        };

        MidiUSB.sendMIDI(event);
#endif
    }
}

void Controller::emitProgramKeys(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi) {
    for (auto programKey : programKeys) {
        bool isPressed = programKey->fallingEdge();
        bool isReleased = programKey->risingEdge();

        // guard non rising/falling events (sustain notes)
        if (!isPressed || !isReleased) {
            continue;
        }

#ifdef TEENSY
        // TODO: how to emit program buttons
        // isPressed
        //     ? midi.sendNoteOn(correctedPitch, 99, midiChannel)
        //     : midi.sendNoteOff(correctedPitch, 0, midiChannel);
#else
        const uint8_t header = isPressed ? 0x09 : 0x08;
        const uint8_t byte1 = isPressed ? 0x90 : 0x80;
        const uint8_t velocity = isPressed ? 127 : 0;

        midiEventPacket_t event = {
            (uint8_t)(header),
            (uint8_t)(byte1 | channel),
            (uint8_t)(correctedPitch),
            (uint8_t)(velocity)
        };

        MidiUSB.sendMIDI(event);
#endif
    }
}

void Controller::emitPots(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi) {
    for (auto pot : pots) {
        if (pot->isStill() || pot->isWithinDebouncePeriod()) {
            continue;
        }
#ifdef TEENSY
    midi.sendControlChange(pot->getControlSetting(), pot->getSignal(), midiChannel);
#else
        midiEventPacket_t event = {
            (uint8_t)(0x0B),
            (uint8_t)(0xB0 | channel),
            (uint8_t)(pot->getControlSetting()),
            (uint8_t)(pot->getSignal())
        };

        MidiUSB.sendMIDI(event);
#endif
    pot->setLastEmitTs(millis());
    }
}

String Controller::print() {
    String ret = "KEYS: ";
    for (auto synthKey : synthKeys) {
        ret += "[";
        ret += synthKey->getPitch() + 12 * octaveSetting;
        ret += ", ";
        ret += synthKey->getSignal();
        ret += "]\t";
    }

    ret += "\tOCTS: ";
    for (auto octaveKey : octaveKeys) {
        ret += "[";
        ret += octaveKey->getDirection();
        ret += ", ";
        ret += octaveKey->getSignal();
        ret += "]\t";
    }

    ret += "\tPRGS: ";
    for (auto programKey : programKeys) {
        ret += "[";
        ret += programKey->getControlSetting();
        ret += ", ";
        ret += programKey->getSignal();
        ret += "]\t";
    }

    ret += "\tPOTS: ";
    for (auto pot : pots) {
        ret += "[";
        ret += pot->getControlSetting();
        ret += ", ";
        ret += pot->getSignal();
        ret += "]\t";
    }

    return ret;
}
