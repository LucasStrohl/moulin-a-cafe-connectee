#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "Display.h"

Display::Display(){}

Display::Display(bool hello)
{
    display = Adafruit_SSD1306(width, height, &Wire, -1);
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    delay(2000);
    display.clearDisplay();

    display.setTextSize(5);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    // Display static text
    display.println("MCC");
    display.display();
}

void Display::Header()
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(40, 0);
    display.println("MCC");
}

void Display::PrintText(int size, int x, int y, String text)
{
    display.setTextSize(size);
    display.setTextColor(WHITE);
    display.setCursor(x, y);
    display.println(text);
}

void Display::Refresh(int counter)
{
    // Clear the buffer.
    display.clearDisplay();

    this->Header();
    
    this->PrintText(2, 0, 25, "+");
    this->PrintText(3, 45, 20, String(counter));
    this->PrintText(2, 115, 25, "-");
    this->PrintText(2, 40, 50, "OK");

    display.display();
}

void Display::PrintLoad(float load, float maxLoad)
{
    // Clear the buffer.
    display.clearDisplay();
    this->Header();


    if (load > maxLoad)
    {
        load = maxLoad;
    }

    float progress = (load * 100) / maxLoad;
    display.fillRect(5, 20, progress * 118 / 100, 20, WHITE);
    this->PrintText(1, 25, 45, String(int(load))+ " / " + String(int(maxLoad)) + " g");

    display.display();
}

void Display::Clear(){
    display.clearDisplay();
}