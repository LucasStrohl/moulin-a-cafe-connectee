#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <esp_sleep.h>
#include "./Models/Button/Button.h"
#include "./Models/UpDownButton/UpDownButton.h"
#include "./Models/Balance/Balance.h"
#include "./Models/Display/Display.h"
#include "./Models/BitMask/BitMask.h"

//Button

// ESP32
#define DownButtonPin 33
#define UpButtonPin 32
#define Ok_buttonPin 14 

// 2^33 = 8 589 934 592 2^32  2^32= 4 294 967 296  2^14= 16 384
#define BUTTON_PIN_BITMASK 0x300004000
//BitMask BUTTON_PIN_BITMASK;

Button okButton;
UpDownButton downButton;
UpDownButton upButton;

//Balance
// ESP32
#define balancePinSCK 27
#define balancePinDT 26
Balance balance;

//Screen
Display display;

// Switch
#define signalSwitch 12

#define initialCounter 100
int counter = initialCounter;

unsigned long time_start;
unsigned long previousMillis=0;

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial Begin !!!!!!!!!!!!!!!!!!!!!!!!");
    
    okButton = Button(Ok_buttonPin);
    downButton = UpDownButton(DownButtonPin, false);
    upButton = UpDownButton(UpButtonPin, true);

    balance = Balance(balancePinDT, balancePinSCK);

    display = Display(true);
    delay(500);
    display.Refresh(counter);

    //BUTTON_PIN_BITMASK = BitMask(Ok_buttonPin, DownButtonPin, UpButtonPin);

    pinMode(signalSwitch, OUTPUT);
}
void LightSleep()
{
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, LOW);
    display.Clear();
    esp_light_sleep_start();
}

void loop()
{
    time_start = millis();
    if ((unsigned long)(time_start - previousMillis) >= 10000) {
        previousMillis = time_start;
        Serial.println("is asleep");
        display.Clear();
        LightSleep();
    }

    downButton.Check();
    upButton.Check();
    delay(100);
    okButton.Check();

    if (downButton.state == LOW)
    {
        counter = downButton.IncrementCounter(counter);
        //Serial.println("down button");
    }

    if (upButton.state == LOW)
    {
        counter = upButton.IncrementCounter(counter);
        //Serial.println("up button");
    }

    if (counter < 0)
    {
        counter = 0;
    }

    if (okButton.state == HIGH)
    {
        previousMillis = time_start;
        Serial.println("ok");
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
        display.Clear();
    }

    display.Refresh(counter);
    delay(120);

}