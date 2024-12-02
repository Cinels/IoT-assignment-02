#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include <Servo.h>

class ServoMotor {
private:
  int pin;
  Servo motor;
public:
  ServoMotor(int pin);
  void on();
  void setPosition(int angle);
  void off();
};

#endif
