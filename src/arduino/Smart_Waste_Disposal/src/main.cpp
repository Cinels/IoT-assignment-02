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
#include "tasks/CommunicationTask.hpp"

#define SCHEDULER_BASE_TIME 150
#define TEMPERATURE_TASK_BASE_TIME 300
#define FILLING_TASK_BASE_TIME 300
#define CONTAINER_TASK_BASE_TIME 150
#define COMMUNICATION_TASK_BASE_TIME 450

#define CLOSE_BUTTON_PIN 9
#define OPEN_BUTTON_PIN 8
#define DOOR_PIN 11
#define GREEN_LED_PIN 13
#define RED_LED_PIN 12
#define TEMPERATURE_SENSOR_PIN A0
#define USER_DETECTOR_PIN 2
#define WASTE_DETECTOR_TRIGGER_PIN 5
#define WASTE_DETECTOR_ECHO_PIN 6

Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  scheduler.init(SCHEDULER_BASE_TIME);
  
  //creating flags
  Flag* flags = new Flag();

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
  display->init();
  display->setText(DISPLAY_POSITION, "INITIALIZING");
  userDetector->init();
  display->clear();

  //creating tasks
  TemperatureTask* temperatureTask = new TemperatureTask(TEMPERATURE_TASK_BASE_TIME);
  FillingTask* fillingTask = new FillingTask(FILLING_TASK_BASE_TIME);
  ContainerTask* containerTask = new ContainerTask(CONTAINER_TASK_BASE_TIME);
  CommunicationTask* communicationTask = new CommunicationTask(COMMUNICATION_TASK_BASE_TIME);

  //initializing tasks
  temperatureTask->setDevices(tempSensor, greenLed, redLed, display, door);
  fillingTask->setDevices(wasteDetector, greenLed, redLed, display, door);
  containerTask->setDevices(openButton, closeButton, greenLed, redLed, display, door, userDetector);
  communicationTask->setDevices(wasteDetector, tempSensor);

  temperatureTask->setFlag(flags);
  fillingTask->setFlag(flags);
  containerTask->setFlag(flags);
  communicationTask->setFlag(flags);

  //starting tasks
  scheduler.addTask(temperatureTask);
  scheduler.addTask(fillingTask);
  scheduler.addTask(containerTask);
  scheduler.addTask(communicationTask);
}

void loop() {
  scheduler.schedule();
}
