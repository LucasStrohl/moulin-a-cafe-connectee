#pragma once

#include <Arduino.h>
#include <HX711.h>

class Balance {
    public:
        int pinDataOut;
        int pinCLK;
        int scale;
        HX711 balance;

        Balance();
        Balance(int _pinDataOut, int _pinCLK);

        void tare();
        float getValue();
        void defineScale();
};
