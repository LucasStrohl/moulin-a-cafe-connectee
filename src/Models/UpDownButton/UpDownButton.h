#include "../Button/Button.h"

#ifndef BUTTON_H
#define BUTTON_H

class UpDownButton : public Button
{
    private:
        bool incr;
    public:
        UpDownButton();
        UpDownButton(int _pin, bool _incr);
        int IncrementCounter(int counter);
};

#endif