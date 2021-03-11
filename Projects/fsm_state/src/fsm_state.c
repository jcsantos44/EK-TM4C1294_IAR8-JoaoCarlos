#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF com apenas 2 estados e 1 evento temporal que alterna entre eles
// Seleção por estado

//typedef enum {Desligado, Ligado} state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  static int Estado = 0; // estado inicial da MEF
  
  LEDInit(LED1);
  LEDInit(LED2);
  LEDInit(LED3);
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1){
    if(Evento){
      Evento=0;
      switch(Estado){
      case 0:
        LEDOff(LED1);
        LEDOff(LED2);
        LEDOff(LED3);
        Estado = 1;
        break;
      case 1:
        LEDOff(LED1);
        LEDOff(LED2);
        LEDOn(LED3);
        Estado = 2;
        break;
      case 2:
        LEDOff(LED1);
        LEDOn(LED2);
        LEDOn(LED3);
        Estado = 3;
        break;
      case 3:
        LEDOff(LED1);
        LEDOn(LED2);
        LEDOff(LED3);
        Estado = 4;
        break;
      case 4:
        LEDOn(LED1);
        LEDOn(LED2);
        LEDOff(LED3);
        Estado = 5;
        break;
      case 5:
        LEDOn(LED1);
        LEDOn(LED2);
        LEDOn(LED3);
        Estado = 0;
        break;
      }
    }
    
    // switch
  } // while
} // main
