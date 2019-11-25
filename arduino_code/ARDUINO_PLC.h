#ifndef ARROB_CONFIG_H
#define ARROB_CONFIG_H

  #include <Arduino.h>

  #include "TERMINAL.h"
  #include "UART.h"
  #include <EEPROM.h>
  #include "ANALOG_OUTPUT.h"
  
  void arduino_plc_init(void);
  bool is_pwm_output(int pin);
#endif
