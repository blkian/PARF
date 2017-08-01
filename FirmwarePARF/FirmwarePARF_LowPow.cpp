
/* =================[Inclusiones]============================================================ */
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include <avr/power.h>
#include <avr/sleep.h>


#include "FirmwarePARF_LowPow.h"
#include "FirmwarePARF_WDT.h"

// Fuentes: http://www.gammon.com.au/interrupts
// http://folk.uio.no/jeanra/Microelectronics/ArduinoWatchdog.html

/* =================[Definiciones y macros internos]========================================= */

/*==================[Declaracion de funciones internas]=======================================*/
void deshabilitarPerifericos(void);
void habilitarPerifericos(void);
/*==================[Definicion de datos internos]============================================*/
volatile static int16_t gCiclosBajoConsumo = 0;

/*==================[Definicion de funciones internas]========================================*/
void habilitarPerifericos(void){
    // Deshabilito perifericos que no utilizo (pag 71)
    // PRR = (1<<PRTWI) | (1<<PRTIM2) | (0<<PRTIM0) | (1<<PRTIM1) | (0<<PRSPI) | (1<<PRUSART0) | (1<<PRADC);
    power_adc_disable();
    power_spi_enable();
    power_usart0_enable();
    power_timer0_enable();
    power_timer1_disable();
    power_timer2_disable();
    power_twi_disable(); 
} /* habilitarPerifericos */
/*==================[Definicion de funciones externas]========================================*/

void LowPow_init(void){
    cli();
    habilitarPerifericos();
  	WDT_reset();
  	sei();
} /* Sleep_init */

int16_t LowPow_getContador(void){
	  return(gCiclosBajoConsumo);
} /* LowPow_getContador */

void LowPow_setContador(int16_t nuevoVal){
    gCiclosBajoConsumo = nuevoVal;
} /* LowPow_setContador */

void LowPow_sleep(int16_t segundos){
    char adcsra_save = ADCSRA;
    cli();
    gCiclosBajoConsumo = segundos; // Seteo el tiempo de sleep
    WDT_reset(); // Reinicializo el WDT para volver a habilitar la interrupcion y resetear las cuentas
    
    // Deshabilito perifericos para reducir el consumo
    ADCSRA = 0;  // deshabilito ADC
    power_all_disable(); // Deshabilito todos los perifericos para bajar el consumo
    // Habilito el modo de bajo consumo. Solo el WDT y interrupciones externas lo resetean
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_bod_disable();
    sei();
    while (gCiclosBajoConsumo > 0){ // Espero los ciclos que tengo que dormir
  
        // Habilito el modo en bajo consumo y lo inicio
        //sleep_mode();
        sleep_cpu();
        // De este punto el micro no pasa hasta que lo despierten
        // Cuando lo hacen entra a la interrupcion que lo desperto y continua
    }
   
    // Habilito todo nuevamente
    ADCSRA = adcsra_save;  // habilito ADC
    habilitarPerifericos(); // Habilito el resto de los perifericos
} /* Sleep_start */

void LowPow_estoyVivo(void){
    WDT_reset();
} /* LowPow_estoyVivo */


/* Ejemplo de prueba
  void setup() {
      IO_init();
      LowPow_init(); // Habilita el modo bajo consumo y el WDT
      delay(500);
      for(uint8_t i = 0;i<2;i++){
          LowPow_estoyVivo();
          IO_toggleLed1();
          delay(500);
      }
  }

  void loop() {
    uint8_t i = 0;

    LowPow_sleep(4);
       
    for(i = 0;i<6;i++){
        LowPow_estoyVivo();
        IO_toggleLed1();
        delay(500);
    }

    // Para ver si el reset de watchdog funciona cuando no esta en modo sleep pongo un delay.
    // Si la interrupcion salta (1 seg de no resetear el wdt) y no estoy en modo sleep pongo tengo
    // 1 segundo para resetear la cuenta del WDT y sino me apago.
    // O sea que tengo 2 segundos para resetear el WDT antes de que se apague. 
    // Por eso con un delay(1500) = 1.5seg el watchdog no resetea, y con uno de 2500 si   
  }
*/

/*==================[Definicion de ISR externas]==============================================*/

/*===================[Fin del archivo]========================================================*/
