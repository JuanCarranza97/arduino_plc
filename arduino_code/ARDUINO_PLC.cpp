#include "ARDUINO_PLC.h"

const int available_pwm_outputs[] = {3,5,6,9,10,11};

#define AVAILABLE_PWM_SIZE (sizeof(available_pwm_outputs)/sizeof(int))

analog_output analog_outputs[AVAILABLE_PWM_SIZE];
int available_outputs = AVAILABLE_PWM_SIZE;

void arduino_plc_init(void){
  uart_init();
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  UART_PORT.println("PWM PORTS: "+String(AVAILABLE_PWM_SIZE));

  for(int i = 0; i<AVAILABLE_PWM_SIZE; i++){
    int offset = 10+(DATA_SIZE)*i;
    int pin;
    //UART_PORT.println("analog output: "+String(i)+", offset: "+String(offset));
    analog_outputs[i].init(offset);  
    analog_outputs[i].read_eeprom();
    //If pin is not PWM output override this with defined values
    if(!is_pwm_output(analog_outputs[i].pin)){
      analog_outputs[i].pin=available_pwm_outputs[i];
      analog_outputs[i].write_eeprom();
    }
    //UART_PORT.println("  ->PIN: "+String(analog_outputs[i].pin));
  }
  UART_PORT.println("---------- Arduino-PLC connection ----------");
  UART_PORT.println("     Version: 0.8.1     Developer: BORRA    ");
  UART_PORT.println("--------------------------------------------");
  
}

bool is_pwm_output(int pin){
  bool was_found=false;
  for(int i=0;i<AVAILABLE_PWM_SIZE;i++)
    if(available_pwm_outputs[i] == pin) was_found=true;

  return was_found;
}
