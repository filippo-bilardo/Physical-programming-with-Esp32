/** ****************************************************************************************
 * @file MyBtn
 *
 * @brief Test pulsanti
 * 
 * https://github.com/filippo-bilardo/TPSIT_2/blob/main/008/pulsanti.c 
 *  
 * @author Filippo Bilardo
 * @version 1.0  30/04/22  Versione iniziale
 */
#define BTN_SX_PIN    0
#define BTN_DX_PIN    35
#define BTN_UP_PIN    35
#define BTN_DW_PIN    0
#define BTN_PRESSED   0     //Collegamento Pullup
#define BTN_RELEASED  1
#define BTN_DB_TIME   20    //Debounce time
#define BTN_LP_TIME   2000  //Long press time
#define BTN_EV_TIME   100   //Intervallo rilievo tra eventi

//TODO creare enum
#define BTN_PRESS_NONE  0
#define BTN_PRESS_BOTH  1
#define BTN_PRESS_SX    2
#define BTN_PRESS_DX    3
#define BTN_CLICK_NONE  0
#define BTN_CLICK_SX    1
#define BTN_CLICK_DX    2

void btnInit();
void btnLoop();
int checkPressButtons();
int btnUpIsClickedBlocking();

int btnDwIsPressedRaw();
int btnDwIsPressed();
int btnDwIsLongPressed();
int btnDwIsClicked();
int btnUpIsPressedRaw();
int btnUpIsPressed();
int btnUpIsLongPressed();
int btnUpIsClicked();

//void btnUpReleased;
//void btnUpChanged;
//void btnUpLongClickDetected;
//void btnUpLongClick;
//void btnUpDoubleClick;
//void btnUpTripleClick;
//void btnUpTap;
