#include "ANALOG_OUTPUT.h"

analog_output::analog_output(){

}

void analog_output::init(int _addr_offset){
  addr_offset = _addr_offset;
}

void analog_output::read_eeprom(void){
  pin = EEPROM.read(addr_offset+0);
  min_value = EEPROM.read(addr_offset+1);
  max_value = EEPROM.read(addr_offset+2);
}

void analog_output::write_eeprom(void){
  EEPROM.write(addr_offset+0,pin);
  EEPROM.write(addr_offset+1,min_value);
  EEPROM.write(addr_offset+2,max_value);
}

void analog_output::set_pwm_pin(int _pin){
  pin = _pin;
  pinMode(pin,OUTPUT);
  analogWrite(pin,0);
}

void analog_output::write_output(int _value){
  value = _value;
  analogWrite(pin,map(_value,min_value,max_value,0,255));
}

void analog_output::set_range(int _min,int _max){
  min_value=_min;
  max_value=_max;
}

void analog_output::get_info(void){
  UART_PORT.println("  --> Pin: "+String(pin));
  UART_PORT.println("  --> Range: "+String(min_value)+" - "+String(max_value));

}
