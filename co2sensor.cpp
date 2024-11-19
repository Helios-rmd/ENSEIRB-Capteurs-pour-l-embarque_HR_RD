#include "co2sensor.h"


// Constructor definition 
Co2Sensor::Co2Sensor(uint8_t address, I2C *i2c)
    {
        this->addr8bit = address << 1;
        this->i2c = i2c;
    }

    
    void Co2Sensor::make_single_measure()
{
    char cmd[2];
    cmd[0] = 0x21;
    cmd[1] = 0x9D;
    int error;
    error = i2c->write(addr8bit, cmd, 2);


    if(error)
       printf("NACK sur single_shot_measure\n");

    ThisThread::sleep_for(5000ms);
    cmd[0] = 0xec;
    cmd[1] = 0x05;
    error = i2c->write(addr8bit, cmd, 2);

    if(error)
        printf("NACK sur read_measure\n");

    ThisThread::sleep_for(5ms);
    error = i2c->read(addr8bit, measure, 9);
    if(error)
        printf("NACK sur lecture\n");
}

// Convert measure to usable values
void Co2Sensor::convert_measure()
{

    result[0] = (measure[0]<<8)|measure[1];
    result[1] = (-45.0)+175.0*(float)(((measure[3]<<8))|(measure[4]))/65535.0;
    result[2] = (100.0*(float)((measure[6]<<8)|measure[7]))/65535.0; 
}

void Co2Sensor::make_measure()
{
    make_single_measure();
    convert_measure();
}

float* Co2Sensor::get_measure()
{
    return result;
}    
    
void Co2Sensor::print_measure()
{
    printf("##### Mesure : #####\n");
    printf("C02[ppm] = %d\n", (int)roundf(result[0]));
    printf("Temp = %d C\n", (int)roundf(result[1]));
    printf("Humidity = %d\n", (int)roundf(result[2]));
    printf("####################\n");
}    

        