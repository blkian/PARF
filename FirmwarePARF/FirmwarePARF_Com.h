#ifndef FIRMWAREPARF_COM_H
#define FIRMWAREPARF_COM_H
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
 * Actualiza la recepcion de la comunicacion
 */
bool Com_rxUpdate(void);

/**
 * Envia datos a traves del cc1101
 */
void Com_txUpdate(void);
/*==================[Fin del archivo]=========================================================*/
#endif /* FIRMWAREPARF_COM_H */
