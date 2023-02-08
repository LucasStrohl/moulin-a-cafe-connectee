#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "./Models/Button/Button.h"
#include "./Models/UpDownButton/UpDownButton.h"
#include "./Models/Balance/Balance.h"
#include "./Models/Display/Display.h"


//Button
#define DownButtonPin 33
#define UpButtonPin 32
#define Ok_buttonPin 14

Button okButton;
UpDownButton downButton;
UpDownButton upButton;

//Balance
#define balancePinSCK 27
#define balancePinDT 26
Balance balance;

//Screen
Display display;

// Switch
#define signalSwitch 12

#define initialCounter 100
int counter = initialCounter;

void setup()
{
    Serial.begin(115200);
    Serial.println("Serial Begin !!!!!!!!!!!!!!!!!!!!!!!!");
    
    okButton = Button(Ok_buttonPin);
    downButton = UpDownButton(DownButtonPin, false);
    upButton = UpDownButton(UpButtonPin, true);

    balance = Balance(balancePinDT, balancePinSCK);

    display = Display(true);
    delay(500);
    display.Refresh(counter);

    pinMode(signalSwitch, OUTPUT);
}

void loop()
{
    downButton.Check();
    upButton.Check();
    okButton.Check();

    if (downButton.state == LOW)
    {
        counter = downButton.IncrementCounter(counter);
    }
    
    if (upButton.state == LOW)
    {
        counter = upButton.IncrementCounter(counter);
    }

    if (counter < 0)
    {
        counter = 0;
    }
    
    if (okButton.state == LOW)
    {
        balance.tare();
        float value = balance.getValue();
        display.PrintLoad(value, counter);
        digitalWrite(signalSwitch, HIGH);
        while (value < counter)
        {
            value = balance.getValue();
            display.PrintLoad(value, counter);
        }
        digitalWrite(signalSwitch, LOW);
        counter = initialCounter;
    }

    display.Refresh(counter);
    delay(120);
}