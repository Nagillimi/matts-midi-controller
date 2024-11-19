#ifndef POT_H
#define POT_H

#include <ResponsiveAnalogRead.h>
#include "constants.h"
#include "controlKey.h"

class Pot: public ResponsiveAnalogRead, public ControlKey {
private:
    uint8_t pin;
    uint8_t controlSetting;
    uint8_t raw;
    uint8_t prevRaw;
    uint8_t signal;
    bool moving;

public:
    uint32_t lastEmitTs;

    Pot(uint8_t const &_pin, uint8_t const & _controlSetting);

    uint8_t getControlSetting();
    uint8_t getSignal();
    void setLastEmitTs(uint32_t ts);

    void measure();
    bool isStill();
    bool isWithinDebouncePeriod();
};

#endif // POT_H
