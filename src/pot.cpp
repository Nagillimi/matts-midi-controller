#include "pot.h"

Pot::Pot(
    uint8_t const &_pin,
    uint8_t const & _controlSetting
) : ResponsiveAnalogRead(_pin, true, POT_SNAP_MULTIPLIER),
    ControlKey(_pin, _controlSetting) {
    lastEmitTs = 0; // guarantees first emmission
    raw = 0;
    prevRaw = 0;
}

void Pot::setLastEmitTs(uint32_t ts) {
    lastEmitTs = ts;
}

void Pot::measure() {
    ResponsiveAnalogRead::update(); // same method name with Bounce class
    prevRaw = raw;
    raw = getValue();
    signal = map(raw, 0, 1023, 0, 99);
}

bool Pot::isStill() {
    return abs(prevRaw - raw) < POT_STILL_TH;
}

bool Pot::isWithinDebouncePeriod() {
    return abs(lastEmitTs - millis()) < POT_DEBOUNCE_MS;
}
