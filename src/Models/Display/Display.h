#pragma once
#include <Adafruit_SSD1306.h>

class Display{
    public: 
        Adafruit_SSD1306 display;
        Display();
        Display(bool hello);

        void PrintLoad(float load, float maxLoad);
        void PrintText(int size, int x, int y, String text);
        void Header();
        void Refresh(int counter);
        void Clear();

    private:
        int width = 128;
        int height = 64;
    
};