#ifndef CONTROLKEY_H
#define CONTROLKEY_H

#include "inputKey.h"
#include "constants.h"

class ControlKey: public InputKey {
private:
    uint8_t controlSetting;

public:
    ControlKey(uint8_t const &_pin, uint8_t const & _controlSetting);

    uint8_t getControlSetting();
    uint8_t getSignal();
};

#endif // CONTROLKEY_H
