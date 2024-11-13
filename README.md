
## Application functionality

The `main()` function is the single thread in the application. It toggles the state of a digital output connected to an LED on the board.

## Activate venv
```bash
$ source ~/env01/bin/activate  
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
$ mbed minicom -D /dev/ttyUSBx -b <BAUDRATE>
$ mbed sterm --port /dev/ttyUSBx --baud <BAUDRATE>
```


## Related Links

* [6Tron](https://6tron.io/).
* [Catie-aq](https://github.com/catie-aq).