#include "synthKey.h"

SynthKey::SynthKey(
    String const &_note,
    uint8_t const &_pin,
    uint8_t const &_pitch
) : InputKey(_pin) {
    note = _note;
    pitch = _pitch;
}

uint8_t SynthKey::getPitch() {
    return pitch;
}

void SynthKey::setPitch(uint8_t _pitch) {
    pitch = _pitch;
}