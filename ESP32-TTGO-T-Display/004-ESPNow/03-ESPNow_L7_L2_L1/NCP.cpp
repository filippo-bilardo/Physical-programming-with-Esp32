#include <Arduino.h>
#include <esp_now.h>
#include "NCP.h"
#include "MyTft.h"
#include "MyBtn.h"
#include "L1_EspNow.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;
QueueHandle_t xCoda_L7TxL2Tx;
QueueHandle_t xCoda_L2TxL1Tx;
QueueHandle_t xCoda_L1RxL2Rx;
QueueHandle_t xCoda_L2RxL7Rx;
QueueHandle_t xCoda_L2L2;
TaskHandle_t L7_TxTaskID;
TaskHandle_t L2_TxTaskID;
TaskHandle_t L1_TxTaskID;
TaskHandle_t L7_RxTaskID;
TaskHandle_t L2_RxTaskID;
TaskHandle_t L1_RxTaskID;

// Structure to receive and trasmit data
// Must match the sender structure
typedef struct struct_frame {
    int src;
    int dst;
    int data;
} struct_frame;

extern uint8_t espnow_macaddr[];

/////////////////////////////////////////////////////////////////
void NcpInit() {

  //Creazione dei task
  // L7_TxTask ----------------------------
  xTaskCreatePinnedToCore(
                    L7_TxTask,   /* Task function. */
                    "L7_TxTask", /* name of task. */
                    1000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &L7_TxTaskID,/* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  

  // L7_RxTask ----------------------------
  xTaskCreatePinnedToCore(
                    L7_RxTask,  /* Task function. */
                    "L7_RxTask",/* name of task. */
                    1000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &L7_RxTaskID,/* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */

  // L2_TxTask ----------------------------
  xTaskCreatePinnedToCore(
                    L2_TxTask,  /* Task function. */
                    "L2_TxTask",/* name of task. */
                    1000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &L2_TxTaskID,/* Task handle to keep track of created task */
                    1);          /* pin task to core 0 */                  
//  xTaskCreate(L2_TxTask,          /* Pointer to the function that implements the task.              */
//                    "L2_TxTask",  
//                    1000,        /* Stack depth in words.                */
//                    NULL,         /* We are not using the task parameter. */
//                    1,            /* This task will run at priority 1.    */
//                    &L2_TxTaskID);/* We are not using the task handle.    */
  // L2_RxTask ----------------------------
  xTaskCreatePinnedToCore(
                    L2_RxTask,  /* Task function. */
                    "L2_RxTask",/* name of task. */
                    1000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &L2_TxTaskID,/* Task handle to keep track of created task */
                    1);          /* pin task to core 0 */                  
//  xTaskCreate(L2_RxTask,          /* Pointer to the function that implements the task.              */
//                    "L2_RxTaskID",  
//                    1000,        /* Stack depth in words.                */
//                    NULL,         /* We are not using the task parameter. */
//                    1,            /* This task will run at priority 1.    */
//                    &L2_RxTaskID);/* We are not using the task handle.    */
  // L1_TxTask ----------------------------
  xTaskCreatePinnedToCore(
                    L1_TxTask,  /* Task function. */
                    "L1_TxTask",/* name of task. */
                    1000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &L1_TxTaskID,/* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  

  // L1_RxTask ----------------------------
  //L1_RxCallback 

  //Creazione delle code utilizate nella comunicazione tra layer
  //Della dimensione del frame da passare
  xCoda_L7TxL2Tx=xQueueCreate(5,sizeof(struct_frame));
  xCoda_L2TxL1Tx=xQueueCreate(5,sizeof(struct_frame));
  xCoda_L1RxL2Rx=xQueueCreate(5,sizeof(struct_frame));
  xCoda_L2RxL7Rx=xQueueCreate(5,sizeof(struct_frame));
  xCoda_L2L2=xQueueCreate(5,sizeof(struct_frame));

  //Inizializzazione del livello fisico
  L1_EspNowInit();
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(L1_TxCallback);
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(L1_RxCallback);

  //Inizializzazione dei led da comandare
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  gpio_set_drive_capability((gpio_num_t)LED1_PIN, GPIO_DRIVE_CAP_2);
  gpio_set_drive_capability((gpio_num_t)LED2_PIN, GPIO_DRIVE_CAP_2);
  
  tft.setCursor(0,0);
  tft.println("NCP start.");
}

/////////////////////////////////////////////////////////////////
void L7_TxTask(void * pvParameters) {

  // Create a struct_frame called myFrame
  struct_frame myFrame;

  Serial.print("L7_TxTask start on core ");
  Serial.println(xPortGetCoreID());
  myFrame.data=EVNT_NONE;
  myFrame.src=BOARD_ADDRESS;
  
  for(;;) {
    if(btnDwIsClicked()) {
      myFrame.dst=BOARD_ADDR1;
      myFrame.data=EVNT_P1_CLICK;
      if(myFrame.src==myFrame.dst) {
        xQueueSend(xCoda_L2RxL7Rx, &myFrame, portMAX_DELAY);
      } else {
        xQueueSend(xCoda_L7TxL2Tx, &myFrame, portMAX_DELAY); 
      }
      Serial.println("L7_TxTask - btnDwIsClicked");
    }
    if(btnUpIsClicked()) {
      myFrame.dst=BOARD_ADDR2;
      myFrame.data=EVNT_P2_CLICK;
      if(myFrame.src==myFrame.dst) {
        xQueueSend(xCoda_L2RxL7Rx, &myFrame, portMAX_DELAY);
      } else {
        xQueueSend(xCoda_L7TxL2Tx, &myFrame, portMAX_DELAY); 
      }
      Serial.println("L7_TxTask - btnUpIsClicked");
    }
    
    vTaskDelay(10); //Prevent Task watchdog got triggered
  } 
}
/////////////////////////////////////////////////////////////////
void L2_TxTask(void * pvParameters) {
  //Crea il frame con l'indirizzo sorgente
  //Calcola del Frame Check Sequence
  //In base all'indirizzo di destinazione invia al corretto L1
  
  // Create a struct_frame called myFrame
  struct_frame myFrame;
  
  Serial.print("L2_TxTask start on core ");
  Serial.println(xPortGetCoreID());

  for(;;) {
//    if(xQueueReceive(xCoda_L7TxL2Tx, &myFrame, 0) == pdPASS ){
//      Serial.println("L2_TxTask - xCoda_L7TxL2Tx");
//      Serial.println(myFrame.data);
//      Serial.println(myFrame.dst);
//      myFrame.src=BOARD_ADDRESS;
//      //myFrame.fcs; //Calcolo del Frame Check Sequence
//      if(myFrame.src==myFrame.dst) {
//        xQueueSend(xCoda_L2L2, &myFrame, portMAX_DELAY);
//      } else {
//        xQueueSend(xCoda_L2TxL1Tx, &myFrame, portMAX_DELAY); 
//      }
//    }
    
    vTaskDelay(10); //Prevent Task watchdog got triggered
  }    
}
/////////////////////////////////////////////////////////////////
void L1_TxTask(void * pvParameters) {

  struct_frame myFrame; // Create a struct_frame called myFrame

  Serial.print("L1_TxTask start on core ");
  Serial.println(xPortGetCoreID());

  for(;;) {
    if(xQueueReceive(xCoda_L7TxL2Tx, &myFrame, 0)==pdPASS) {
      Serial.println("L1_TxTask - xCoda_L2TxL1Tx");
      Serial.println(myFrame.data);

      //---Debug--- visulizza ciò che invia
      if(myFrame.data==EVNT_P1_CLICK) {
        Serial.println("TX EVNT_P1_CLICK");
        tft.setCursor(0, 0);
        tft.println("TX EVNT_P1_CLICK"); 
        tft.fillCircle(tft.width()/2, tft.height()/2, 30, TFT_BLUE);
        tft.drawCircle(tft.width()/2, tft.height()/2, 30, TFT_YELLOW);
      } else if (myFrame.data==EVNT_P2_CLICK) {
        Serial.println("TX EVNT_P2_CLICK");
        tft.setCursor(0, 0);
        tft.println("TX EVNT_P2_CLICK"); 
        tft.fillCircle(tft.width()/2, tft.height()/2, 30, TFT_RED);
        tft.drawCircle(tft.width()/2, tft.height()/2, 30, TFT_YELLOW);
      }
      //---Fine Debug---
      
      // Send message via ESP-NOW
      esp_err_t result = esp_now_send(espnow_macaddr, (uint8_t *)&myFrame, sizeof(myFrame));
      if (result == ESP_OK) {
        Serial.println("Sending confirmed");
      } else {
        Serial.println("Sending error");
      }      

    }
      
    vTaskDelay(10); //Prevent Task watchdog got triggered
  } 
}

/////////////////////////////////////////////////////////////////
// Callback function executed when data is received
void L1_RxCallback(const uint8_t *mac, const uint8_t *incomingData, int len) {
  //Se esiste un solo L1 i dati potevano andare direttamente al L2
  //Con questa funzione sarà possibile aggiungere in futuro altri L1
  
  //struct_frame myFrame; // Create a struct_frame called myFrame
  //memcpy(&myFrame, incomingData, sizeof(myFrame));
  //xQueueSendToBack(xCoda_L1RxL2Rx, &myFrame, portMAX_DELAY); 
  xQueueSendToBack(xCoda_L1RxL2Rx, incomingData, portMAX_DELAY); 
}

/////////////////////////////////////////////////////////////////
void L2_RxTask(void * pvParameters) {
  
  struct_frame myFrame; // Create a struct_frame called myFrame

  Serial.print("L2_RxTask start on core ");
  Serial.println(xPortGetCoreID());

  for(;;) {
    if(xQueueReceive(xCoda_L1RxL2Rx, &myFrame, 0)==pdPASS) {
      Serial.println("xCoda_L1RxL2Rx");
      Serial.println(myFrame.data);
      Serial.println(myFrame.src);
      Serial.println(myFrame.dst);
      //Controllo del frame ricevuto: fcs e dest addr
      if(myFrame.dst==BOARD_ADDRESS) {
        //Destinazione corretta passo i dati al layer superiore
        xQueueSend(xCoda_L2RxL7Rx, &myFrame, 0); 
      } 
    }
  
    vTaskDelay(10); //Prevent Task watchdog got triggered
  }    
}
/////////////////////////////////////////////////////////////////
void L7_RxTask(void * pvParameters) {

  struct_frame myFrame; // Create a struct_frame called myFrame

  Serial.print("L7_RxTask start on core ");
  Serial.println(xPortGetCoreID());
  
  for(;;) {
    if(xQueueReceive(xCoda_L2RxL7Rx, &myFrame, 0) == pdPASS) {
      Serial.println("xCoda_L2RxL7Rx");
      Serial.println(myFrame.data);
      Serial.println(myFrame.src);
      if(myFrame.data==EVNT_P1_CLICK) {
        Serial.println("RX EVNT_P1_CLICK");
        tft.setCursor(0, 0);
        tft.println("RX EVNT_P1_CLICK"); 
        tft.fillCircle(tft.width()/2, tft.height()/2, 30, TFT_GREEN);
        tft.drawCircle(tft.width()/2, tft.height()/2, 30, TFT_YELLOW);
        digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
      } else if (myFrame.data==EVNT_P2_CLICK) {
        Serial.println("RX EVNT_P2_CLICK");
        tft.setCursor(0, 0);
        tft.println("RX EVNT_P2_CLICK"); 
        tft.fillCircle(tft.width()/2, tft.height()/2, 30, TFT_MAGENTA);
        tft.drawCircle(tft.width()/2, tft.height()/2, 30, TFT_YELLOW);
        digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
      }
    }
      
    vTaskDelay(10); //Prevent Task watchdog got triggered
  }
}

/////////////////////////////////////////////////////////////////
// Callback when data is sent
void L1_TxCallback(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
