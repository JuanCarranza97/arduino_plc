#ifndef ANALOG_OUTPUT_H
#define ANALOG_OUTPUT_H

  #include <Arduino.h>

  #include "ARDUINO_PLC.h"

  #define DATA_SIZE        3

  class analog_output{
    public:
      analog_output();
      analog_output(int _pin,int _addr_offset);
      void init(int _addr_offset);
      void read_eeprom(void);
      void write_eeprom(void);
      void set_pwm_pin(int _pin);
      void write_output(int _value);
      void set_range(int _min,int _max);
      void get_info(void);
      int pin,value,min_value,max_value;
    private:      
      int addr_offset;
  };

#endif
