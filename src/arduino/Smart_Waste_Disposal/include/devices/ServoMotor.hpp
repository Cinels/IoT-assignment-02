#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor {
private:
    int pin;
    int angle;
    int getCurrent();
public:
    ServoMotor(int pin);
    void setAngle(int angle);
};

#endif