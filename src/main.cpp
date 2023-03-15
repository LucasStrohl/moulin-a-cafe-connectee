#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "./Models/Button/Button.h"
#include "./Models/UpDownButton/UpDownButton.h"
#include "./Models/Balance/Balance.h"
#include "./Models/Display/Display.h"
#include "./Models/BitMask/BitMask.h"


//Button

// ESP32
#define DownButtonPin 33
#define Ok_buttonPin 14
#define UpButtonPin 32

// ESP82
//#define DownButtonPin 14
//#define UpButtonPin 13
//#define Ok_buttonPin 12

// 2^33 = 8 589 934 592 2^32  2^32= 4 294 967 296  2^14= 16 384
//#define BUTTON_PIN_BITMASK 
BitMask BUTTON_PIN_BITMASK;

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

    BUTTON_PIN_BITMASK = BitMask(Ok_buttonPin, DownButtonPin, UpButtonPin);

    pinMode(signalSwitch, OUTPUT);
}

void LightSleep()
{
  Serial.print(BUTTON_PIN_BITMASK.DecToHex());
  esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK.DecToHex(), ESP_EXT1_WAKEUP_ANY_HIGH); // ext1 for more than one pin
  esp_light_sleep_start();
}

void loop()
{
    downButton.Check();
    upButton.Check();
    okButton.Check();

    if (downButton.state == LOW)
    {
        counter = downButton.IncrementCounter(counter);
        Serial.print("down button");
    }
    
    if (upButton.state == LOW)
    {
        counter = upButton.IncrementCounter(counter);
        Serial.print("up button");
    }

    if (counter < 0)
    {
        counter = 0;
    }
    
    if (okButton.state == LOW)
    {
        Serial.print("ok");
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

    Serial.println("is awake");
    delay(1000);
    Serial.println("going to sleep");
    delay(1000);

    LightSleep();
}