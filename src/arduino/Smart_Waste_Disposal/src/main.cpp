#include "devices/Button.hpp"
#include "devices/Display.hpp"
#include "devices/Door.hpp"
#include "devices/Led.hpp"
#include "devices/ServoMotor.hpp"
#include "devices/TempSensor.hpp"
#include "devices/UserDetector.hpp"
#include "devices/WasteDetector.hpp"
#include "tasks/Scheduler.hpp"
//#include "tasks/Task.hpp"
#include "tasks/ContainerTaks.hpp"
#include "tasks/FillingTask.hpp"
#include "tasks/TemperatureTask.hpp"
#include <Arduino.h>

Scheduler s;

void setup() {
  Serial.begin(9600);
  //s = new Scheduler();
  s.init(150);
  
  TemperatureTask* TT = new TemperatureTask(50);
  ContainerTaks* CT = new ContainerTaks(100);
  FillingTask* FT = new FillingTask(150);

  s.addTask(TT);
  s.addTask(CT);
  s.addTask(FT);
}

void loop() {
  s.schedule();
}
