#include "controller.h"

Controller::Controller(
    uint8_t synthPinList[SYNTH_COUNT],
    DirectionState octaveKeyList[OCT_COUNT],
    uint8_t octavePinList[OCT_COUNT],
    uint8_t programControlSettingList[PRG_COUNT],
    uint8_t programPinList[PRG_COUNT],
    uint8_t potControlSettingList[POT_COUNT],
    uint8_t potPinList[POT_COUNT],
    uint8_t volumePin
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
    for (i = 0; i < SYNTH_COUNT; i++) {
        synthKeys[i] = new SynthKey(synthPinList[i], FIRST_C + i);
    }
  
    for (i = 0; i < OCT_COUNT; i++) {
        octaveKeys[i] = new OctaveKey(octavePinList[i], octaveKeyList[i]);
    }

    for (i = 0; i < PRG_COUNT; i++) {
        programKeys[i] = new ControlKey(programPinList[i], programControlSettingList[i]);
    }

    for (i = 0; i < POT_COUNT; i++) {
        pots[i] = new Pot(potPinList[i], potControlSettingList[i]);
    }

    slide = new Pot(volumePin, MIDI_NAMESPACE::ChannelVolume); // 7
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

    slide->measure();
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
    emitSlide(midi);

    // ignore incoming MIDI messages, could perform tasks in the future
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

        const uint8_t correctedPitch = synthKey->getPitch() + SYNTH_COUNT * octaveSetting; 

        // list of pitches belonging to the note on all octaves
        const uint8_t rootPitch = correctedPitch % SYNTH_COUNT;
        uint8_t pitches[RANGE_OCTAVES];
        for (uint8_t i = 0; i < RANGE_OCTAVES; i++) {
            pitches[i] = rootPitch + SYNTH_COUNT * i;
        }
#ifdef TEENSY
        if (isReleased) {
            for (auto pitch : pitches) {
                midi.sendNoteOff(pitch, 0, midiChannel);
            }
            return;
        }
        midi.sendNoteOn(correctedPitch, 99, midiChannel);
#else
        const uint8_t header = isPressed ? 0x09 : 0x08;
        const uint8_t byte1 = isPressed ? 0x90 : 0x80;
        const uint8_t velocity = isPressed ? 127 : 0;

        if (isReleased) {
            for (auto pitch : pitches) {
                midiEventPacket_t event = {
                    (uint8_t)(header),
                    (uint8_t)(byte1 | channel),
                    (uint8_t)(pitch),
                    (uint8_t)(velocity)
                };

                MidiUSB.sendMIDI(event);
            }
            return;
        }

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
        midi.sendControlChange(
            programKey->getControlSetting(),
            programKey->getSignal(),
            midiChannel
        );
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
        midi.sendControlChange(
            pot->getControlSetting(),
            pot->getSignal(),
            midiChannel
        );
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

void Controller::emitSlide(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi) {
    if (slide->isStill() || slide->isWithinDebouncePeriod()) {
        return;
    }
#ifdef TEENSY
    midi.sendControlChange(
        slide->getControlSetting(),
        slide->getSignal(),
        midiChannel
    );
#else
    midiEventPacket_t event = {
        (uint8_t)(0x0B),
        (uint8_t)(0xB0 | channel),
        (uint8_t)(slide->getControlSetting()),
        (uint8_t)(slide->getSignal())
    };

    MidiUSB.sendMIDI(event);
#endif
    slide->setLastEmitTs(millis());
}

String Controller::print() {
    String ret = "KEYS: ";
    for (auto synthKey : synthKeys) {
        ret += "[";
        ret += synthKey->getPitch() + SYNTH_COUNT * octaveSetting;
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

    ret += "\tVOL: ";
    ret += "[";
    ret += slide->getControlSetting();
    ret += ", ";
    ret += slide->getSignal();
    ret += "]\t";
    return ret;
}
