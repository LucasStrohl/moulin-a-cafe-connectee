#include "Balance.h"

Balance::Balance(){}

Balance::Balance(int _pinDataOut, int _pinCLK) {
    pinDataOut = _pinDataOut;
    pinCLK = _pinCLK;
    scale = 0;
    Serial.println("Initialisation de la balance...");
    balance.begin(pinDataOut, pinCLK);
    // Serial.print(balance.is_ready());
    // balance.set_scale(scale); //le paramètre dépend de votre cellule de charge.
    //this->defineScale();
    balance.set_scale(390);
    balance.tare(); //ajustement du zéro
    Serial.println("La balance est prete!");
}

void Balance::tare() {
    balance.tare();
}

float Balance::getValue() {
    return balance.get_units(10);
}

void Balance::defineScale() {
    balance.set_scale();
    balance.tare();
    scale = balance.get_units(10);
    balance.set_scale(scale);
    Serial.print("scale: ");
    Serial.println(scale);
}