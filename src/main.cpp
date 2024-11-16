#include <Arduino.h>
#include "pinMap.h"
#include "keys.h"

#define LATENCY_MICROS 10000

Keys *keys;

void setup() {
    keys->setupPins();

    Serial.begin(115200);
}

void loop() {
    uint32_t head = micros();
    keys->assignSignals();
    // keys->sendSignalsMIDI();
    Serial.println(keys->printSignals());

    while ((micros() - head) < LATENCY_MICROS) {}
}
