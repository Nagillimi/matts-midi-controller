#ifndef INPUTKEY_H
#define INPUTKEY_H

#include <map>
#include <iostream>
#include <WString.h>
#include <Bounce.h>
#include "constants.h"

class InputKey: public Bounce {
protected:
    uint8_t pin;
    uint8_t signal;

public:
    InputKey(uint8_t const &_pin);
    void measure();

    uint8_t getSignal();
};

#endif // INPUTKEY_H
