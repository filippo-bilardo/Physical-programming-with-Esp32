/** ****************************************************************************************
 * @file NCP.h
 *
 * @brief Network Comunication Protocol
 * 
 *  
 * @author Filippo Bilardo
 * @version 1.0  30/04/22  Versione iniziale
 */
#include <esp_now.h>

#define BOARD_ADDRESS   3 //Ogni scheda deve avere un indirizzo differente
#define BOARD_ADDR1     1 //Indirizzo della scheda 1
#define BOARD_ADDR2     2 //Indirizzo della scheda 2
#define BOARD_ADDR3     3 //Indirizzo della scheda 3

#define EVNT_NONE       0
#define EVNT_P1_PRESS   1
#define EVNT_P2_PRESS   2
#define EVNT_P1_CLICK   3
#define EVNT_P2_CLICK   4

#define LED1_PIN        21
#define LED2_PIN        27


void NcpInit();
void L7_TxTask(void * pvParameters);
void L2_TxTask(void * pvParameters);
void L1_TxTask(void * pvParameters);
void L7_RxTask(void * pvParameters);
void L2_RxTask(void * pvParameters);
void L1_TxCallback(const uint8_t *mac_addr, esp_now_send_status_t status);
void L1_RxCallback(const uint8_t *mac, const uint8_t *incomingData, int len);
