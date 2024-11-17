#include <Arduino.h>
#include "synth.h"

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

#ifdef TEENSY
    MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);
#endif

String synthKeyList[12] = {"C", "C_SHARP", "D", "E_FLAT", "E", "F", "F_SHARP", "G", "A_FLAT", "A", "B_FLAT", "B"};
uint8_t synthPinList[12] = {1, 39, 2, 38, 3, 4, 5, 6, 7, 8, 9, 10};
DirectionState octaveKeyList[2] = {UP, DOWN};
uint8_t octavePinList[2] = {36, 37};

Synth *synth;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    delay(1000);

#ifdef TEENSY
    MIDI1.begin(MIDI_CHANNEL_OMNI);
#endif

    synth = new Synth(
        synthKeyList,
        synthPinList,
        octaveKeyList,
        octavePinList
    );

    while (!Serial);
    Serial.println("Streaming...");
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    uint32_t head = micros();

    Serial.print(head);
    Serial.print("\t\t");

    synth->scan();
    synth->process();
    // synth->emit(MIDI1);
    Serial.println(synth->print());

    digitalWrite(LED_BUILTIN, LOW);
    if ((micros() - head) > LATENCY_MICROS) {
        Serial.println("LATENCY_MICROS is too small (sampling too fast)");
        while (true);
    }

    while ((micros() - head) < LATENCY_MICROS);
}
