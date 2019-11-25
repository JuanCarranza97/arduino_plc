#include "TERMINAL.h"

extern analog_output analog_outputs[];
extern int available_outputs;

terminal_actions actions[]={
  {terminalAction_a,'a',1},
  {terminalAction_p,'p',2},
  {terminalAction_w,'w',1},
  {terminalAction_r,'r',1},
  {terminalAction_q,'q',3},
  {terminalAction_g,'g',1},
  {terminalAction_v,'v',1},
  {terminalAction_h,'h',0},
};


#define TERMINAL_ACTIONS_SIZE (sizeof(actions)/sizeof(terminal_actions))

void terminal_lab(void){
  if(UART_PORT.available()){
      char caracter;
      int Numbers[20];
      int bufferSize=0;

        if(uart_get(&caracter,&bufferSize,Numbers)){
           bool found = false;
              for(int i = 0;i<TERMINAL_ACTIONS_SIZE;i++){
                if(caracter == actions[i].caracter){
                  found = true;
                  if(actions[i].tam == bufferSize){
                    UART_PORT.println("e"+String(actions[i].Callback(Numbers)));
                  }
                  else{
                    UART_PORT.println("e"+String(2));                
                  }
                }
              }
        }
        else{
          UART_PORT.println("e"+String(3));
        }
  }  
}


int terminalAction_a(int var[]){
  if(var[0] == 0 ||  var[0] == 1){
     if(var[0] == 0)        digitalWrite(13,LOW);
     else if(var[0] == 1)   digitalWrite(13,HIGH);
  }
  else  return 3;
  return 0;  
}


int terminalAction_p(int var[]){
  if(var[0] >= 0 && var[0] < available_outputs){
    if(!is_pwm_output(var[1]))  {
      UART_PORT.println("Entered value: "+String(var[1])+", is not a pwm output"); 
      return 3;
    }
    analog_outputs[var[0]].set_pwm_pin(var[1]);
    UART_PORT.println("Was configurated PIN "+String(var[1])+" to analog output "+String(var[0]));
  }else{
    UART_PORT.println("Entered value for output is not in range from 0 to "+String(available_outputs));
    return 2;
  }
  return 0;
}

int terminalAction_w(int var[]){
  if(var[0] >= 0 && var[0] < available_outputs){
    analog_outputs[var[0]].write_eeprom();
    UART_PORT.println("Data for analog output: "+String(var[0])+" was written");
  }else{
    UART_PORT.println("Entered value for output is not in range from 0 to "+String(available_outputs));
    return 2;
  }
  return 0;
}

int terminalAction_r(int var[]){
  if(var[0] >= 0 && var[0] < available_outputs){
    analog_outputs[var[0]].read_eeprom();
    UART_PORT.println("Data for analog output: "+String(var[0])+" was read");
  }else{
    UART_PORT.println("Entered value for output is not in range from 0 to "+String(available_outputs));
    return 2;
  }
  return 0;
}

int terminalAction_s(int var[]){
  if(var[0] >= 0 && var[0] < available_outputs){
    analog_outputs[var[0]].write_output(var[1]);
    UART_PORT.println("Value: "+String(analog_outputs[var[0]].pin)+" was writen to port "+String(var[0]));
  }else{
    UART_PORT.println("Entered value for output is not in range from 0 to "+String(available_outputs));
    return 2;
  }
  return 0;
}

int terminalAction_q(int var[]){
  if(var[0] >= 0 && var[0] < available_outputs){
    analog_outputs[var[0]].set_range(var[1],var[2]);
    UART_PORT.println("Range was writen to port "+String(var[0])+", min: "+String(analog_outputs[var[0]].min_value)+" - max: "+String(analog_outputs[var[0]].max_value));
  }else{
    UART_PORT.println("Entered value for output is not in range from 0 to "+String(available_outputs));
    return 2;
  }
  return 0;
}

int terminalAction_g(int var[]){
  if(var[0] >= 0 && var[0] < available_outputs){
    UART_PORT.println("INFO FROM ANALOG PORT: "+String(var[0]));
    analog_outputs[var[0]].get_info();
  }else{
    UART_PORT.println("Entered value for output is not in range from 0 to "+String(available_outputs));
    return 2;
  }
  return 0;
}

int terminalAction_v(int var[]){
  if(var[0] >= 0 && var[0] < available_outputs){
    UART_PORT.println("v:"+
                        String(analog_outputs[var[0]].pin)+","+
                        String(analog_outputs[var[0]].min_value)+","+
                        String(analog_outputs[var[0]].max_value));
  }else{
    UART_PORT.println("Entered value for output is not in range from 0 to "+String(available_outputs));
    return 2;
  }
  return 0;
}

int terminalAction_h(int var[]){
  UART_PORT.println("Help String");
  return 0;
}
