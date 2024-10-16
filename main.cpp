/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
InterruptIn button(PH_1);
DigitalOut led(LED1);

void flip()
{
    led = !led;
}

int main()
{
    button.rise(&flip);  // attach the address of the flip function to the rising edge
    while (1) {          // wait around, interrupts will interrupt this!
        ThisThread::sleep_for(250);
    }
}




