#include <Arduino.h>

#include "devices/Button.hpp"
#include "devices/Display.hpp"
#include "devices/Door.hpp"
#include "devices/Led.hpp"
#include "devices/ServoMotor.hpp"
#include "devices/TempSensor.hpp"
#include "devices/UserDetector.hpp"
#include "devices/WasteDetector.hpp"

#include "tasks/Scheduler.hpp"
#include "tasks/ContainerTask.hpp"
#include "tasks/FillingTask.hpp"
#include "tasks/TemperatureTask.hpp"

#define SCHEDULER_BASE_TIME 100
#define TEMPERATURE_TASK_BASE_TIME 500
#define FILLING_TASK_BASE_TIME 500
#define CONTAINER_TASK_BASE_TIME 500

#define CLOSE_BUTTON_PIN 3
#define OPEN_BUTTON_PIN 2
#define DOOR_PIN 11
#define GREEN_LED_PIN 13
#define RED_LED_PIN 12
#define TEMPERATURE_SENSOR_PIN A1
#define USER_DETECTOR_PIN 8
#define WASTE_DETECTOR_TRIGGER_PIN 5
#define WASTE_DETECTOR_ECHO_PIN 6

Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  scheduler.init(SCHEDULER_BASE_TIME);
  
  //creating flags
  Flag* tempAllarm = new Flag();
  Flag* containerFull = new Flag();

  //creating devices
  Button* openButton = new Button(OPEN_BUTTON_PIN);
  Button* closeButton = new Button(CLOSE_BUTTON_PIN);
  Display* display = new Display();
  Door* door = new Door(DOOR_PIN);
  Led* greenLed = new Led(GREEN_LED_PIN);
  Led* redLed = new Led(RED_LED_PIN);
  TempSensor* tempSensor = new TempSensor(TEMPERATURE_SENSOR_PIN);
  UserDetector* userDetector = new UserDetector(USER_DETECTOR_PIN);
  WasteDetector* wasteDetector = new WasteDetector(WASTE_DETECTOR_TRIGGER_PIN, WASTE_DETECTOR_ECHO_PIN);

  //initializing devices
  openButton->init(OPEN_BUTTON);
  closeButton->init(CLOSE_BUTTON);
  display->init();
  userDetector->init();

  //creating tasks
  TemperatureTask* temperatureTask = new TemperatureTask(TEMPERATURE_TASK_BASE_TIME);
  FillingTask* fillingTask = new FillingTask(FILLING_TASK_BASE_TIME);
  ContainerTask* containerTask = new ContainerTask(CONTAINER_TASK_BASE_TIME);

  //initializing tasks
  temperatureTask->init(tempAllarm, containerFull);
  fillingTask->init(tempAllarm, containerFull);
  containerTask->init(tempAllarm, containerFull);

  temperatureTask->setDevices(tempSensor, greenLed, redLed, display, door);
  fillingTask->setDevices(wasteDetector, greenLed, redLed, display, door);
  containerTask->setDevices(openButton, closeButton, greenLed, redLed, display, door, userDetector);

  //starting tasks
  scheduler.addTask(temperatureTask);
  scheduler.addTask(fillingTask);
  scheduler.addTask(containerTask);
}

void loop() {
  scheduler.schedule();
}
