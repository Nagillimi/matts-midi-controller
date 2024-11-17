#ifndef OCTAVEKEY_H
#define OCTAVEKEY_H

#include <iostream>
#include <WString.h>
#include "state.h"
#include "inputKey.h"

class OctaveKey: public InputKey {
private:
    DirectionState direction;

public:
    OctaveKey(
        DirectionState const & _direction,
        uint8_t const &_pin
    );

    DirectionState getDirection();
};

#endif // OCTAVEKEY_H
