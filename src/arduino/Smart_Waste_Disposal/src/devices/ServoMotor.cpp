#include "devices/ServoMotor.hpp"
#include <Arduino.h>
#include <Servo.h>

#define MOVING_TIME 70.0
#define DEFAULT_POSITION 180

ServoMotor::ServoMotor(int pin) {
    this->pin = pin;
    this->on();
    delay(MOVING_TIME);
    motor.write(DEFAULT_POSITION);
    delay(MOVING_TIME);
    this->off();
}

void ServoMotor::on(){
  motor.attach(this->pin);
}

void ServoMotor::setPosition(int angle){
  this->on();
  delay(MOVING_TIME);
  motor.write(angle);
  delay(MOVING_TIME);
  this->off();
}

void ServoMotor::off(){
  motor.detach();    
}
