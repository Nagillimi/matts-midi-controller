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

/**
 * @brief Middle C MIDI pitch
 * 
 *                     MIDI NOTE NUMBERS 
 *        C   C#  D   D#  E   F   F#  G   G#  A   A#  B
 *    |------------------------------------------------
 * -2 |   0   1   2   3   4   5   6   7   8   9  10  11
 * -1 |  12  13  14  15  16  17  18  19  20  21  22  23
 *  0 |  24  25  26  27  28  29  30  31  32  33  34  35
 *  1 |  36  37  38  39  40  41  42  43  44  45  46  47
 *  2 |  48  49  50  51  52  53  54  55  56  57  58  59
 *  3 |  60  61  62  63  64  65  66  67  68  69  70  71
 *  4 |  72  73  74  75  76  77  78  79  80  81  82  83
 *  5 |  84  85  86  87  88  89  90  91  92  93  94  95
 *  6 |  96  97  98  99 100 101 102 103 104 105 106 107
 *  7 | 108 109 110 111 112 113 114 115 116 117 118 119
 *  8 | 120 121 122 123 124 125 126 127                  (<- ignored since partial)
 */
#define FIRST_C 24

/**
 * @brief Max octave shift, on a 24 key range starting from pitch 24
 */
#define MAX_OCTAVE_SETTING 3

/**
 * @brief Min octave shift, on a 24 key range starting from pitch 24
 */
#define MIN_OCTAVE_SETTING -1

/**
 * @brief Number of possible octave shifts available
 * 
 * Convenience constant, don't edit.
 */
#define RANGE_OCTAVES MAX_OCTAVE_SETTING - MIN_OCTAVE_SETTING

/**
 * @brief Analog threhold, [0, 1023] ADC
 */
#define POT_STILL_TH 10

/**
 * @brief Value from 0 to 1 that controls the amount of easing
 * 
 * increase this to lessen the amount of easing (such as 0.1) and make the responsive values more responsive
 * but doing so may cause more noise to seep through if sleep is not enabled
 */
#define POT_SNAP_MULTIPLIER 0.01

/**
 * @brief Debounce period in ms for each new pot signal to emit at 
 */
#define POT_DEBOUNCE_MS 300

#endif // CONSTANTS_H
