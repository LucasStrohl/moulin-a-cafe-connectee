#include <Arduino.h>
#include "BitMask.h"

BitMask::BitMask(){}

BitMask::BitMask(int _pin1, int _pin2, int _pin3){
    pin1 = pow(2,_pin1);
    pin2 = pow(2,_pin1);
    pin3 = pow(2,_pin3);

    mask = pin1+pin2+pin3;
}

uint64_t BitMask::DecToHex(){
    uint64_t maskHex = mask;
    return maskHex;   
}