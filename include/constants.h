#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TEENSY 1

#define BUTTON_DEBOUNCE_MS 10

#ifndef TEENSY
#include <MIDIUSB.h>
#else
#include <MIDI.h>
#endif

#endif // CONSTANTS_H
