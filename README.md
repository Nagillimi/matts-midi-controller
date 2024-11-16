# MIDI Digital Pin Scanner

## Goals

- [x] octave sequence dsa
- [ ] octave multiplier. (ex: `int octave[] = {-36, -24, -12, 1, 12, 24, 36}` to alter each key signal)
- [ ] MIDI output
- [ ] misc buttons and knobs for extra MIDI configs

## Setup

### Set latency

`#define LATENCY_MICROS 10000`

### Set Pin Map

`SynthKey` expects a note `String` and a digital pin `uint8_t`.

Initialized as a single octave:

```cpp
SynthKey *keys[12] = {
    new SynthKey("C", 1),
    new SynthKey("C_SHARP", 15),
    new SynthKey("D", 2),
    new SynthKey("E_FLAT", 14),
    new SynthKey("E", 3),
    new SynthKey("F", 4),
    new SynthKey("F_SHARP", 5),
    new SynthKey("G", 6),
    new SynthKey("A_FLAT", 7),
    new SynthKey("A", 8),
    new SynthKey("B_FLAT", 9),
    new SynthKey("B", 10),
};
```

## Example Output

```
Streaming...
12291004        1       1       1       0       1       1       1       1       1       1       1       1
12301004        1       1       1       0       1       1       1       1       1       1       1       1
12311004        1       1       1       0       1       1       1       1       1       1       1       1
12321004        1       1       1       0       1       1       1       1       1       1       1       1
12331004        1       1       1       0       1       1       1       1       1       1       1       1
12341004        1       1       1       0       1       1       1       1       1       1       1       1
12351004        1       1       1       0       1       1       1       1       1       1       1       1
12361004        1       1       1       0       1       1       1       1       1       1       1       1
12371004        1       1       1       0       1       1       1       1       1       1       1       1
12381004        1       0       1       0       1       1       1       1       1       1       1       1
12391004        1       0       1       0       1       1       1       1       1       1       1       1
12401004        1       0       1       1       1       1       1       1       1       1       1       1
12411004        1       0       1       1       1       1       1       1       1       1       1       1
12421004        1       0       1       1       1       1       1       1       1       1       1       1
12431004        1       0       1       1       1       1       1       1       1       1       1       1
12441004        1       0       1       1       1       1       1       1       1       1       1       1
12451004        1       0       1       1       1       1       1       1       1       1       1       1
12461004        1       0       1       1       1       1       1       1       1       1       1       1
```
