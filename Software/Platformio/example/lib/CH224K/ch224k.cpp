/**
 * @file ch224k.cpp
 * @author T76
 * @brief CH224K USB-C PD Interface library
 * 
 * @copyright Copyright (c) 2023 T76.org
 * @license MIT
 */

#include "ch224k.hpp"


void CH224KController::begin(uint8_t CFG1, uint8_t CFG2, uint8_t CFG3, uint8_t PG) {
  _CFG1 = CFG1;
  _CFG2 = CFG2;
  _CFG3 = CFG3;
  _PG   = PG;

  pinMode(CFG1, OUTPUT);
  pinMode(CFG2, OUTPUT);
  pinMode(CFG3, OUTPUT);

  if (PG) {
    pinMode(PG, INPUT_PULLUP);
  }

  // Default to 5V

  setVoltageSetPoint(V5);
}

void CH224KController::setVoltageSetPoint(CH224KVoltage newVoltageSetPoint) {
  switch (newVoltageSetPoint) {
    case V5:
      digitalWrite(_CFG1, HIGH);
      digitalWrite(_CFG2, LOW);
      digitalWrite(_CFG3, LOW);
      break;

    case V9:
      digitalWrite(_CFG1, LOW);
      digitalWrite(_CFG2, LOW);
      digitalWrite(_CFG3, LOW);
      break;

    case V12:
      digitalWrite(_CFG1, LOW);
      digitalWrite(_CFG2, LOW);
      digitalWrite(_CFG3, HIGH);
      break;

    case V15:
      digitalWrite(_CFG1, LOW);
      digitalWrite(_CFG2, HIGH);
      digitalWrite(_CFG3, HIGH);
      break;

    case V20:
      digitalWrite(_CFG1, LOW);
      digitalWrite(_CFG2, HIGH);
      digitalWrite(_CFG3, LOW);
      break;

    default:
      // Do nothing
      return;
  }

  _voltageSetPoint = newVoltageSetPoint;
}

CH224KVoltage CH224KController::getVoltageSetPoint() {
  return _voltageSetPoint;
}

bool CH224KController::powerGood() {
  if (_PG) {
    return digitalRead(_PG) == LOW;
  } else {
    return false;
  }
}

