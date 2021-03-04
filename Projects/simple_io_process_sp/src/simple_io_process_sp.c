#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

uint8_t LED_D1 = 0;
float teste = 2.5;
float teste2 = 3.5;
float result = 0;

//Exercicio 3 (exercise_exception):
//� Quais s�o os valores dos registradores CONTROL e LR?
//  0x2 (FLAG SPSEL = 1) e 0x0000 0c2f quando 

//� Qual ponteiro de pilha est� sendo usado? Verifique na
//janela Registers do depurador (banco �CPU Registers�).


//QUANDO NA INSTRUCAO DA FUNCAO SYSTICK_HANDLER(VOID)
// CONTROL = 0x0
// LR = 0xffff ffed

//QUANDO CHEGA NA INSTRU��O DE INTERRUPCAO SYSTICK_HANDLER
// CONTROL = 0x4 (FLAG FPCA = 1, SP = SP_process)
// LR = 0x0000 0a23

//QUANDO NA INSTRU��O DA FUN��O MAIN
// CONTROL = 0x2 (FLAG FPCA = 0, FLAG SPSEL = 1, SP = SP_process)
// LR = 0x0000 0c2f
  
// S� consegui fazer o registrador CONTROL capturar a floating point unit
// colocando a opera��o de float DENTRO da fun��o SYSTICK_HANDLER(), ao contr�ro
// da fun��o MAIN como diz no enunciado do exerc�cio e com o breakpoint na 
// instru��o SYSTICK_HANDLER e n�o SYSTICK_HANDLER(VOID)


void SysTick_Handler(void){
  LED_D1 ^= GPIO_PIN_1; // Troca estado do LED D1
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, LED_D1); // Acende ou apaga LED D1
  result = teste*teste2; //colocando aqui o reg CONTROL seta a flag FPCA
} // SysTick_Handler

void main(void){
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); // Habilita GPIO N (LED D1 = PN1, LED D2 = PN0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)); // Aguarda final da habilita��o
  
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1); // LEDs D1 e D2 como sa�da
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0); // LEDs D1 e D2 apagados
  GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilita��o
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4); // LEDs D3 e D4 como sa�da
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0); // LEDs D3 e D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); // Habilita GPIO J (push-button SW1 = PJ0, push-button SW2 = PJ1)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)); // Aguarda final da habilita��o
    
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1); // push-buttons SW1 e SW2 como entrada
  GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

  SysTickIntEnable();
  SysTickEnable();

  while(1){
    teste++;
    result = teste*teste2;
    if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == GPIO_PIN_0)
      // Testa estado do push-button SW1
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0); // Apaga LED D3
    else
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4); // Acende LED D3
//
//    if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == GPIO_PIN_1) // Testa estado do push-button SW2
//      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // Apaga LED D4
//    else
//      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // Acende LED D4
  } // while
} // main