#include "../Button/Button.h"
#include "UpDownButton.h"

UpDownButton::UpDownButton() : Button(){}

UpDownButton::UpDownButton(int _pin, bool _incr) : Button(_pin){
    pin = _pin;
    incr = _incr;
}

int UpDownButton::IncrementCounter(int counter){
    return incr ? counter += 1 : counter += -1; 
}
