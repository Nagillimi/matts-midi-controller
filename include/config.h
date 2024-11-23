#ifndef CONFIG_H
#define CONFIG_H

#include "controller.h"

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
uint8_t synthPinList[12] = {1, 39, 2, 38, 3, 4,  5, 6,  7, 8, 9, 10};

// - MARK: OCT KEYS

/**
 * @brief Octave key type list
 */
DirectionState octaveKeyList[2] = {UP, DOWN};

/**
 * @brief Digital pins for octave keys
 */
uint8_t octavePinList[2] = {36, 37};

// - MARK: PRG KEYS

/**
 * @brief MIDI control settings for control keys
 */
uint8_t programControlSettingList[4] = {1, 2, 3, 4};

/**
 * @brief Digital pins for control keys
 */
uint8_t programPinList[4] = {32, 33, 34, 35};

// - MARK: POTS

/**
 * @brief MIDI control settings for potentiometers
 */
uint8_t potControlSettingList[4] = {1, 2, 3, 4};

/**
 * @brief Analog pins for potentiometers
 */
uint8_t potPinList[4] = {32, 33, 34, 35};

#endif
