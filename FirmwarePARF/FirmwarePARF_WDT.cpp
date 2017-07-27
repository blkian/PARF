
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
void WDT_init(void){
    cli();
    wdt_reset();
    /* Watchdog Timer Prescale (pag 81):
    WDP[3:0] = 0000 => 16ms
    WDP[3:0] = 0110 => 1s
    WDP[3:0] = 1000 => 4s
    WDP[3:0] = 1001 => 8s
    */
    // Entro al modo de configuracion del watchdog
    WDTCSR |=(1<<WDCE) | (1<<WDE);
    // Configuro el watchdog para resetear al micro si en 8segundos no responde
    WDTCSR = (0<<WDIE) | (1<<WDE) | (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0);
  
    sei();
} /* WD_init */


void WDT_reset(void){
    wdt_reset();
} /* WD_reset */


void WDT_off(void){
    cli();
    wdt_reset();
  
    // Entro al modo de configuracion del watchdog
    WDTCSR |=(1<<WDCE) | (1<<WDE);
    // Deshabilito el watchdog
    WDTCSR = 0;
  
    sei();
} /* WD_off */

/*==================[Definicion de ISR externas]==============================================*/

/*===================[Fin del archivo]========================================================*/
