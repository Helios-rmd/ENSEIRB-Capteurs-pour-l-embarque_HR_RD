/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "co2sensor.h"


using namespace std::chrono;
#define TIMMER_RATE     500ms

I2C i2c(P1_I2C_SDA, P1_I2C_SCL);


int main()
{
    uint8_t addr7bit = 0x62;
    // Create sensor object
    Co2Sensor sensor = Co2Sensor(addr7bit, &i2c);
    
    float *result; 
    while(1)
    {
        sensor.make_measure();
        sensor.print_measure();
        result = sensor.get_measure(); 
    }
}