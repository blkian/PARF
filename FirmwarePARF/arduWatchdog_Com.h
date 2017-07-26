#ifndef ARDUWATCHDOG_COM_H
#define ARDUWATCHDOG_COM_H
/*==================[Descripcion]=============================================================*/

/*==================[TODO]====================================================================*/

/*==================[Dependencias]============================================================*/

/*==================[Definicion de macros externos]===========================================*/
/*==================[Declaracion de funciones externas]=======================================*/
/**
 * Inicializa la comunicacion serie y el buffer de recepcion
 */
void Com_init(void);

/**
 * Devuelve 1 si hay un paquete disponible en el receptor
 */
bool Com_paqueteDisponible(void);

/**
 * Actualiza la recepcion de la comunicacion
 */
void Com_rxUpdate(void);
/*==================[Fin del archivo]=========================================================*/
#endif /* ARDUWATCHDOG_COM_H */
