#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor {

    int pin;
    int angle;

public:
    ServoMotor(int pin);
    void setAngle(int angle);

private:
    int getCurrent();

};

#endif