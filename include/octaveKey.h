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
        uint8_t const &_pin,
        DirectionState const & _direction
    );

    DirectionState getDirection();
};

#endif // OCTAVEKEY_H
