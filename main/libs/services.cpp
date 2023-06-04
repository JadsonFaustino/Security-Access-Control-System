#include "RFID.h"
#include "sounds.h"
#include "DY50.h"

// bool masterMode = false;  // initialize programming mode to false
bool successRead = false;    // Variable integer to keep if we have Successful Read from Reader

byte readCard[4];   // Stores scanned ID read from RFID Module
byte masterCard[4];   // Stores master card's ID read from EEPROM



void setPinInStateForTime(int timeInSeconds, int pin, int state) {
  digitalWrite(pin, state); // Define o pino como HIGH
  delay(timeInSeconds * 1000); // Converte o tempo em segundos para milissegundos
  digitalWrite(pin, !state); // Define o pino como LOW
}

void executeAfterTimeInState(void (*functionToExecute)(), unsigned long time, int pin, int state){
  unsigned long startTime = millis();
  
  while (digitalRead(pin) == state){
    if (millis() - startTime >= (time * 1000)){
      functionToExecute(); // Execute the specified function after x seconds
      break;
    }
  }
}

void deleteMasterCard(){
  Serial.println("Wipe Button pressed. In 10 seconds the master card will be erased!");
  soundCardRemoved();
  Serial.println("Cleaning Master Card...");
  clearMaster(); // After clear master the system is reloaded.
}

void deleteAllCards(){
  Serial.println("Wipe Button pressed. In 10 seconds all cards will be erased!");
  clearCards();
  soundAllCardsRemoved();
  Serial.println("Cleaning All Cards...");
}

void checkMasterDefinition(){
    // Check if Master Card is not defined
    if (!masterExists()) {
        Serial.println("No Master Card defined");
        Serial.println("Scan a card to define as Master Card");
        
        do { // Trying to scan a card
            successRead = readRFID(readCard);  // sets successRead to 1 when we get read from reader otherwise 0
        }
        while (!successRead);                // Program will not go further while you not get a successful read
        
        setMaster(readCard);
        Serial.println("Master Card defined");
        soundCardDefined();
    } else {
        Serial.println("Master Card already defined");
        executeAfterTimeInState(deleteMasterCard, 10, WIPEBUTTON_PIN, HIGH);
    }

}

void tryScanAccessMethod(){
  do { // Trying to scan a card
    executeAfterTimeInState(deleteAllCards, 10, WIPEBUTTON_PIN, HIGH);
    memset(readCard, 0, sizeof(readCard));
    // sets successRead to 1 when we get read from reader otherwise 0
    // sets successRead to 1 when we get a finger
    if(readRFID(readCard) || readFinger()){
      Serial.println("LEU");
      successRead = true;
    }

  }
  while (!successRead);   //the program will not go further while you are not getting a successful read

}

void masterMode(){
  do{
    memset(readCard, 0, sizeof(readCard));
    readRFID(readCard);
    
    if ( isMaster(readCard) ) { //When in program mode check First If master card scanned again to exit program mode
      Serial.println("Master Card scanned");
      soundExitMasterMode();
      Serial.println("Exiting Program Mode");
      break;
    } 
    else {
      if ( cardExists(readCard)) { // If scanned card is known delete it
        Serial.println("I know this card, removing...");
        deleteCard(readCard);
        soundCardRemoved();
      }
      else if(false){
        Serial.println("I know this finger, removing...");
        deleteFinger(1);
        soundCardRemoved();
      }
      else if(readCard[0] != 0) {                    // If check readCard that is not null and is not known, add it!
        Serial.println("I do not know this card, adding...");
        writeNewCard(readCard);
        soundCardDefined();
      }
      else if(!searchFinger()){
        Serial.println("Dedo não encontrado!");
        storeFinger(1);
        soundCardDefined();
        break;
      }
      else{
        delay(1000);
        continue;
      }
    }
  }while (true);
  

}




















