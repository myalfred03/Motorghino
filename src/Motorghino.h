/***************************************************
Arduino library for Motorghino Supports work with Lamborghino 2.2 and newers. Lamborghino sensor detects the
absolute angular position of the shaft.
----> http://lamborghino.com
Written by Andrés Bercovich: twitter: @andresbercovich
MIT license, all text above must be included in any redistribution
 ****************************************************/

#ifndef Motorghino_H
#define Motorghino_H

#if (ARDUINO >= 100)
     #include "Arduino.h"
#else
     #include "WProgram.h"
#endif
#include <SPI.h>


#define MOTORGHINO_SPI_MODE_3       SPI_MODE3

class Motorghino {
public:
    Motorghino();
    void  begin(uint8_t diameter_wheel, uint8_t reduction_motor, uint8_t cs_motorghino);
    void end();



    long get_bits();
    double get_angule();
    long get_revolutions();
    long get_counts();
    float get_mm();
    float get_speed_mps();

private:
};

#endif //Motorghino_H
