#include "synth.h"

/**
 * @brief Construct a new Synth:: Synth object
 * 
 * @param synthKeyList 
 * @param synthPinList 
 * @param octaveKeyList 
 * @param octavePinList
 * 
 *                     MIDI NOTE NUMBERS 
 *         C   C#  D   D#  E   F   F#  G   G#  A   A#  B
 *     |------------------------------------------------
 *  -2 |   0   1   2   3   4   5   6   7   8   9  10  11
 *  -1 |  12  13  14  15  16  17  18  19  20  21  22  23
 *   0 |  24  25  26  27  28  29  30  31  32  33  34  35
 *   1 |  36  37  38  39  40  41  42  43  44  45  46  47
 *   2 |  48  49  50  51  52  53  54  55  56  57  58  59
 *   3 |  60  61  62  63  64  65  66  67  68  69  70  71
 *   4 |  72  73  74  75  76  77  78  79  80  81  82  83
 *   5 |  84  85  86  87  88  89  90  91  92  93  94  95
 *   6 |  96  97  98  99 100 101 102 103 104 105 106 107
 *   7 | 108 109 110 111 112 113 114 115 116 117 118 119
 *   8 | 120 121 122 123 124 125 126 127
 */


Synth::Synth(
    String synthKeyList[12],
    uint8_t synthPinList[12],
    DirectionState octaveKeyList[2],
    uint8_t octavePinList[2]
) {
    octaveSetting = 0;

    // MIDI channel to be used - start with 1 for MIDI.h lib or 0 for MIDIUSB lib
#ifdef TEENSY
    midiChannel = 1;
#else
    midiChannel = 0;
#endif

    midiLowestNote = 36;
    midiLowestControlChange = 1;

    // pin setup
    uint8_t i;
    for (i = 0; i < 12; i++) {
        synthKeys[i] = new SynthKey(synthKeyList[i], synthPinList[i], midiLowestNote + i);
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
        // guard for only button press events
        if (!octaveKey->fallingEdge()) {
            continue;
        }
        octaveSetting += octaveKey->getDirection() == UP ? 1 : -1;
    }

    // TODO: programmed buttons

    // TODO: programmed pots

    // TODO: programmed linear slides

}

void Synth::emit(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> midi) {

    for (auto synthKey : synthKeys) {
        bool isNotePressed = synthKey->fallingEdge();
        bool isNoteReleased = synthKey->risingEdge();

        // guard non rising/falling events (sustain notes)
        if (!isNotePressed || !isNoteReleased) {
            return;
        }

        const uint8_t correctedPitch = synthKey->getPitch() + 12 * octaveSetting;
#ifdef TEENSY
        isNotePressed
            ? midi.sendNoteOn(correctedPitch, 99, midiChannel)
            : midi.sendNoteOff(correctedPitch, 0, midiChannel);
#else
        const uint8_t header = isNotePressed ? 0x09 : 0x08;
        const uint8_t byte1 = isNotePressed ? 0x90 : 0x80;
        const uint8_t velocity = isNotePressed ? 127 : 0;

        midiEventPacket_t event = {
            (uint8_t)header,
            (uint8_t)(byte1 | channel),
            (uint8_t)correctedPitch,
            (uint8_t)velocity
        };

        MidiUSB.sendMIDI(event);
#endif
    }

    // ignore incoming MIDI messages
#ifdef TEENSY
    while (midi.read());
#else
    while(MidiUSB.read());
#endif
}

String Synth::print() {
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

    return ret;
}