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
#define TIMMER_RATE     500ms

I2C i2c(P1_I2C_SDA, P1_I2C_SCL);


// Make measure using single shot measurement
void make_single_measure(uint8_t adress, char* measure)
{
    uint8_t addr8bit_write = adress<<1;
    uint8_t addr8bit_read = addr8bit_write + 1;
    char cmd[2];
    cmd[0] = 0x21;
    cmd[1] = 0x9D;
    int error;
    error = i2c.write(addr8bit_write, cmd, 2);
    if(error)
       printf("NACK sur single_shot_measure\n");
        
    ThisThread::sleep_for(5000ms);

    cmd[0] = 0xec;
    cmd[1] = 0x05;
    error = i2c.write(addr8bit_write, cmd, 2);
    if(error)
        printf("NACK sur read_measure\n");

    ThisThread::sleep_for(5ms);
    error = i2c.read(addr8bit_read, measure, 6);
    if(error)
        printf("NACK sur lecture\n");
}

// Convert measure to usable values
void convert(char* measure, float* result)
{
    result[0] = (measure[0]<<8)|measure[1];
    result[1] = (-45.0)+175.0*(float)(((measure[3]<<8))|(measure[4]))/65535.0;
    result[2] = 100.0*(float)((measure[6]<<8)|measure[7])/65535.0;
}

int main()
{
    uint8_t addr7bit = 0x62;
    char measure[9];
    float result[3];


    while(1){
        
        make_single_measure(addr7bit, measure);
        char cmd[2];
        convert(measure, result);

        printf("C02[ppm] = %d\n", (int)roundf(result[0]));
        printf("Temp = %d C\n", (int)roundf(result[1]));
        printf("Humidity = %d\n", (int)roundf(result[2]));
        printf("\n");
    }
}




