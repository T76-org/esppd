#include <Arduino.h>
#include <ch224k.hpp>

CH224KController CH224K;

void setup() {
  // Initialize the CH224K chip. This requests 5V by default.
  CH224K.begin();

  Serial.begin(115200);
}

CH224KVoltage voltages[] = {
  V5,
  V9,
  V12,
  V15,
  V20
};

String voltageNames[] = {
  "5V",
  "9V",
  "12V",
  "15V",
  "20V"
};

void loop() {
  // Cycle through all the voltages, waiting 3 seconds
  // between each voltage and the next. For each step,
  // write out the current request voltage, and wait until
  // the power good signal is high.

  for (int i = 0; i < 5; i++) {
    CH224K.setVoltageSetPoint(voltages[i]);
    Serial.print("Requested ");
    Serial.print(voltageNames[i]);
    Serial.print("...");

    delay(300);
    Serial.println(CH224K.powerGood() ? "power good!" : "power bad!");

    delay(3000);
  }
}