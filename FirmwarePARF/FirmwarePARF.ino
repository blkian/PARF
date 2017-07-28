/* =================[Inclusiones]============================================================ */
#include <Arduino.h>


// Includes de modulos personales
#include "FirmwarePARF_WDT.h"
#include "FirmwarePARF_Com.h"
#include "FirmwarePARF_IO.h"
#include "FirmwarePARF_LowPow.h"

/* =================[Definiciones y macros internos]========================================= */
#define TIEMPO_ESTOYVIVO 500
#define TIEMPO_ENVIODATOS 1000
/*==================[Declaracion de funciones internas]=======================================*/
/*==================[Definicion de datos internos]============================================*/

/*==================[Definicion de funciones internas]========================================*/
void setup() {
    LowPow_init(); // Habilita el modo bajo consumo y el WDT
    IO_init();
    //Com_init();
    delay(500);
    for(uint8_t i = 0;i<2;i++){
        LowPow_estoyVivo();
        IO_toggleLed1();
        delay(500);
    }
}

void loop() {
    static uint32_t tiempo_estoyVivo = 0, tiempo_envioDatos;

    uint8_t i = 0;

    LowPow_sleep(4);
    /*
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
    }*/
    
    for(i = 0;i<6;i++){
      LowPow_estoyVivo();
      IO_toggleLed1();
      delay(500);
    }

    //delay(1500);
    
}
/*==================[Definicion de funciones externas]========================================*/

/*==================[Definicion de ISR externas]==============================================*/

/*===================[Fin del archivo]========================================================*/


