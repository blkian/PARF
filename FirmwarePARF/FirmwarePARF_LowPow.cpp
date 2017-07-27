
/* =================[Inclusiones]============================================================ */
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "FirmwarePARF_LowPow.h"

/* =================[Definiciones y macros internos]========================================= */

/*==================[Declaracion de funciones internas]=======================================*/

/*==================[Definicion de datos internos]============================================*/

/*==================[Definicion de funciones internas]========================================*/

/*==================[Definicion de funciones externas]========================================*/

void LowPow_init(void){
  /* Apago el comparador analogico para minimizar el consumo (pag 301) */
  ACSR &= ~(1<<ACIE); // Deshabilitar interrupcion de comparador analogico
  ACSR |= (1<<ACD); // Deshabilitar comparador analogico
  
  /* Configuro el registro de reduccion de potencia (pag 71). 1 deshabilitado, 0 habilitado */
  PRR = (1<<PRTWI) | (1<<PRTIM2) | (0<<PRTIM0) | (1<<PRTIM1) | (0<<PRSPI) | (1<<PRUSART0) | (1<<PRADC);

  /* Selecciona modo IDLE y deshabilita el modo sleep */
  SMCR = (0<<SM2) | (0<<SM1) | (0<<SM0) | (0<<SE); 
} /* Sleep_init */

/*
void LowPow_habilitarPeriferico(uint8_t perif){
    PRR &= ~(1<<perif);
} 

void LowPow_deshabilitarPeriferico(uint8_t perif){
    PRR |= (1<<perif)
} 
*/


void LowPow_start(void){
  SMCR |= (1<<SE); //Habilita el modo sleep
  __asm__ __volatile__ ( "sleep" "\n\t" :: ); //Entra al modo sleep
  SMCR |= (0<<SE); //Deshabilita el modo sleep (necesario)
} /* Sleep_start */


/*==================[Definicion de ISR externas]==============================================*/

/*===================[Fin del archivo]========================================================*/
