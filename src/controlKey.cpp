#include "controlKey.h"

ControlKey::ControlKey(
    uint8_t const &_pin,
    uint8_t const & _controlSetting
) : InputKey(_pin) {
    pin = _pin;
    controlSetting = _controlSetting;
}

uint8_t ControlKey::getControlSetting() {
    return controlSetting;
}

uint8_t ControlKey::getSignal() {
    return signal;
}
