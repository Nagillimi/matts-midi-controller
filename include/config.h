#ifndef CONFIG_H
#define CONFIG_H

#include "controller.h"

#define SYNTH_COUNT 24
#define OCT_COUNT 2
#define PRG_COUNT 4
#define POT_COUNT 4

/**
 * EDIT THESE CONFIGS FOR YOUR PIN / HARDWARE SETUP
 */

// - MARK: SYNTH KEYS

/**
 * @brief Digital pins for piano keys (synth)
 * 
 * Assumes base C octave:
 * 
 * ```
 * [C, C#, D, D#, E, F, F#, G, G#, A, A#, B]
 * ```
 */
uint8_t synthPinList[SYNTH_COUNT] = {
     0,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12,
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
};

// - MARK: OCT KEYS

/**
 * @brief Octave key type list
 */
DirectionState octaveKeyList[OCT_COUNT] = {UP, DOWN};

/**
 * @brief Digital pins for octave keys
 */
uint8_t octavePinList[OCT_COUNT] = {36, 37};

// - MARK: PRG KEYS

/**
 * @brief MIDI control settings for control keys
 */
uint8_t programControlSettingList[PRG_COUNT] = {1, 2, 3, 4};

/**
 * @brief Digital pins for control keys
 */
uint8_t programPinList[PRG_COUNT] = {38, 39, 40, 41};

// - MARK: POTS

/**
 * @brief MIDI control settings for potentiometers
 */
uint8_t potControlSettingList[POT_COUNT] = {1, 2, 3, 4};

/**
 * @brief Analog pins for potentiometers
 */
uint8_t potPinList[POT_COUNT] = {A0, A1, A2, A3};

/**
 * @brief Analog pin for linear volume slide
 */
uint8_t volumePin = A4;

#endif
