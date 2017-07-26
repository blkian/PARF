/* =================[Inclusiones]============================================================ */
#include <Arduino.h>


// Includes de modulos personales
#include "arduWatchdog_WD.h"
#include "arduWatchdog_Com.h"
#include "arduWatchdog_IO.h"

/* =================[Definiciones y macros internos]========================================= */

/*==================[Declaracion de funciones internas]=======================================*/
/*==================[Definicion de datos internos]============================================*/

/*==================[Definicion de funciones internas]========================================*/
void setup() {
    IO_init();
    
    Com_init();
}

void loop() {
    Com_rxUpdate();
}
/*==================[Definicion de funciones externas]========================================*/

/*==================[Definicion de ISR externas]==============================================*/

/*===================[Fin del archivo]========================================================*/


