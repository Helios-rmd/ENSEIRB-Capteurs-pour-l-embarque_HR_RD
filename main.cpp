/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"




using namespace std::chrono;

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
InterruptIn button(BUTTON1);
DigitalOut led(LED1);
Timer t;
Ticker flipper; 
bool flag; 

void start_counting()
{
    t.start();
    //led = true;
}

void end_counting()
{
    t.stop();
    //led = false;
    flag = true;
}

void flip_led()
{
    led = !led;
}

int main()
{
    // interrupt when the button is pressed/released
    button.rise(&start_counting);  
    button.fall(&end_counting);
    // ticker interruption. Call flip_led every 1s
    flipper.attach(&flip_led, 500ms);

    while (1) {          // wait around, interrupts will interrupt this!
        if(flag){
            printf("The button was pressed during %llu ms\n", duration_cast<milliseconds>(t.elapsed_time()).count());
            flag = false; 
            t.reset();
        }
        ThisThread::sleep_for(250ms);
    }
}




