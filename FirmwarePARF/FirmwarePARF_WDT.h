#ifndef FIRMWAREPARF_WDT_H
#define FIRMWAREPARF_WDT_H
/*==================[Descripcion]=============================================================*/
/* Modulo encargado del manejo del periferico Watch Dog Timer (WDT) */

/*==================[TODO]====================================================================*/

/*==================[Dependencias]============================================================*/

/*==================[Definicion de macros externos]===========================================*/

/*==================[Declaracion de funciones externas]=======================================*/
/**
* Inicializo el periferico de Watchdog, configurado para resetear el micro
* si no se resetea durante 8 segundos
* Recomendacion: antes de inicializar el wd, utilizar WDT_off()
*/
void WDT_init(void);
/**
* Vuelve a 0 las cuentas del watchdog para evitar el reseteo del micro
*/
void WDT_reset(void);
/**
* Deshabilita el watchdog
*/
void WDT_off(void);

/*==================[Fin del archivo]=========================================================*/
#endif /* FIRMWAREPARF_WDT_H */
