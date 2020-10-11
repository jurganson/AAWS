#include <LowPower.h>

// SENSORS
// Sensors on analog pins
int sensor01rd = A1;
int sensor02rd = A2;
int sensor03rd = A3;

// Sensor values
int sensor01val = 0;
int sensor02val = 0;
int sensor03val = 0;

// Sensor power
int sensor01pwr = 2;
int sensor02pwr = 3;
int sensor03pwr = 4;

// Sensor sensitivity
int sensorThreshold = 400;

// PUMPS
// Pump power
int pump01pwr = 5;
int pump02pwr = 6;
int pump03pwr = 7;

// BATTERY VALUES
const long InternalReferenceVoltage = 1100;

// TIMING
int sensorDelay = 1000;
int pumpDuration = 3000;
int pumpDurationDown = 500;

// Hours
int twelve = 5400; // 60 minutes * 60 seconds * 12 hours / 8 seconds

// Timer
int currentTime = 5400;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (currentTime >= twelve) {
    currentTime = 0;
    
    // Check sensors
    sensor01val = checkSensor(sensor01pwr, sensor01rd);
    sensor02val = checkSensor(sensor02pwr, sensor02rd);
    sensor03val = checkSensor(sensor03pwr, sensor03rd);
    
    // Pump 1
    if (sensor01val < sensorThreshold) {
      pumpWater(pump01pwr);
    }
    // Pump 2
    if (sensor02val < sensorThreshold) {
      pumpWater(pump02pwr);
    }
    // Pump 3
    if (sensor01val < sensorThreshold) {
      pumpWater(pump03pwr);
    }
    
  } else {
    currentTime = currentTime + 8;
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

int checkSensor(int sensorPower, int sensorRead) {
  digitalWrite(sensorPower, HIGH);
  delay(sensorDelay);
  int result = analogRead(sensorRead);
  digitalWrite(sensorPower, LOW);
  return result;
}

void pumpWater (int pumpPower) {
  digitalWrite(pumpPower, HIGH);
  delay(pumpDuration);
  digitalWrite(pumpPower, LOW);
  delay(pumpDurationDown);
}
