#include "UART.h"

char last_char = CHAR_ENDS; 

void uart_init(void){
  UART_PORT.begin(UART_BAUD);  
}

bool uart_get(char *caracter_salida,int *size_,int _datos[]){
    bool bufferComplete = false,first_digit = false;
    char actual;
    int index = 0;
    String valores[20];

    if(last_char == CHAR_ENDS || last_char == NUMBERS_BETWEEN ){ //Si finalizo bien o con error de comma
      *caracter_salida = UART_PORT.read();
      last_char = *caracter_salida;
          if(*caracter_salida == CHAR_ENDS){
              #ifdef UART_LOG
                UART_PORT.println("ERROR: Message need start with a letter");
              #endif 
              return false;
          }
          if(*caracter_salida == NUMBERS_BETWEEN){
              #ifdef UART_LOG
                UART_PORT.println("ERROR: Message can not start with "+String(NUMBERS_BETWEEN));
              #endif 
              return false;
          }
          if(*caracter_salida >= 48 && *caracter_salida <= 57){
              #ifdef UART_LOG
                UART_PORT.println("ERROR: Message can not start with a number");
              #endif 
              last_char = *caracter_salida;
              return false;
          }
    }
    else{
      *caracter_salida = last_char;
      last_char = 0;
    }

    do{
      if(UART_PORT.available()){
        actual = UART_PORT.read();

          if((actual >= 48 && actual <= 57) || (actual == '-')){//Si el caracter es un digito
            first_digit = true;
            valores[index]+=actual;
            last_char = actual; 
          }
          else if(actual == NUMBERS_BETWEEN){
              if(last_char == NUMBERS_BETWEEN){
                  #ifdef UART_LOG 
                    UART_PORT.println("ERROR: It's no possible to put 2 "+String(NUMBERS_BETWEEN)+" followed");
                  #endif
                last_char = NUMBERS_BETWEEN;
                return false;
              }
              else if(!first_digit){
                 #ifdef UART_LOG 
                    UART_PORT.println("ERROR: It is need to put at least 1 number");
                  #endif
                last_char = NUMBERS_BETWEEN;
                return false;
              }
              else{   //Se cambio de numero correctamente
                  index++;
                  last_char = NUMBERS_BETWEEN;
              }
          }
          else if(actual == CHAR_ENDS){
              if(last_char == NUMBERS_BETWEEN) {
                  #ifdef UART_LOG 
                    UART_PORT.println("ERROR: Message can not end with "+String(NUMBERS_BETWEEN));
                  #endif
                last_char = NUMBERS_BETWEEN;
                return false;
              }
              
            if(first_digit){
              last_char = CHAR_ENDS;
              bufferComplete=true;
            }
            else{
                #ifdef UART_LOG 
                    UART_PORT.println("ERROR: Needs at least ONE argument "+String(NUMBERS_BETWEEN));
                  #endif
                last_char = CHAR_ENDS;
                *size_=0;
                return true;
            }
          }
          else{
              #ifdef UART_LOG
                if(last_char >= 48 && last_char <= 57)  UART_PORT.println("You can not finish message with a letter");
                else                                    UART_PORT.println("It's not possible to put 2 letters followed");
              #endif
              last_char = actual;
              return false;
          }
      }
    }while(!bufferComplete);

      *size_ = index+1;
      for(int i = 0;i<=index;i++) _datos[i]=valores[i].toInt();
    return true;    
}
