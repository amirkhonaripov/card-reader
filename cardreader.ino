// Connecting libraries
#include <SPI.h> 
#include <MFRC522.h> 
#include <Servo.h> 
// Defining the pins
#define SS_PIN 10
#define RST_PIN 9 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance. 
int buttonState;  
int buttonPin = 2;  

void setup()  
{ 
  Serial.begin(9600);   // Initiate a serial communication 
  SPI.begin();      // Initiate  SPI bus 
  mfrc522.PCD_Init();   // Initiate MFRC522 
  Serial.println("Approximate your card to the reader..."); 
  Serial.println(); 
  pinMode(buttonPin, INPUT); 
} 
void loop()  
{ 
    buttonState = digitalRead(buttonPin); 
    if (buttonState == HIGH) { 
    Serial.println("close"); 
    delay(1000); 
  } 
  else{ 
  // Look for new cards 
  if ( ! mfrc522.PICC_IsNewCardPresent())  
  { 
    return; 
  } 
  // Select one of the cards 
  if ( ! mfrc522.PICC_ReadCardSerial())  
  { 
    return; 
  } 
  //Show UID on serial monitor 
  Serial.print("UID tag :"); 
  String content= ""; 
  byte letter; 
  for (byte i = 0; i < mfrc522.uid.size; i++)  
  { 
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "); 
     Serial.print(mfrc522.uid.uidByte[i], HEX); 
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ")); 
     content.concat(String(mfrc522.uid.uidByte[i], HEX)); 
  } 
  Serial.println(); 
  Serial.print("Message : "); 
  content.toUpperCase(); 
   
  if (content.substring(1) == "93 3E 48 2E") //change here the UID of the card/cards that you want to give access 
  { 
    Serial.println("93 3E 48 2E accessed successfully!"); 
    Serial.println();  
  } 
  else if(content.substring(1) == "35 1C 7E 2D") 
  { 
    Serial.println("35 1C 7E 2D accessed successfully!"); 
    Serial.println();  
  }
  else if(content.substring(1) == "05 9C 92 2D") 
  { 
    Serial.println("05 9C 92 2D accessed successfully!"); 
    Serial.println();  
  }  
  else if(content.substring(1) == "94 58 4A 73") 
  { 
    Serial.println("94 58 4A 73 accessed successfully!"); 
    Serial.println();  
  }  
 else   { 
    Serial.println(" Access denied"); 

  } 
  } 
}
