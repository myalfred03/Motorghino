# Motorghino library
Arduino library for Motorghino (Ultra High precision Motor Feed)

## About
Motorghino detects the absolute angular position of the shaft

For more information of Motorghino, and Open Lamborghino proyects

http://lamborghino.com

https://github.com/AndresBercovich/Motorghino/blob/master/Motorghino%20Direct%201.png

## License
Written by Andres Bercovich, CEO Lamborghino.

![Alt text](relative/path/to/img.jpg?raw=true "Motorghino Wired 1")

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

### SPI communication
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

## Step 3, Begin and set the motor parameters:

Begin the motorghino object setting the 3 parameters:

**(int) Diameter of the Wheel**: That value is for calculate speed of the wheel.

**(int) Gear Reduction**: Some N20 micrometal gear motors have reductions. Motorghino work detecting the angle position of the extended motor shaft, then, to get the correct rps, rpm or speed of the wheel, you must set the gear reduction.

**(int) Chip Select**: Set the chip select pin (SC), of the Motorghino. Motorghino work with SPI sensor, then you must specify which pin you are use.  (If you use Open Lamborghino, the default Chip select pins are D2 and D3 for Left and Right motor respectively.

```C++
 Motor_Left.begin(uint8_t diameter_wheel, uint8_t reduction_motor, uint8_t cs_motorghino);
```
Example:

```C++
 Motor_Left.begin(32, 5, 2); //if you have a wheel of 32mm of diameter, a 5:1 gearmotor reduction, and the chip select pin connected in D2.
```
## Step 4, Use the get functions:

Finally, to get the values of the sensor, just use the function to get it.

Motorghino work with a sensor of 14 bits/revolution, (16.384 counts/revolution of the extended motor shaft).

**(uint16_t) get_bits()**: get the angle position of the wheel in bits (between 0 and 16.384);

**(long) get_counts()**: get the accumulated wheel path in counts.

**(float) get_rps()**: get the current angular speed of the wheel, in revolution/second;

**(float) get_rpm()**: get the current angular speed of the wheel, in revolution/minute;

**(long) get_mm()**: get the accumulated wheel path in mm.

**(float) get_speed_mms()**: get the current speed of the wheel, in mm/s;

### Example:


```C++
  float sp;

  // assign the path (mm) to "sp" variable
  sp = Motor_Left.get_mm();

  // finally, print "sp" variable through Serial Terminal
  Serial.println(sp);
  ```

# Complete code example:

```C++


#include <Motorghino.h>

//Declare the motorghino variable, like a "Motor_Left"
Motorghino Motor_Left;

void setup() {
 //Begin function of the element have 3 arguments: .begin(Diametert of the wheel, Reduction Ratio, CS pin of SPI)
 // Keep in mind that OpenLamborghino 2.2 have the CS pin of the left motor in D2, and right motor in D3 in Arduino), but
 //if you want a use Motorghino without Open Lamborghino, you can select any digital pin (except SPI pins)

  Motor_Left.begin(32, 5, 2);

  //init the serial port comunication
  Serial.begin(115200);

}

void loop() {
// Declare variable, for example "mm" (Remember that "get_mm" function, return a float variable).
float mm;

// assign the speed (mm) to "sp" variable
mm = Motor_Left.get_mm();

// finally, print "sp" variable through Serial Terminal
Serial.println(mm);

}
  ```
