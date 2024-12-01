#include "tasks/ContainerTask.hpp"
#include <Arduino.h>
#include <avr/sleep.h>

#define SLEEP_TIME 15000
#define OPEN_TIME 15000
#define CLOSE_TIME 2000

ContainerTask::ContainerTask(int period) {
    Task::init(period);
    this->state = AWAKE;
    this->ts = millis();
}

void ContainerTask::init(Flag* tempflag, Flag* fillflag) {
    this->tempAllarm = tempAllarm;
    this->containerFull = containerFull;
}

void ContainerTask::setDevices(Button* openButton, Button* closeButton, Led* greenLed, Led* redLed, Display* display, Door* door, UserDetector* userDetector) {
    this->openButton = openButton;
    this->closeButton = closeButton;
    this->greenLed = greenLed;
    this->redLed = redLed;
    this->display = display;
    this->door = door;
    this->userDetector = userDetector;
}

void ContainerTask::tick() {
    Serial.println("CONTAINER TASK");
    switch (this->state) {
    case AWAKE:
        if(millis() - ts >= SLEEP_TIME) {
            this->state = SLEEP;
            // sleepScreen();
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();  

            sleep_disable();
            this->state = AWAKE;
            // old screen
            this->ts = millis();
        }
        //guarda la coda degli eventi (ci stanno dentro l'user sensor, i bottoni e il movimento del motore)
        // dopo che hai aperto ↓
        // this->display->setText(DISPLAY_POSITION, "PRESS CLOSE WHEN DONE");
        // this->ts = millis();
        break;
    case OPEN:
        //guarda la coda
        if(millis() - ts >= OPEN_TIME) {
            this->state = CLOSE;
            this->door->close();
            this->display->setText(DISPLAY_POSITION, "WASTE RECEIVED");
            this->ts = millis();
        }
        break;
    case CLOSE:
        if(millis() - ts >= CLOSE_TIME) {
            this->state = AWAKE;
            if(!this->tempAllarm->getValue() && !this->containerFull->getValue()) {
                this->display->setText(DISPLAY_POSITION, "PRESS OPEN TO");
                this->display->setText(DISPLAY_POSITION_2, "ENTER WASTE");
            }
            this->ts = millis();
        }
        break;
    default: break;
    }
}
