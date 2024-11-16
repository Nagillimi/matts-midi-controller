#include <Arduino.h>
#include "keys.h"
#include "synthKey.h"

#define LATENCY_MICROS 10000

void setup() {
    Serial.begin(115200);
    delay(1000);

    while (!Serial);
    Serial.println("Streaming...");
}

void loop() {
    uint32_t head = micros();

    Serial.print(head);
    Serial.print("\t");

    for (auto key: keys) {
        key->assignSignal();
        key->sendSignalMIDI();
        Serial.print(key->getSignal());
        Serial.print("\t");
    }

    Serial.println();

    while ((micros() - head) < LATENCY_MICROS);
}
