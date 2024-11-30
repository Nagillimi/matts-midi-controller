#include <Arduino.h>
#include "config.h"

#ifdef TEENSY
    MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);
#endif

Controller *controller;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    delay(1000);

#ifdef TEENSY
    MIDI1.begin(MIDI_CHANNEL_OMNI);
#endif

    controller = new Controller(
        synthPinList,
        octaveKeyList,
        octavePinList,
        programControlSettingList,
        programPinList,
        potControlSettingList,
        potPinList,
        volumePin
    );

    while (!Serial);
    Serial.println("Streaming...");
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    uint32_t head = micros();

    Serial.print(head);
    Serial.print("\t\t");

    controller->scan();
    controller->process();
    controller->emit(MIDI1);
    Serial.println(controller->print());

    digitalWrite(LED_BUILTIN, LOW);
    if ((micros() - head) > LATENCY_MICROS) {
        Serial.println("LATENCY_MICROS is too small (sampling too fast)");
        while (true);
    }

    while ((micros() - head) < LATENCY_MICROS);
}
