/***************************************************
  Arduino library for Motorghino Supports work with Lamborghino 2.2 and newers. Lamborghino sensor detects the
  absolute angular position of the shaft.
  ----> http://lamborghino.com
  Written by Andrés Bercovich: twitter: @andresbercovich
  MIT license, all text above must be included in any redistribution
****************************************************/

#include "Motorghino.h"

uint8_t _cs_motorghino;
uint8_t _diameter_wheel;
uint8_t _reduction_motor;
long _l_Counts;
float l_measure_mm = 0;
long firstcount;
long l_micros;

int revolutions = 0;


SPISettings settings(10000000, MSBFIRST, SPI_MODE3);

Motorghino::Motorghino(){

}


void  Motorghino::begin(uint8_t diameter_wheel, uint8_t reduction_motor, uint8_t cs_motorghino){
    _cs_motorghino = cs_motorghino;
    _diameter_wheel = diameter_wheel;
    _reduction_motor = reduction_motor;
    Serial.begin(115200);

    pinMode(_cs_motorghino, OUTPUT);
    digitalWrite(_cs_motorghino, HIGH);
    SPI.begin();
    SPI.beginTransaction(settings);
    firstcount = get_bits();
}

void Motorghino::end(){
    SPI.end();
}



long Motorghino::get_bits(){
  volatile uint16_t motor_bits;
  digitalWrite(_cs_motorghino, LOW);
  long l_motor_bits = SPI.transfer16(0x0000)>>2 ; //Read 16-bit angle
  digitalWrite(_cs_motorghino, HIGH);
  return l_motor_bits;
}


long Motorghino::get_revolutions() {
  long _counts = get_bits();
  long count_dif = _l_Counts - _counts;

  if (count_dif > 8192) {
    revolutions++;
  }

  if (count_dif < -8192) {
    revolutions--;
  }

  _l_Counts = _counts;
  return revolutions;
}



long Motorghino::get_counts() {
  long _motor_counts = get_bits() + 16384 * get_revolutions();
  return _motor_counts;
}



float Motorghino::get_mm() {
  float _mms = get_counts() / (16384.0);
  volatile float mms = (_mms/_reduction_motor) * (_diameter_wheel * 3.14);
  return mms;
}



float Motorghino::get_speed_mps() {
  volatile long measure_time = micros();
  volatile float measure_distance = get_mm();
  volatile long timediference = (measure_time - l_micros);
  volatile float distancediference = (measure_distance - l_measure_mm);
  volatile float speed_mps = (distancediference / timediference);
  speed_mps = speed_mps * 1000000.0;

  l_micros = measure_time;
  l_measure_mm = measure_distance;
  return speed_mps;
}
