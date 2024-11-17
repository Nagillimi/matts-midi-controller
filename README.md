# MIDI Digital Pin Scanner

## Goals

- [x] synth & key dsa
- [x] octave pitch multiplier
- [x] MIDI output
  - [x] teensy
  - [ ] arduino
- [ ] misc buttons and knobs for extra MIDI configs
- [ ] update current key state if octave is pressed while sustained

## Setup

### Set latency

`#define LATENCY_MICROS 10000`

### Set Pin Maps

`Synth` expects a few pin maps, initialized as a single octave:

```cpp
String synthKeyList[12] = {"C", "C_SHARP", "D", "E_FLAT", "E", "F", "F_SHARP", "G", "A_FLAT", "A", "B_FLAT", "B"};
uint8_t synthPinList[12] = {1, 39, 2, 38, 3, 4, 5, 6, 7, 8, 9, 10};
DirectionState octaveKeyList[2] = {UP, DOWN};
uint8_t octavePinList[2] = {36, 37};
```

## MIDI Definitions

Pitch designations for keys:

```cpp
                     MIDI NOTE NUMBERS 
        C   C#  D   D#  E   F   F#  G   G#  A   A#  B
    |------------------------------------------------
 -2 |   0   1   2   3   4   5   6   7   8   9  10  11
 -1 |  12  13  14  15  16  17  18  19  20  21  22  23
  0 |  24  25  26  27  28  29  30  31  32  33  34  35
  1 |  36  37  38  39  40  41  42  43  44  45  46  47
  2 |  48  49  50  51  52  53  54  55  56  57  58  59
  3 |  60  61  62  63  64  65  66  67  68  69  70  71
  4 |  72  73  74  75  76  77  78  79  80  81  82  83
  5 |  84  85  86  87  88  89  90  91  92  93  94  95
  6 |  96  97  98  99 100 101 102 103 104 105 106 107
  7 | 108 109 110 111 112 113 114 115 116 117 118 119
  8 | 120 121 122 123 124 125 126 127
```

## Example Output

Each pitch value and signal are updated together:

- Keys: [MIDI pitch, on signal]
- Octs: [0 Up/1 Down, on signal

```
Streaming...
4201052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 0]
4211052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 0]
4221052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 0]
4231052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 0]
4241052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 0]
4251052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 0] 
4261052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 1]    [1, 0] // OCTAVE UP!
4271052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 1]    [1, 0]
4281052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 1]    [1, 0]
4291052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 1]    [1, 0]
4301052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 1]    [1, 0]
4311052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 1]    [1, 0]
4321052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 1]    [1, 0]
4331052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4341052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4351052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4361052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4371052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4381052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4391052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4401052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4411052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4421052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 1]    [1, 0] // OCTAVE UP!
4431052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 1]    [1, 0]
4441052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 1]    [1, 0]
4451052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 1]    [1, 0]
4461052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 1]    [1, 0]
4471052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 1]    [1, 0]
4481052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 1]    [1, 0]
4491052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4501052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4511052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4521052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4531052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4541052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4551052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4561052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4571052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4581052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4591052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4601052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4611052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4621052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4631052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4641052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4651052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4661052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4671052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4681052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4691052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4701052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4711052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4721052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4731052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4741052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4751052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4761052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4771052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4781052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4791052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4801052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4811052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4821052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4831052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4841052         KEYS: [60, 1]   [61, 0] [62, 0] [63, 0] [64, 0] [65, 0] [66, 0] [67, 0] [68, 0] [69, 0] [70, 0] [71, 0]         OCTS: [0, 0]    [1, 0]
4851052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 1] // OCTAVE DOWN!
4861052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 1]
4871052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 1]
4881052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 1]
4891052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 1]
4901052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 1]
4911052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 1]
4921052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 1]
4931052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 1]
4941052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4951052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4961052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4971052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4981052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
4991052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
5001052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
5011052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
5021052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
5031052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
5041052         KEYS: [48, 1]   [49, 0] [50, 0] [51, 0] [52, 0] [53, 0] [54, 0] [55, 0] [56, 0] [57, 0] [58, 0] [59, 0]         OCTS: [0, 0]    [1, 0]
5051052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 1] // OCTAVE DOWN!
5061052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 1]
5071052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 1]
5081052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 1]
5091052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 1]
5101052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 1]
5111052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 1]
5121052         KEYS: [36, 1]   [37, 0] [38, 0] [39, 0] [40, 0] [41, 0] [42, 0] [43, 0] [44, 0] [45, 0] [46, 0] [47, 0]         OCTS: [0, 0]    [1, 1]
```
