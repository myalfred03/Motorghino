# Motorghino library
Arduino library for Motorghino (Ultra High precision Motor Feed)

## About
Motorghino detects the absolute angular position of the shaft

For more information of Motorghino, and Open Lamborghino proyects

http://lamborghino.com


## License
Written by Andres Bercovich, CEO Lamborghino and Safter Mechatronics.

## Connections
### Power supply

| Motorghino  | Arduino | Motor Terminal |
| ----------------------- | ---- | ---- |
| M1          |  | Terminal  |
| 3.3V        | 3.3V                                  |
| GND         | GND                                   |
| CLK         | CLK (D13)                             |
| MISO        | MISO (D12)                            |
| CS          | CS (Any digital pin D2, for example)  |
| M2          |  | Terminal  |

| Warning |
| :-------: |
| Unlike most Arduino & Genuino boards, MOTORGHINO RUNS AT 3.3V**. Even if the I/O can tolerate 5V, check that the voltage applied to VDD is at 3.3V. **Applying a voltages higher than 3.3V to the VDD pin could damage the sensor**.|

### Serial communication
MOTORGHINO have a SPI communication interface.


#### Arduino SPI pin mapping
| Arduino / Genuino Board | MOSI | MISO | SCK | CS  | Voltage Level |
| ----------------------- | ---- | ---- | ---- | :---: | ------------- |
| Zero                    | ICSP-4 | ICSP-1 | ICSP-3 | defined by the user, any digital pin (default: pin 0)  | +3.3V |
| MKRZero                 | 8 | 10 | 9 | defined by the user, any digital pin (default: pin 0)  | +3.3V |
| MKR1000                 | 8 | 10 | 9 | defined by the user, any digital pin (default: pin 0)  | +3.3V |
| 101                     | 11 or ICSP-4 | 12 or ICSP-1 | 13 or ICSP-3 | defined by the user, any digital pin (default: pin 0)  | +3.3V |
| Due                     | ICSP-4 | ICSP-1 | ICSP-3 | defined by the user, any digital pin (default: pin 0)  | +3.3V |
| Uno or Duemilanove      | 11 or ICSP-4 | 12 or ICSP-1 | 13 or ICSP-3 | defined by the user, any digital pin. **Default pin must be changed because pin 0 is also used by the Serial port**. (use pin 7 for example)  | +5V |
| Mega1280 or Mega2560    | 51 or ICSP-4 | 50 or ICSP-1 | 52 or ICSP-3 | defined by the user, any digital pin (default: pin 0)  | +5V |
| Leonardo                | ICSP-4 | ICSP-1 | ICSP-3 | defined by the user, any digital pin (default: pin 0)  | +5V |

Check [Arduino SPI library reference page](https://www.arduino.cc/en/Reference/SPI) for more information on the SPI signal connections.

## Setup
Install the library directly from within the Arduino IDE by using the Library Manager (Sketch => Include Library => Manage Libraries...).

It is also possible to import the library Zip file (check release tab) from the Arduino IDE (Sketch => Include Library => Add .ZIP Library...).

The library can also be manually installed by copying the Motorghino library folder in your arduinosketchfolder/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE to see the library.

# Using the library 

## Step 1, import the library:

Include the lamborghino library in the header of the code

```C++
#include <Motorghino.h>
```

## Step 2, Create the motorghino object:

Create the motorghino object with the name whatever you want, for example Motor_Left 

```C++
Motorghino Motor_Left; 
```

## Step 3, Begin the motor:

Create the motorghino object with the name whatever you want, for example Motor_Left 

```C++
Motorghino Motor_Left; 
```
