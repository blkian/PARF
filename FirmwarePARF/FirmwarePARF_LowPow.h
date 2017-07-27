#ifndef FIRMWAREPARF_LOWPOW_H
#define FIRMWAREPARF_LOWPOW_H
/*==================[Descripcion]=============================================================*/

/*==================[TODO]====================================================================*/

/*==================[Dependencias]============================================================*/

/*==================[Definicion de macros externos]===========================================*/
// Definidos en iom328p.h
#define LOWPOW_ADC 0//PRADC 0
#define LOWPOW_UART 1//PRUSART0 1
#define LOWPOW_SPI 2//PRSPI 2
#define LOWPOW_TIMER1 3 //PRTIM1 3
#define LOWPOW_TIMER0 5//PRTIM0 5
#define LOWPOW_TIMER2 6//PRTIM2 6
#define LOWPOW_I2C 7//PRTWI 7
/*==================[Declaracion de funciones externas]=======================================*/

/**
 * Inicializa el periferico de bajo consumo en modo IDLE (para el CPU)
 * y deshabilita algunos otros periféricos
 */
void LowPow_init(void);

/**
 *  Entra al modo de bajo consumo
 */
void LowPow_start(void);

/*==================[Fin del archivo]=========================================================*/
#endif /* FIRMWAREPARF_LOWPOW_H */
