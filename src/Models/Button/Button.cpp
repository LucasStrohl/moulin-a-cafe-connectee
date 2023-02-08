#include <Arduino.h>
#include "Button.h"

Button::Button(){}

Button::Button(int _pin){
   pin = _pin;
   state = 1;
   pinMode(pin, INPUT_PULLUP);
}

void Button::Check(){
   state = digitalRead(pin);
   // Delay a little bit to avoid bouncing
   //delay(50);
}