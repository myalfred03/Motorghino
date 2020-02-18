#include <OpenTB6612FNG.h>
#include <Motorghino.h>
#include <TimerOne.h>


OpenTB6612FNG driver;
Motorghino Motor_Left;

boolean Timer_flag = 0;




/* PID Speed Variables*/
int Setpoint = 0;
int l_Prop_Speed = 0;
float KP_Speed = 0.05;
float KD_Speed = 0.00;






void setup() {
  Serial.begin(115200);
  Timer1.initialize(3000);
  Timer1.attachInterrupt(func1);
  Motor_Left.begin(32, 5, 2);


  driver.begin();

}

void loop() {
  // Declare variable, for example "sp" (Remember that "get_speed_ms()" function, return a float variable).



  if (Timer_flag == 1 ) {
    volatile float vl;


    // assign the speed (mm/s) to "sp" variable
    vl = Motor_Left.get_speed_mms();
    volatile int pow = PID_Speed(vl, Setpoint);
    driver.MotorIz(-pow);



    Serial.print(Setpoint);
    Serial.print("\t");
    Serial.print(5000);
    Serial.print("\t");
    Serial.print(0);
    Serial.print("\t");
    Serial.println(vl);




    Timer_flag = 0;
  }

  // finally, print "sp" variable through Serial Terminal
  Serialin();

}


void Serialin() {
  if (Serial.available() > 0) {
    Setpoint = Serial.parseInt();
    if (Setpoint == 0) {
      driver.MotorIz(0);
      delay(30000);
    }
    tone(10, 2000, 120);
    Serial.read();

  }
}



int PID_Speed(int current_Speed, int setpoint_Speed) {

  volatile int error_Speed = int(current_Speed) - setpoint_Speed;
  volatile int deriv_Speed = Prop_Speed - l_Prop_Speed;
  volatile int power_motor = int(Prop_Speed * KP_Speed - KD_Speed * deriv_Speed);

  if (power_motor > 255)
    power_motor = 255;
  else if (power_motor < -255)
    power_motor = -255;
  return power_motor;


  errorOld = error;
  error = setPos - currentPos;
  PWM   = kP * error;
  PWM  += kD * (error - errorOld);


}



void func1(void)
{

  Timer_flag = 1;

}
