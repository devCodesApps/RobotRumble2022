
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "robot";    //pick a unique address, any 5-char string
int radioData[4];
int VRx = A0;
int VRy = A1;
int mapX = 0;
int mapY = 0;

int xPosition = 0;
int yPosition = 0;
void setup() {

  //packet to send
  radioData[0] = 0;
  radioData[1] = 1;
  radioData[2] = 2;
  radioData[3] = 3;
  radioData[4] = 4;

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setRetries(15, 15);  //(time, tries)  time is number of 250uS intervals
  radio.setPALevel(RF24_PA_MIN);   //if modules are very close, use RF24_PA_MIN
  radio.stopListening();           //sets module in TRANSMISSION mode
}
void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);

  mapX = map(xPosition, 0, 1023, -10, 10);
  mapY = map(yPosition, 0, 1023, -10, 10);


  if ( mapY > 3) {
    radioData[0] = 0; //0-fwd

  }
  else if (mapY < -3) {
    radioData[0] = 1;

  }
  else if (mapX > 3) {
    radioData[0] = 2;


  }
  else if (mapX < -3) {
    radioData[0] = 3;

  }
  else {
    radioData[0] = 4;

  }

  boolean radioACK_OK = radio.write(radioData, sizeof(radioData[1]));

  if (radioACK_OK != true)
  {
    Serial.println("Radio Message not received...");
  }
  else
  {
    Serial.println("Acknowledgement Received");
  }

}
