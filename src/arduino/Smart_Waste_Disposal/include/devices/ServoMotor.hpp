#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include <Servo.h>

/// @brief Class to manage servo motors.
class ServoMotor {
private:
  int pin;
  Servo motor;
public:
  /// @brief Servo motor constructor, it creates a servo motor connected to the given pin.
  /// @param pin the pin where the servo motor is connected.
  ServoMotor(int pin);
  
  /// @brief Attaches the pin to the servo motor.
  void on();
  
  /// @brief Sets the servo motor to a given angle.
  /// @param angle the angle to set the servo motor.
  void setPosition(int angle);
  
  /// @brief Detaches the servo motor from the pin in order to reduce power consumption.
  void off();
};

#endif
