#include "devices/ServoMotor.hpp"
#include <Arduino.h>
#include <Servo.h>

ServoMotor::ServoMotor(int pin) {
    this->pin = pin;
    //this->motor = new Servo();
}

void ServoMotor::on(){
  // Serial.println("on");
  motor.attach(this->pin);
}

void ServoMotor::setPosition(int angle){
  this->on();
  // Serial.print("shold be in position ");
  // Serial.println(angle);
  motor.write(angle);
  //devi lasciargli il tempo di muoversi -> voglio mettere una lista roba in coda
  this->off();
}

void ServoMotor::off(){
  // Serial.println("off");
  motor.detach();    
}