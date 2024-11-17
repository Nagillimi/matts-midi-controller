#ifndef STATE_H
#define STATE_H

enum DirectionState {
    _UP,
    _DOWN,
};

enum ButtonState {
    _HIGH,
    _FALLING, // transitional
    _LOW,
    _RISING, // transitional
};

#endif // STATE_H
