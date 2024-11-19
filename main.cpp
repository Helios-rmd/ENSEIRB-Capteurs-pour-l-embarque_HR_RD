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