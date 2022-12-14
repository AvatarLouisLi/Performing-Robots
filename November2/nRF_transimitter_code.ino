// Transmitter
const int SWITCH1PIN = 2;
const int SWITCH2PIN = 4;
const int CEPIN = 9;
const int CSNPIN = 10;
int pot_pin = 0;

// In summary,
// nRF 24L01 pin    Arduino pin   name
//          1                     GND
//          2                     3.3V
//          3             9       CE
//          4             10      CSN
//          5             13      SCLK
//          6             11      MOSI/COPI
//          7             12      MISO/CIPO

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(CEPIN, CSNPIN);                
const byte address[6] = "200";

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH1PIN, INPUT);
  pinMode(SWITCH2PIN, INPUT);
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1);
  } else {
    Serial.println("radio successfully initialized");
  }
  radio.openWritingPipe(address);  
  radio.setPALevel(RF24_PA_MIN);   
  radio.stopListening();           
}

void loop() {
  int left = B00000000;
  if (digitalRead(SWITCH1PIN) == HIGH) {
    left = B00000001;
  }
  int right = B00000000;
  if (digitalRead(SWITCH2PIN) == HIGH) {
    right = B00000010;
  }

  int pot = 0;
  int val = 0;
  if((val = analogRead(pot_pin))){
    pot = val;
    pot *= 10;
  }


  int data = left | right;

  int totalVal = data + pot;
  if (data) {
    Serial.print( "sending data = " );
    Serial.println(data);
    radio.write(&data, sizeof(data)) ;
  }
  else if(pot){
    Serial.print( "sending pot data = " );
    Serial.println(pot);
    radio.write(&pot, sizeof(pot));
  }
}
