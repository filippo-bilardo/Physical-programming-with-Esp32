#include <Arduino.h>
#include <esp_now.h>
#include <TFT_eSPI.h>
#include "WiFi.h"
#include "MyBtn.h"
#include "MyTft.h"
#include "L1_EspNow.h"
#include "ESPNow_Broadcast.h"

extern TFT_eSPI tft;

#define EVNT_NONE 0
#define EVNT_P1_CLICK 1
#define EVNT_P2_CLICK 2

void EspNowTxTestCallback(const uint8_t *macAddr, esp_now_send_status_t status);
void EspNowRxTest(const uint8_t * macAddr, const uint8_t *incomingData, int dataLen);

/////////////////////////////////////////////////////////////////
void EspNowTxTestCallback(const uint8_t *macAddr, esp_now_send_status_t status) {
  
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void EspNowBroadcastInit() {
  
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(EspNowTxTestCallback);
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(EspNowRxTest);  
}

void EspNowTxTestTask() {
  
  uint8_t evento;
  if(btnDwIsClicked()) {
    evento=EVNT_P1_CLICK;
    Serial.println("TX EVNT_P1_CLICK");
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.println("TX EVNT_P1_CLICK"); 
    tft.fillCircle(tft.width()/2, tft.height()/2, 30, TFT_BLUE);
    tft.drawCircle(tft.width()/2, tft.height()/2, 30, TFT_YELLOW);
    L1_EspNowTx(&evento, sizeof(evento));
  }
  if(btnUpIsClicked()) {
    evento=EVNT_P2_CLICK;
    Serial.println("TX EVNT_P2_CLICK");
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.println("TX EVNT_P2_CLICK"); 
    tft.fillCircle(tft.width()/2, tft.height()/2, 30, TFT_RED);
    tft.drawCircle(tft.width()/2, tft.height()/2, 30, TFT_YELLOW);
    L1_EspNowTx(&evento, sizeof(evento));
  }
}
// callback function that will be executed when data is received
void EspNowRxTest(const uint8_t *macAddr, const uint8_t *incomingData, int dataLen) {
  
  char macStr[13];
  snprintf(macStr, sizeof(macStr), "%02X%02X%02X-%02X%02X%02X", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
  Serial.printf("Received message from: %s\n", macStr);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.print("RX ");
  tft.println(macStr);

  int evento=EVNT_NONE;
  memcpy(&evento, incomingData, sizeof(evento));
  if(evento==EVNT_P1_CLICK) {
    Serial.println("RX EVNT_P1_CLICK");
    tft.println("RX EVNT_P1_CLICK"); 
    tft.fillCircle(tft.width()/2, tft.height()/2, 30, TFT_GREEN);
    tft.drawCircle(tft.width()/2, tft.height()/2, 30, TFT_YELLOW);
  } else if (evento==EVNT_P2_CLICK) {
    Serial.println("RX EVNT_P2_CLICK");
    tft.println("RX EVNT_P2_CLICK"); 
    tft.fillCircle(tft.width()/2, tft.height()/2, 30, TFT_MAGENTA);
    tft.drawCircle(tft.width()/2, tft.height()/2, 30, TFT_YELLOW);
  }
}
