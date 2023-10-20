/**
 * @file ch224k.hpp
 * @author T76
 * @brief CH224K USB-C PD Interface library
 * 
 * @copyright Copyright (c) 2023 T76.org
 * @license MIT
 */

#pragma once

#include <Arduino.h>

typedef enum {
  V5,
  V9,
  V12,
  V15,
  V20
} CH224KVoltage;

/**
 * @brief 
 * 
 */
class CH224KController {

public:

  /**
   * @brief Initializes the library
   * 
   * @param CFG1 The pin connected to the CFG1 line
   * @param CFG2 The pin connected to the CFG2 line
   * @param CFG3 The pin connected to the CFG3 line
   * @param PG The pin connected to the PG line (or 0 if PG is not connected)
   */
  void begin(
    uint8_t CFG1 = 36,
    uint8_t CFG2 = 35,
    uint8_t CFG3 = 45,
    uint8_t PG   = 37
  );

  /**
   * @brief Request a new voltage from the power supply
   * 
   * @param newVoltage The new voltage requested.
   * 
   * @note Requesting a voltage doesn't automatically mean
   *       that the power supply is capable (or willing) to provide
   *       it. You should not assume that the voltage has changed
   *       until `powerGood()` returns true.
   */
  void setVoltageSetPoint(CH224KVoltage newVoltage);


  /**
   * @brief Get the current voltage set point
   * 
   * @return CH224KVoltage the current voltage setpoint configuration
   *
   * @note This isn't necessarily the voltage provided by the power
   *       supply -- to find out whether the the voltage provide is 
   *       correct, use `powerGood()`.
   */
  CH224KVoltage getVoltageSetPoint();

  /**
   * @brief Returns the state of the Power Good pin
   * 
   * @return true if the CH224K is in a power good state
   * @return false otherwise
   */
  bool powerGood();

protected:

  CH224KVoltage _voltageSetPoint;

  uint8_t _CFG1, _CFG2, _CFG3, _PG;
};
