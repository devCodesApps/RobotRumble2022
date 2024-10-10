
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_MotorShield.h>

RF24 radio(4, 6); // CE, CSN
int counter;
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(2);
const byte address[6] = "robot";
void setup() {

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }

  myMotor->run(RELEASE);
   myMotor1->run(RELEASE);
  Serial.println("Motor Shield found.");
  
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  pinMode(5, INPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9
);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("Starting to listen...");
}


void Straight() {
  myMotor1->setSpeed(255);
  myMotor->setSpeed(252);
  myMotor->run(FORWARD);

  myMotor1->run(FORWARD);

  delay(10);
  //  myMotor->run(RELEASE);
  //  myMotor1->run(RELEASE);

}
void Back() {
  myMotor1->setSpeed(255);
  myMotor->setSpeed(252);
  myMotor->run(BACKWARD);

  myMotor1->run(BACKWARD);

  delay(10);
  //  myMotor->run(RELEASE);
  //  myMotor1->run(RELEASE);

}


void Left() {
  myMotor1->setSpeed(150);
  myMotor->setSpeed(155);
  myMotor->run(BACKWARD);

  myMotor1->run(FORWARD);

  delay(10);

}

void Right() {

  myMotor->setSpeed(100);
  myMotor1->setSpeed(105);

  myMotor->run(FORWARD);
  myMotor1->run(BACKWARD);

  delay(10);

}
void readRadio()
{
  if (radio.available()) {
    int packet[4];      //sized for our anticipated msg, but can have extra room if that makes more sense
    radio.read(&packet, sizeof(packet));
    int one = packet[0];

    Serial.print("Packet Received: ");
    Serial.println(one);
    if (one == 0) {
      Straight();
    }
    else if (one == 1) {
      Back();
    }
    else if (one == 2) {
      Left();
    }
    else if (one == 3) {
      Right();
    }
    else {
      myMotor->run(RELEASE);
      myMotor1->run(RELEASE);

    }

  }
}

void loop() {
  Serial.println("listening...");
  readRadio();
  delay(30);
}
