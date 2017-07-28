#ifndef FIRMWAREPARF_WDT_H
#define FIRMWAREPARF_WDT_H
/*==================[Descripcion]=============================================================*/
/* Modulo encargado del manejo del periferico Watch Dog Timer (WDT) */

/*==================[TODO]====================================================================*/

/*==================[Dependencias]============================================================*/

/*==================[Definicion de macros externos]===========================================*/

/*==================[Declaracion de funciones externas]=======================================*/
/**
* Inicializo el periferico watchdog para que interrumpa cada 1 segundo y reseteo las cuentas
* Luego del segundo la interrupcion se deshabilita automaticamente y se tiene 1 segundo mas
* para resetear el WDT antes de que se reinicie el micro
*/
void WDT_reset(void);
/**
* Deshabilita el watchdog
*/
void WDT_off(void);

/*==================[Fin del archivo]=========================================================*/
#endif /* FIRMWAREPARF_WDT_H */
