
/* =================[Inclusiones]============================================================ */
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include <avr/wdt.h>

#include "FirmwarePARF_WDT.h"
#include "FirmwarePARF_LowPow.h"

/* =================[Definiciones y macros internos]========================================= */

/*==================[Declaracion de funciones internas]=======================================*/

/*==================[Definicion de datos internos]============================================*/

/*==================[Definicion de funciones internas]========================================*/

/*==================[Definicion de funciones externas]========================================*/
void WDT_reset(void){
    /* Watchdog Timer Prescale (pag 81):
    WDP[3:0] = 0000 => 16ms
    WDP[3:0] = 0110 => 1s
    WDP[3:0] = 1000 => 4s
    WDP[3:0] = 1001 => 8s
    */
	  MCUSR = 0; // reseteo flags de status                              
    WDTCSR |=(1<<WDCE) | (1<<WDE); // Entro al modo de configuracion del WDT
  	// Habilito interr WDT y seteo tiempo en 1 seg
  	WDTCSR = (1<<WDIE) | (0<<WDE) | (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0); 

    wdt_reset();
} /* WD_init */


void WDT_off(void){
    cli();
    wdt_reset();
    MCUSR = 0; // reseteo flags de status   
  
    // Entro al modo de configuracion del watchdog
    WDTCSR |=(1<<WDCE) | (1<<WDE);
    // Deshabilito el watchdog
    WDTCSR = 0;
  
    sei();
} /* WD_off */

/*==================[Definicion de ISR externas]==============================================*/
ISR(WDT_vect){
    int16_t contador = LowPow_getContador();
    // Verifico si estoy en modo bajo consumo o si se tildo el programa
    if(contador > 0){ // modo bajo consumo
        LowPow_setContador(contador-1);
        wdt_reset();
    } else { // programa tildado
        MCUSR = 0;                          // reset flags
        // Reseteo el micro
        WDTCSR |=(1<<WDCE) | (1<<WDE);
        // Habilito el reset para dentro de 1 segundo a menos que algo lo detenga.
        // IMPORTANTE: como deshabilito la interrupcion es necesario volver a iniciarla con WDT_init()
        WDTCSR = (0<<WDIE) | (1<<WDE) | (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0); 
    }
}
/*===================[Fin del archivo]========================================================*/
