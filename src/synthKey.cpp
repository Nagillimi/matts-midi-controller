#include "synthKey.h"

SynthKey::SynthKey(
    String const &_note,
    uint8_t const &_pin,
    uint8_t const &_pitch
) : InputKey(_pin) {
    note = _note;
    pitch = _pitch;
}

void SynthKey::setChannel(uint8_t const &_channel) {
    channel = _channel;
}

uint8_t SynthKey::getPitch() {
    return pitch;
}

midiEventPacket_t SynthKey::constructEvent(uint8_t const &octaveSetting) {
    // guard non rising/falling events (sustain notes)
    if (state != _RISING || state != _FALLING) {
        return;
    }

    bool isNotePressed = state == _FALLING;

    const uint8_t header = isNotePressed ? 0x09 : 0x08;
    const uint8_t byte1 = isNotePressed ? 0x90 : 0x80;
    const uint8_t velocity = isNotePressed ? 127 : 0;

    midiEventPacket_t event = {
        (uint8_t)header,
        (uint8_t)(byte1 | channel),
        (uint8_t)(pitch + 12 * octaveSetting),
        (uint8_t)velocity
    };

    return event;
}
