/*
Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST -> GPIO 22(ESP32)
   SPI SS      SDA(SS)      10            53        D10        10               10  -> GPIO 21(ESP32)
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16  -> GPIO 23(ESP32)
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14  -> GPIO 19(ESP32)
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15  -> GPIO 18(ESP32)
*/

//RFID pins definitions:
#define RST 22
#define SDA 21
#define MOSI 23
#define MISO 19
#define SCK 18

//Position in memory that save how many cards are recorded in flash memory 
#define slotMemory_nCards 0

//
#define initialGapMemory 1

//Last position memory in EEPROM of master card registration 
#define lastSlotMaster 4



//Verify If masterCard Exists
bool masterExists();