
/* =================[Inclusiones]============================================================ */
#include <arduino.h>

#include <cc1101.h>
#include <ccpacket.h>
//#include <util/crc16.h>

#include "arduWatchdog_Com.h"
#include "arduWatchdog_IO.h"

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

bool Com_paqueteDisponible(void){
    return(gPaqueteDisponible);
} /* Com_paqueteDisponible */

void Com_rxUpdate(void){
    static uint32_t miTiempo = 0;
    static uint16_t counter = 0;
    uint8_t packetLength = 0;

    if (gPaqueteDisponible) {
        gPaqueteDisponible = false;
        CCPACKET packet;
        if (radio.receiveData(&packet) > 0) { // Si algo me llegó
            if(HAB_UARTDEBUG){ 
              /*
              Serial.println(F("Received packet..."));
              Serial.print(F("lqi: ")); Serial.print(lqi(packet.lqi));
              Serial.print(F(" ; rssi: ")); Serial.print(rssi(packet.rssi)); Serial.println(F("dBm"));
              */
            }
            packetLength = packet.length;
            if (packet.crc_ok && packetLength > 0) { // Si el crc esta ok y el largo es mayor a 0
                /*
                if(HAB_UARTDEBUG){ 
                  Serial.print(F("packet: len "));Serial.println(packetLength);
                  Serial.println("data: ");
                  for(uint8_t i = 0; i<packetLength;i++){
                    Serial.write(packet.data[i]);
                  }
                  Serial.println();
                }
                */
                
                if( packet.data[0] == '$'){
                  if(millis() > miTiempo){
                    miTiempo = millis() + 100;
                    
                    IO_toggleLed1();
                    IO_setLed2(0);
                  }
                  if(HAB_UARTDEBUG){ 
                      uint8_t id = packet.data[1] + '0';
                      Serial.write(id); Serial.write(id); Serial.write(id); Serial.write(id); Serial.write(id);
                      Serial.println();
                    }
                }
            }
            else{
              IO_setLed2(1);
            }
        }
        else{
          IO_setLed2(1);
        }
    }
} /* Com_rxUpdate */

/*==================[Definicion de ISR externas]==============================================*/
// Funcion llamada cuando un mensaje es recibido
void messageReceived(void) {
    gPaqueteDisponible = true;
} /* messageReceived */
/*===================[Fin del archivo]========================================================*/

