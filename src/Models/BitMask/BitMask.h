#pragma once

#define _HEX

class BitMask{
   public: 
      int mask;
      int pin1;
      int pin2;
      int pin3;
      BitMask();
      BitMask(int _pin1, int _pin2, int pin_3);

      int DecToHex();
};