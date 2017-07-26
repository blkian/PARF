#ifndef ARDUWATCHDOG_IO_H
#define ARDUWATCHDOG_IO_H
/*==================[Descripcion]=============================================================*/
/* Modulo encargado de manejar las entradas y salidas digitales y analogicas del sistema */
/*==================[TODO]====================================================================*/

/*==================[Dependencias]============================================================*/

/*==================[Definicion de macros externos]===========================================*/

/*==================[Declaracion de funciones externas]=======================================*/
/**
 * Inicializa las entradas y salidas digitales y analogicas del sistema
 */
void IO_init(void);

/**
 * Parpadea el led de status para inicidar que el sistema está activo
 */
void IO_estoyVivo(void);

/**
 * Devuelve el valor analogico del potenciometro con una resolucion de 10 bits
 */
uint16_t IO_getValorPote(void);

void IO_toggleLed1(void);

void IO_setLed2(bool estado);
/*==================[Fin del archivo]=========================================================*/
#endif /* ARDUWATCHDOG_IO_H */
