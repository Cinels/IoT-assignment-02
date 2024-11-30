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
#include <Arduino.h>

Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  scheduler.init(150);
  
  TemperatureTask* TT = new TemperatureTask(50);
  ContainerTask* CT = new ContainerTask(100);
  FillingTask* FT = new FillingTask(150);

  scheduler.addTask(TT);
  scheduler.addTask(CT);
  scheduler.addTask(FT);
}

void loop() {
  scheduler.schedule();
}
