#pragma once

class Button{
   public: 
      int pin;
      int state;
      Button();
      Button(int _pin);

      void Check();
};