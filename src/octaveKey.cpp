#include "octaveKey.h"

OctaveKey::OctaveKey(
    DirectionState const & _direction,
    uint8_t const &_pin
) : InputKey(_pin) {
    direction = _direction;
}

DirectionState OctaveKey::getDirection() {
    return direction;
}
