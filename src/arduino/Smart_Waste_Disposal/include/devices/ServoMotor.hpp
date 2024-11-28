#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include <Servo.h>

/*class ServoMotor {
private:
    int pin;
    Servo motor;
    int getCurrent();
    void on();
    void off();
public:
    ServoMotor(int pin);
    void setPosition(int angle);
};*/

class ServoMotor {

public:
  ServoMotor(int pin);

  void on();
  void setPosition(int angle);
  void off();
  Servo motor;  
private:
  int pin;
};

#endif