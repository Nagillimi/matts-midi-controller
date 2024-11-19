#include <Arduino.h>
#include "controller.h"

#ifdef TEENSY
    MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);
#endif

String synthKeyList[12] = {"C", "C_SHARP", "D", "E_FLAT", "E", "F", "F_SHARP", "G", "A_FLAT", "A", "B_FLAT", "B"};
uint8_t synthPinList[12] = {1, 39, 2, 38, 3, 4, 5, 6, 7, 8, 9, 10};

DirectionState octaveKeyList[2] = {UP, DOWN};
uint8_t octavePinList[2] = {36, 37};

uint8_t programKeyList[4] = {1, 2, 3, 4};
uint8_t programPinList[4] = {32, 33, 34, 35};

uint8_t potControlSettingList[4] = {1, 2, 3, 4};
uint8_t potPinList[4] = {32, 33, 34, 35};

Controller *controller;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    delay(1000);

#ifdef TEENSY
    MIDI1.begin(MIDI_CHANNEL_OMNI);
#endif

    controller = new Controller(
        synthKeyList,
        synthPinList,
        octaveKeyList,
        octavePinList,
        programKeyList,
        programPinList,
        potControlSettingList,
        potPinList
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
    // controller->emit(MIDI1);
    Serial.println(controller->print());

    digitalWrite(LED_BUILTIN, LOW);
    if ((micros() - head) > LATENCY_MICROS) {
        Serial.println("LATENCY_MICROS is too small (sampling too fast)");
        while (true);
    }

    while ((micros() - head) < LATENCY_MICROS);
}
