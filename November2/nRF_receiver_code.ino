// Receiver
  const int LED1PIN = 2;
  const int LED2PIN = 4;
  const int CEPIN = 9;
  const int CSNPIN = 10;
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
  const byte address[6] = "00001";
  
  void setup() {
  Serial.begin(9600);
  pinMode(LED1PIN, OUTPUT);
  pinMode(LED2PIN, OUTPUT);
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
  uint8_t pipeNum;
  if (radio.available(&pipeNum))  //Looking for the data.
  {
    int data;
    Serial.print("data available on pipe ");
    Serial.println(pipeNum);
    radio.read(&data, sizeof(data));  //Reading the data
    Serial.print("data = ");
    Serial.println( data);
    switch (data) {
      case B00000000:
        digitalWrite(LED1PIN, LOW);
        digitalWrite(LED2PIN, LOW);
        break;
      case B00000001:
        digitalWrite(LED1PIN, HIGH);
        break;
      case B00000010:
        digitalWrite(LED2PIN, HIGH);
        break;
      case B00000011:
        digitalWrite(LED1PIN, HIGH);
        digitalWrite(LED2PIN, HIGH);
        break;
    }
    delay(5);
  }
  }
