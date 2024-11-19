/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "co2sensor.h"


using namespace std::chrono;
#define TIMMER_RATE     500ms

I2C i2c(P1_I2C_SDA, P1_I2C_SCL);

uint8_t addr7bit = 0x62;
// Create sensor object
Co2Sensor sensor = Co2Sensor(addr7bit, &i2c);
DigitalOut led(LED1);

Thread thread_measure(osPriorityNormal, 1024, nullptr, nullptr); // 1024 = stack_size => mémoire allouée pour le thread
Thread thread_blink(osPriorityNormal, 1024, nullptr, nullptr); // 1024 = stack_size => mémoire allouée pour le thread)

void measure_routine()
{
    while(1)
    {
        sensor.make_measure();
        sensor.print_measure();
    }
}

void blink_routine()
{
    while(1)
    {
        led =!led;
        ThisThread::sleep_for(1000ms);
    }
}

int main()
{
   thread_measure.start(measure_routine);
   thread_blink.start(blink_routine);
   thread_measure.join();
   thread_blink.join(); 
}