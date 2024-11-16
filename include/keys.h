#ifndef PINMAP_H
#define PINMAP_H

#include <map>
#include <iostream>
#include <WString.h>
#include "synthKey.h"

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

#endif // PINMAP_H
