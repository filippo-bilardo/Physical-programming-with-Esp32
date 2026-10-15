#include <Arduino.h>
#include "MyBtn.h"

/////////////////////////////////////////////////////////////////
void btnInit() {
  pinMode(BTN_SX_PIN, INPUT_PULLUP);
  pinMode(BTN_DX_PIN, INPUT_PULLUP);
}

/////////////////////////////////////////////////////////////////
int btnDwIsPressedRaw() {
  if(digitalRead(BTN_DW_PIN)==BTN_PRESSED) return 1;
  return 0;
}

int btnDwIsPressed() {
  // Controllo che il pulsante sia premuto per un tempo minimo
  if(btnDwIsPressedRaw()) {
    for(int cont=0; cont<BTN_DB_TIME; ++cont) {
      delay(1);
      if(!btnDwIsPressedRaw()) return 0;
    }
    return 1;
  } 
  return 0;  
}

int btnDwIsLongPressed() {
  // Controllo che il pulsante sia premuto per un tempo lungo
  if(btnDwIsPressedRaw()) {
    for(int cont=0; cont<BTN_LP_TIME; ++cont) {
      delay(1);
      if(!btnDwIsPressedRaw()) return 0;
    }
    return 1;
  } 
  return 0; 
}
int btnDwIsClicked() {
  static int btn_dw_is_pressed=0; //Stato precedente
  
  if(btnDwIsPressedRaw()) {
    if(!btn_dw_is_pressed) btn_dw_is_pressed=1;
    return 0;
  } else { 
    if(btn_dw_is_pressed) {
      btn_dw_is_pressed=0;
      return 1;
    } else {
      return 0; 
    }
  }
}

int btnUpIsPressedRaw() {
  if(digitalRead(BTN_UP_PIN)==BTN_PRESSED) 
    return 1;
  return 0;
}

int btnUpIsPressed() {
  // Controllo che il pulsante sia premuto per un tempo minimo
  if(btnUpIsPressedRaw()) {
    for(int cont=0; cont<BTN_DB_TIME; ++cont) {
      delay(1);
      if(!btnUpIsPressedRaw()) return 0;
    }
    return 1;
  } 
  return 0;  
}

int btnUpIsLongPressed() {
  // Controllo che il pulsante sia premuto per un tempo lungo
  if(btnUpIsPressedRaw()) {
    for(int cont=0; cont<BTN_LP_TIME; ++cont) {
      delay(1);
      if(!btnUpIsPressedRaw()) return 0;
    }
    return 1;
  } 
  return 0; 
}

int btnUpIsClicked() {
  static int btn_up_is_pressed=0; //Stato precedente
  
  if(btnUpIsPressedRaw()) {
    if(!btn_up_is_pressed) btn_up_is_pressed=1;
    return 0;
  } else { 
    if(btn_up_is_pressed) {
      btn_up_is_pressed=0;
      return 1;
    } else {
      return 0; 
    }
  }
}

int btnUpIsClickedBlocking() {
  if(btnUpIsPressedRaw()) {
    while (btnUpIsPressedRaw()) {;}
    return 1;
  } 
  return 0; 
}
/////////////////////////////////////////////////////////////////
int checkPressButtons() {
  int retValue=BTN_PRESS_NONE;
  
  if(btnDwIsPressed()) {      //Se il pulsante è premuto
    if(btnUpIsPressed()) {    //Se è premuto anche l'altro pulsante
      retValue=BTN_PRESS_BOTH;//Allora sono premuti entrambi
    } else {
      retValue=BTN_PRESS_SX;
    }
  }
  
  if(btnUpIsPressed()) {
    if(btnDwIsPressed()) {
      retValue=BTN_PRESS_BOTH;
    } else {
      retValue=BTN_PRESS_DX;
    }
  }

  if(retValue!=BTN_PRESS_NONE)
    delay(BTN_EV_TIME); //Dopo evento rallento il controllo successivo
  return retValue;
}

/////////////////////////////////////////////////////////////////
//void btnUpPressed(Button2 &btn) {
//  Serial.println("btnUp pressed");
//}
//void btnUpReleased(Button2 &btn) {
//  Serial.print("btnUp released: ");
//  Serial.println(btn.wasPressedFor());
//}
//void btnUpChanged(Button2 &btn) {
//  Serial.println("btnUp changed");
//}
//void btnUpClick(Button2 &btn) {
//  Serial.print("btnUp click");
//}
//void btnUpLongClickDetected(Button2 &btn) {
//  Serial.println("btnUp long click detected\n");
//}
//void btnUpLongClick(Button2 &btn) {
//  Serial.println("btnUp long click\n");
//}
//void btnUpDoubleClick(Button2 &btn) {
//  Serial.println("btnUp double click\n");
//}
//void btnUpTripleClick(Button2 &btn) {
//  Serial.println("btnUp triple click\n");
//}
//void btnUpTap(Button2 &btn) {
//  Serial.println("btnUp tap");
//}
