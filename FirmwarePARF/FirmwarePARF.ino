/* =================[Inclusiones]============================================================ */
#include <Arduino.h>


// Includes de modulos personales
#include "FirmwarePARF_WDT.h"
#include "FirmwarePARF_Com.h"
#include "FirmwarePARF_IO.h"

/* =================[Definiciones y macros internos]========================================= */
#define TIEMPO_ESTOYVIVO 500
#define TIEMPO_ENVIODATOS 1000
/*==================[Declaracion de funciones internas]=======================================*/
/*==================[Definicion de datos internos]============================================*/

/*==================[Definicion de funciones internas]========================================*/
void setup() {
    IO_init();
    
    Com_init();
}

void loop() {
    static uint32_t tiempo_estoyVivo = 0, tiempo_envioDatos;
    if( Com_rxUpdate() ){
        if(millis() > tiempo_estoyVivo){
            tiempo_estoyVivo = millis() + TIEMPO_ESTOYVIVO;
            IO_toggleLed1();
       
        }
    }
    if( millis() > tiempo_envioDatos ){
        tiempo_envioDatos = millis() + TIEMPO_ENVIODATOS;
        Com_txUpdate();
        IO_toggleLed2();
    }
    
}
/*==================[Definicion de funciones externas]========================================*/

/*==================[Definicion de ISR externas]==============================================*/

/*===================[Fin del archivo]========================================================*/


