#include "synthKey.h"

SynthKey::SynthKey(
    uint8_t const &_pitch,
    uint8_t const &_pin
) : InputKey(_pin) {
    pitch = _pitch;
}

uint8_t SynthKey::getPitch() {
    return pitch;
}

void SynthKey::setPitch(uint8_t _pitch) {
    pitch = _pitch;
}