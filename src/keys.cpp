#include "keys.h"

class Keys {
private:
    Key keys[12] = {
        Key(PinMap::C),
        Key(PinMap::C_SHARP),
        Key(PinMap::D),
        Key(PinMap::E_FLAT),
        Key(PinMap::E),
        Key(PinMap::F),
        Key(PinMap::F_SHARP),
        Key(PinMap::G),
        Key(PinMap::A_FLAT),
        Key(PinMap::A),
        Key(PinMap::B_FLAT),
        Key(PinMap::B),
    };

public:
    void setupPins() {
        for (auto key: this->keys) {
            key.setupPin();
        }
    }

    void assignSignals() {
        for (auto key: this->keys) {
            key.assignSignal();
        }
    }

    String printSignals() {
        String ret = "";
        for (auto key: this->keys) {
            ret += key.getPin() + ' ' + key.getSignal() + '\t';
        }
        return ret;
    }
    
    void sendSignalsMIDI() {
        for (auto key: this->keys) {
            key.sendSignalMIDI();
        }
    }
};