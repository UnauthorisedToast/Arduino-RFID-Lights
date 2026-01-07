#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8
#define LED_PIN A0
#define lol_PIN A1

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(LED_PIN,OUTPUT);
 
   pinMode(lol_PIN, OUTPUT);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;


  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("Tap card key: ");
  Serial.println(strID);

  if (strID.indexOf("2A:D1:4E:19") >=0) {
    digitalWrite(LED_PIN, HIGH);
    delay(10000);
    digitalWrite(LED_PIN, LOW);
  } else {
    

  }
  
  if (strID.indexOf("D6:50:E2:F7") >=0) {
    digitalWrite(lol_PIN, HIGH);
    delay(1000);
    digitalWrite(lol_PIN, LOW);
  } 
  
  else {


    
  }
  

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
