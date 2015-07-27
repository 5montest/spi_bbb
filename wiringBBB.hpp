#ifndef HEAD_WIRINGBBB
#define HEAD_WIRINGBBB


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef enum{
    INPUT,
    OUTPUT,
    AINPUT,
    AOUTPUT
}DIRECTION;

typedef enum{
    LOW = 0,
    HIGH = 1
}STATE;

void pinMode(int pin, DIRECTION direction);

int digitalRead(int pin);
void digitalWrite(int pin, STATE state);
int analogRead(int pin);
void analogWrite(int pin, int value);

#endif // HEAD_WIRINGBBB
