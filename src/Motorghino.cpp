/***************************************************
  Arduino library for Motorghino Supports work with Lamborghino 2.2 and newers. Lamborghino sensor detects the
  absolute angular position of the shaft.
  ----> http://lamborghino.com
  Written by Andrés Bercovich: twitter: @andresbercovich
  MIT license, all text above must be included in any redistribution
****************************************************/

#include "Motorghino.h"




SPISettings settings(10000000, MSBFIRST, SPI_MODE3);

Motorghino::Motorghino(){

}


void  Motorghino::begin(uint8_t diameter_wheel, uint8_t reduction_motor, uint8_t cs_motorghino){
    _cs_motorghino = cs_motorghino;
    _diameter_wheel = diameter_wheel;
    _reduction_motor = reduction_motor;
    pinMode(_cs_motorghino, OUTPUT);
    digitalWrite(_cs_motorghino, HIGH);
    SPI.begin();
    SPI.beginTransaction(settings);
    firstcount = get_bits();
}

void Motorghino::end(){
    SPI.end();
}



uint16_t Motorghino::get_bits(){
  volatile uint16_t motor_bits;
  digitalWrite(_cs_motorghino, LOW);
  uint16_t l_motor_bits = SPI.transfer16(0x0000)>>2 ; //Read 16-bit angle
  digitalWrite(_cs_motorghino, HIGH);
  return l_motor_bits;
}


long Motorghino::get_bitSpeed_fast_case() {
  volatile long bits1 = int(get_bits());
  if (bits1 - lbits1 < 0) {
    bitDiff = int(bits1 + 16384 - lbits1);
  } else {
    bitDiff = int(bits1 - lbits1);
  }
  lbits1 = bits1;
  return bitDiff;
}



long Motorghino::get_bitSpeed_slow_case() {
  volatile long bits2 = get_counts();
  if (abs(bits2 - lbits2) < 1500) {
    bitDiff = bits2 - lbits2;
  }
  lbits2 = bits2;
  return bitDiff;
}



float Motorghino::get_counts_speed() {
  volatile long now = micros();
  volatile long timediference = now - lnow;
  volatile float count_speed;
  if (l_count_speed <= 1000.0) {
    count_speed = get_bitSpeed_slow_case();
  } else {
    count_speed = get_bitSpeed_fast_case();
  }
  l_count_speed = count_speed;
  lnow = now;
  return l_count_speed;
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


float Motorghino::get_rps() {
  volatile float rps_counts = get_counts_speed()*(1000.0/(_reduction_motor*16384.0));
  return rps_counts;
}


float Motorghino::get_rpm() {
  volatile float rpm_counts = 60*get_counts_speed()*(1000.0/(_reduction_motor*16384.0));
  return rpm_counts;
}

float Motorghino::get_speed_mms() {
  volatile float speed_mm = get_rps()*3.1415*_diameter_wheel;
  return speed_mm;
}
