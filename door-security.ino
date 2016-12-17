
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9
#define SS_PIN   10
#define lockpin  2
#define relay 1
#define bb 3
#define bc 4
#define ba 5


byte approvedA[] {21,161,95,81};
byte approvedB[] {196,32,58,213};

MFRC522 mfrc522(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;

//initialize//
void setup(){
   Serial.begin(9600);   
   while (!Serial);      
   SPI.begin();          
   mfrc522.PCD_Init();
   
   pinMode(lockpin, OUTPUT);
   
    
  
   for(byte i=0; i<6; i++){
       key.keyByte[i] = 0xFF;}
}
byte cardUid[4];

void getUid(){
          
        
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            cardUid[i] = mfrc522.uid.uidByte[i];
            Serial.println(mfrc522.uid.uidByte[i]);
          }
         return;
        }



int compareUid() {
   if (cardUid[0] == approvedA[0]) 
     {if(cardUid[1] == approvedA[1])
       {if (cardUid[2] == approvedA[2])
         {if (cardUid[3] == approvedA[3])
           {return 0;}}}}
   if (cardUid[0] == approvedB[0]) 
     {if(cardUid[1] == approvedB[1])
       {if (cardUid[2] == approvedB[2])
         {if (cardUid[3] == approvedB[3])
           {return 1;}}}}
      if (cardUid[0] != approvedA[0] && approvedB[0])
     {if(cardUid[1] != approvedA[1] && approvedB[1] )
       {if (cardUid[2] != approvedA[2] && approvedB[2])
         {if (cardUid[3] != approvedA[3] && approvedB[3])
           {return 9;}}}}
   return 3;
   } 

void loop(){
   
 
   if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
            delay(50);
            return;}
      getUid();
   
   switch(compareUid()) {
    case 1 : 
    digitalWrite(bc, HIGH);
    digitalWrite(bb, LOW);
    digitalWrite(ba, LOW);
    digitalWrite(relay,HIGH);
    Serial.println("Access Granted to User1!");
    break;
    case 0 : 
    digitalWrite(bb, HIGH);
    digitalWrite(bc, LOW);
    digitalWrite(ba, LOW);
    digitalWrite(relay,HIGH);
    Serial.println("Access Granted to User2!");
   
    break; 
    case 9 :
    Serial.println("Invalid user!");
    digitalWrite(bc, LOW);
    digitalWrite(bb, LOW);
    for (int i=0;i<5;i++){
     digitalWrite(ba, HIGH);   
    delay(1000);                       
    digitalWrite(ba, LOW);    
    delay(1000); 
    }
    case 3 :
    break;          
   }
   
   delay(2000);
   }
