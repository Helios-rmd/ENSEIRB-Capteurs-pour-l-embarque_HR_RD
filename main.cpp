/**
 * Copyright (c) 2017, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>

#include "mbed.h"




using namespace std::chrono;

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
InterruptIn button(BUTTON1);
DigitalOut led(LED1);
Timer t;
bool flag; 

void start_counting()
{
    t.start();
    led = true;
}

void end_counting()
{
    t.stop();
    led = false;
    flag = true;
}

int main()
{
    button.rise(&start_counting);  // attach the address of the flip function to the rising edge
    button.fall(&end_counting);

    while (1) {          // wait around, interrupts will interrupt this!
        if(flag){
            printf("The button was pressed during %llu ms\n", duration_cast<milliseconds>(t.elapsed_time()).count());
            flag = false; 
            t.reset();
        }
        ThisThread::sleep_for(250ms);
    }
}




