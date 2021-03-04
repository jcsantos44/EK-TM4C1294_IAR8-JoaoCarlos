#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

uint8_t LED_D1 = 0;
//uint32_t clock = 24000000;
//uint8_t delay = 1;
//uint8_t state2 = 0;
//
//typedef enum { off, on } state;
//state state1;

void SysTick_Handler(void){
  LED_D1 ^= GPIO_PIN_1; // Troca estado do LED D1
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, LED_D1); // Acende ou apaga LED D1
} // SysTick_Handler

void main(void){
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilitação
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4); // LEDs D3 e D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0); // LEDs D3 e D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  SysTickIntEnable();
  SysTickEnable();
  
//  uint32_t loops = delay*(clock/3);

  while(1){
    //para clock de 24000000Mhz
//    SysCtlDelay(8000000);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 1); 
//    SysCtlDelay(8000000);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
    
    //para clock de 120000000Mhz
    SysCtlDelay(40000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 1); 
    SysCtlDelay(40000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
    
    // Há variações na temporização do software nos casos de:
    //
    // 1. Diferentes níveis de otimização do compilador C
    // R: Neste código não, pois as funções utilizadas são feitas em assembly,
    // SysCtlDelay() é implementada em sempre terá um atraso de 3 instruções;
    // se houvesse código em C que precisasse ser compilado poderia haver uma
    // diferença.
    // 
    // 2. Frequência de clock de 120Mhz
    // R: Sim, pois o delay utilizado é feito com 3 instruções em assembly,
    // se mudar o clock é necessário alterar o número de loops de 3 instruções
    // para executar o mesmo delay.
    

    
    
//    if (state1 == on)
//      state1 = off;
//    else
//      state1 = on;
        
        
// Very hard to get the right interval by using for loops
//  for (int i = 0; i < loops; i++)
//  {
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 1);
//  }
//  for (int i = 0; i < loops; i++)
//  {
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
//  }
    
    // SysCtlDelay() //   "provides a means of generating a delay by executing a 
                     //   simple 3 instruction cycle loop a given number of times"
        
        
  } // while
} // main