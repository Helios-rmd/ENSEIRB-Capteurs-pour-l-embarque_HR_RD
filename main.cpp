/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"




using namespace std::chrono;

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define BASE_FREQ         100ms
InterruptIn button(BUTTON1);
DigitalOut led(LED1);
Timer t;
Ticker flipper; 
bool flag;
int freq = 1; 

void start_counting()
{
    t.start();
    //led = true;
    // int used to modify led blinking frequency
    if(freq >= 6){
        freq = 1;
    }
    else{
        freq +=1;
    }
}

void end_counting()
{
    t.stop();
    //led = false;
    flag = true;
}

// Function called by ticker interruption to blink the LED 
void flip_led()
{
    led = !led;
}

int main()
{
    // interrupt when the button is pressed/released
    button.rise(&start_counting);  
    button.fall(&end_counting);
    // ticker interruption. Call flip_led every BASE_FREQ ms. 
    flipper.attach(&flip_led, BASE_FREQ);

    while (1) {          // wait around, interrupts will interrupt this!
        if(flag){
            printf("The button was pressed during %llu ms\n", duration_cast<milliseconds>(t.elapsed_time()).count());
            // Detach the flipper 
            flipper.detach();
            // Attach it with the new freq. 
            flipper.attach(&flip_led, BASE_FREQ*freq); 
            flag = false; 
            t.reset();
        }
        ThisThread::sleep_for(250ms);
    }
}




