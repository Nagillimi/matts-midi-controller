#include "octaveKey.h"

OctaveKey::OctaveKey(
    uint8_t const &_pin,
    DirectionState const & _direction
) : InputKey(_pin) {
    direction = _direction;
}

DirectionState OctaveKey::getDirection() {
    return direction;
}
