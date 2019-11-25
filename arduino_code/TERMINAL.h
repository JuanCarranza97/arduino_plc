#ifndef TERMINAL_H
#define TERMINAL_H

  #include <Arduino.h>

  #include "ARDUINO_PLC.h"
  
  typedef int (*terminalCallback)(int var[]);  

  typedef struct{
    terminalCallback Callback;
    const char caracter;
    int tam;
  }terminal_actions;

  void terminal_lab(void);
   
  int terminalAction_a(int var[]);
  int terminalAction_p(int var[]);
  int terminalAction_w(int var[]);
  int terminalAction_r(int var[]);
  int terminalAction_s(int var[]);
  int terminalAction_q(int var[]);
  int terminalAction_g(int var[]);
  int terminalAction_v(int var[]);
  int terminalAction_h(int var[]);
 
#endif*/
