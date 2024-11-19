#include "mbed.h"



class Co2Sensor
{
    private :
    char measure[9];
    uint8_t addr8bit;
    I2C *i2c; 
    float result[3]; 
    void convert_measure();
    void make_single_measure();
    

    public:
    Co2Sensor(uint8_t address, I2C* i2c);
    float* get_measure();
    void print_measure();
    void make_measure();

};