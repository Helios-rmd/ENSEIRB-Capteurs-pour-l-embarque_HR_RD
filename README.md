
## Application functionality

The `main()` function is the single thread in the application. It toggles the state of a digital output connected to an LED on the board.

## Activate venv
```bash
$ source ~/my_env01/bin/activate  
```
## Configure

Run the following commands to define target and toolchain:
```bash
(env_name)$ mbed target ZEST_CORE_FMLR-72
(env_name)$ mbed toolchain GCC_ARM
```

## Building and running

1. Connect a USB cable between the USB port on the board and the host computer.
2. Run the following command to build the example project and program the microcontroller flash memory:

```bash
$ mbed compile
```
Your PC may take a few minutes to compile your code.

Then flash uc

```bash
$ sixtron_flash
```

3. Display target communication

```bash 
$ ls /dev/ttyUSB*
$ minicom -D /dev/ttyUSB0 --baud 9600
$ mbed sterm --port /dev/ttyUSB0 --baud 9600
```

## Sensor communication features (CO2 sensor SCD41-D-R2)
1. Features
    
    I2C communication
    
    Adress : 0x62
    
    Data type and length :  Data sent to and received from the sensor consists of a sequence of 16-bit commands and/or 16-bit words (each to be interpreted
                            as unsigned integer with the most significant byte transmitted first). Each data word is immediately succeeded by an 8-bit CRC.
                            In write direction it is mandatory to transmit the checksum. In read direction it is up to the master to decide if it wants to process the checksum
    
See https://sensirion.com/media/documents/48C4B7FB/66E05452/CD_DS_SCD4x_Datasheet_D1.pdf p7 for more details

2. Get a single measure
    
    Use measure_single_shot command : 0x219d 

    Wait for max. command duration time (5000ms)

    Then use read_measurement command : 0xec05

3. Convert signal

    𝐶𝑂2 [ppm] = 𝑤𝑜𝑟𝑑[0]

    𝑇 = −45 + 175 ∗ 𝑤𝑜𝑟𝑑[1]/(2^16-1)    

    𝑅𝐻 = 100 ∗ 𝑤𝑜𝑟𝑑[2]/(2^16-1)

## Related Links

* [6Tron](https://6tron.io/).
* [Catie-aq](https://github.com/catie-aq).