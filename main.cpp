/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
DigitalIn sw(PH_1);

int main()
{
    // Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif
    int button;

    while (true) {

        if(sw.read())
        {
            led = true;
            printf("LED ALLUMEE\n");
        }
        else {
            led = false;
            printf("LED ETEINTE\n");
        }
        
        //ThisThread::sleep_for(BLINKING_RATE);
    }
}
