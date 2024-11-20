#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor {

public:
    virtual void setAngle(int degrees) = 0;
};

#endif