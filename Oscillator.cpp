#include "Oscillator.h"


short Oscillator::val()
{
    short res;
    res = sin((freq/(double)counter)*(2*PI));
    counter++;
    if (counter > 1024) counter -= 1024;
    return res;
}

Oscillator::~Oscillator()
{
    //dtor
}
