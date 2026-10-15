#include <Arduino.h>
#include <esp_now.h>
#include "L1_EspNow.h"

// E' possibile sia la comunicazione unicast che broadcast
// MAC Address of your receiver 
uint8_t macaddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//uint8_t macaddr01[] = {0x3C, 0x61, 0x05, 0x0B, 0xA7, 0x10}; //Board1 3C:61:05:0B:A7:10
//uint8_t macaddr02[] = {0x30, 0xC6, 0xF7, 0x25, 0xAF, 0x44}; //Board2 30:C6:F7:25:AF:44
//uint8_t macaddr03[] = {0x30, 0xC6, 0xF7, 0x25, 0xAE, 0xF8}; //Board3 30:C6:F7:25:AE:F8
//uint8_t macaddr04[] = {0x30, 0xC6, 0xF7, 0x25, 0xAA, 0xA8}; //Board4 30:C6:F7:25:AA:A8
//uint8_t macaddrFF[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //Broadcast address

esp_now_peer_info_t peerInfo;
 
/////////////////////////////////////////////////////////////////
void L1_EspNowInit() {

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  memcpy(peerInfo.peer_addr, macaddr, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false; 
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

/////////////////////////////////////////////////////////////////
void L1_EspNowTx(uint8_t *data, size_t len) {
  // Send message via ESP-NOW
  //esp_err_t result = esp_now_send(macaddr, (uint8_t *)&myData, sizeof(myData));
  esp_err_t result = esp_now_send(macaddr, data, len);
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  } else {
    Serial.println("Sending error");
  } 
}
