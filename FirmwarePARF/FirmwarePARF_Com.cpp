
/* =================[Inclusiones]============================================================ */
#include <arduino.h>

#include "cc1101.h"
#include "ccpacket.h"

#include "FirmwarePARF_Com.h"
//#include "FirmwarePARF_IO.h"

/* =================[Definiciones y macros internos]========================================= */
#define HAB_UARTDEBUG 1

#define Com_PACKET_START 0x24 // caracter de inicio de paquete ($)
#define Com_PACKET_END 0x23 // caracter de final de paquete (#)

#define CC1101Interrupt 0 // Pin 0
#define CC1101_GDO0 2 // Pin 2
/*==================[Declaracion de funciones internas]=======================================*/
int16_t rssi(int8_t raw);
int lqi(char raw);
void messageReceived(void);
/*==================[Definicion de datos internos]============================================*/
static CC1101 radio;

static byte syncWord[2] = {199, 10};
static bool gPaqueteDisponible = false;
/*==================[Definicion de funciones internas]========================================*/
// Get signal strength indicator in dBm.
// Uso: Serial.print(rssi(packet.rssi)); // unidad en dBm
// See: http://www.ti.com/lit/an/swra114d/swra114d.pdf
int16_t rssi(int8_t raw) {
    int16_t rssi_dbm = 0;
    uint8_t rssi_dec = 0;
    
    //uint8_t rssi_offset = 74; // rssi_offset is dependent on baud and MHz; this is for 38.4kbps and 433 MHz.
    rssi_dec = (uint8_t) raw;
    if(rssi_dec >= 128){
        rssi_dbm = ((int16_t)( rssi_dec - 256) / 2) - 74; //rssi_offset;
    }
    else{
        rssi_dbm = (rssi_dec / 2) - 74; //rssi_offset;
    }
    return(rssi_dbm);
} /* rssi */

// Get link quality indicator.
// Uso: Serial.print(lqi(packet.lqi));
int lqi(char raw) {
    return 0x3F - raw;
} /* lqi */
/*==================[Definicion de funciones externas]========================================*/
void Com_init(void){
    if(HAB_UARTDEBUG){ Serial.begin(9600); }
  
    radio.init();
    radio.setSyncWord(syncWord);
    radio.setCarrierFreq(CFREQ_433);
    radio.disableAddressCheck();
    radio.setTxPowerAmp(PA_LongDistance);
    // habilito interrupcion por recepcion
    attachInterrupt(CC1101Interrupt, messageReceived, FALLING);
} /* Com_init */

bool Com_rxUpdate(void){
    bool packetOK = false;
    uint8_t packetLength = 0;
    
    if(gPaqueteDisponible){
        gPaqueteDisponible = false;
        CCPACKET packet;
        if(radio.receiveData(&packet) > 0){ // Si algo me llegó
            packetLength = packet.length;
            /*if(HAB_UARTDEBUG){ 
                Serial.print("Paquete recibido. Largo: "); Serial.println(packetLength);
                Serial.print("CRC OK: "); Serial.println(packet.crc_ok);
            }*/
            if(packet.crc_ok && packetLength > 0){ // Si el crc esta ok y el largo es mayor a 0
                packetOK = true;
                if(HAB_UARTDEBUG){ 
                    Serial.print("Addr: "); Serial.println(radio.devAddress);
                    Serial.print("data: ");
                    for(uint8_t i = 0; i<packetLength;i++){
                        Serial.write(packet.data[i]);
                    }
                    Serial.println();
                }
            }
        }
    }
    return(packetOK);
} /* Com_rxUpdate */
    
void Com_txUpdate(void){
    const char message[] = {65, 108, 111}; //Alo
    CCPACKET packet;
    
    packet.length = strlen(message);
    strncpy((char *) packet.data, message, packet.length);
    radio.sendData(packet);
} /* Com_txUpdate */


/*==================[Definicion de ISR externas]==============================================*/
// Funcion llamada cuando un mensaje es recibido
void messageReceived(void) {
    gPaqueteDisponible = true;
} /* messageReceived */
/*===================[Fin del archivo]========================================================*/

