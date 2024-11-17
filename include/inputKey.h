#ifndef INPUTKEY_H
#define INPUTKEY_H

#include <map>
#include <iostream>
#include <WString.h>
#include "state.h"

class InputKey {
protected:
    uint8_t pin;
    uint8_t signal;
    ButtonState state;

public:
    InputKey(uint8_t const &_pin);

    uint8_t getSignal();
    ButtonState getState();

    void measure();
};

#endif // INPUTKEY_H
