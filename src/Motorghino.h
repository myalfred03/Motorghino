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


    float get_rps();
    float get_rpm();
    uint16_t get_bits();
    long get_bitSpeed_fast_case();
    long get_bitSpeed_slow_case();
    float get_counts_speed();
    float get_speed_mms();
    double get_angule();
    long get_revolutions();
    long get_counts();
    float get_mm();


private:

  uint8_t _cs_motorghino;
  uint8_t _diameter_wheel;
  uint8_t _reduction_motor;



  long _l_Counts;
  long l_counts;
  float l_rps;
  float l_measure_mm = 0;
  long firstcount;
  long l_micros;
  long bitDiff = 0;

  float lspeed = 0.0;
  long lnow = 0;
  float l_count_speed = 0.0;


  long lbits1 = 0;
  long lbits2 = 0;
  long l_bs_fast_timer = 0;

  int revolutions = 0;
};

#endif //Motorghino_H
