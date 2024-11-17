#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @brief Sampling latency in microseconds
 * 
 * Piano fNyq ~= 20Hz
 * 
 * 150Hz =  6,667us
 * 100Hz = 10,000us
 * 50Hz  = 20,000us
 */
#define LATENCY_MICROS 10000

/**
 * @brief Controller type
 * 
 * Currently it's either Tennsy or non-Teensy
 */
#define TEENSY 1

/**
 * @brief Button debounce timing 
 */
#define BUTTON_DEBOUNCE_MS 10


// Do not edit 

#ifndef TEENSY
#include <MIDIUSB.h>
#else
#include <MIDI.h>
#endif

#endif // CONSTANTS_H
