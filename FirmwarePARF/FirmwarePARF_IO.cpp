/* =================[Inclusiones]============================================================ */
#include <arduino.h>

#include "FirmwarePARF_IO.h"

/* =================[Definiciones y macros internos]========================================= */
// Definicion de salidas
#define IO_POTE A1 // Pin a donde esta conectado el potenciometro

#define IO_STATUSLED_1 5
#define IO_STATUSLED_2 6

/*==================[Declaracion de funciones internas]=======================================*/

/*==================[Definicion de datos internos]============================================*/


/*==================[Definicion de funciones internas]========================================*/

/*==================[Definicion de funciones externas]========================================*/

void IO_init(void){
    pinMode(IO_STATUSLED_1,OUTPUT);
    digitalWrite(IO_STATUSLED_1, 0);
    pinMode(IO_STATUSLED_2,OUTPUT);
    digitalWrite(IO_STATUSLED_2, 0);
} /* IO_init */

uint16_t IO_getValorPote(void){
    return( analogRead(IO_POTE) );
} /* IO_getValorPote */

void IO_toggleLed1(void){
    static bool led_status = false;
  
    led_status = !led_status;
    digitalWrite(IO_STATUSLED_1, led_status);
} /* IO_toggleLed1 */

void IO_toggleLed2(void){
    static bool led_status = false;
  
    led_status = !led_status;
    digitalWrite(IO_STATUSLED_2, led_status);
} /* IO_setLed2 */


/*==================[Definicion de ISR externas]==============================================*/

/*===================[Fin del archivo]========================================================*/
