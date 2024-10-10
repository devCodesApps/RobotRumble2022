/*
  This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
  It won't work with v1.x motor shields! Only for the v2's with built in PWM
  control

  For use with the Adafruit Motor Shield v2
  ---->  http://www.adafruit.com/products/1438
*/

#include <Adafruit_MotorShield.h>
int counter;
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  pinMode(5, INPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)

}

void Straight() {
  myMotor1->setSpeed(255);
  myMotor->setSpeed(252);
  myMotor->run(FORWARD);

  myMotor1->run(FORWARD);

  delay(600);
  //  myMotor->run(RELEASE);
  //  myMotor1->run(RELEASE);

}
void Back() {
  myMotor1->setSpeed(255);
  myMotor->setSpeed(252);
  myMotor->run(BACKWARD);

  myMotor1->run(BACKWARD);

  delay(600);
  //  myMotor->run(RELEASE);
  //  myMotor1->run(RELEASE);

}


void Left() {
  myMotor1->setSpeed(150);
  myMotor->setSpeed(155);
  myMotor->run(BACKWARD);

  myMotor1->run(FORWARD);

  delay(600);

}

void Right2() {

  myMotor->setSpeed(100);
  myMotor1->setSpeed(105);

  myMotor->run(FORWARD);
  myMotor1->run(BACKWARD);

  delay(600);

}

void Right() {

  myMotor->setSpeed(150);
  myMotor1->setSpeed(155);

  myMotor->run(FORWARD);
  myMotor1->run(BACKWARD);

  delay(1000);

}
// check sensors 2 is sensor-based movement
void CheckSensors() {

  if ((digitalRead(8) == 0) && (digitalRead(9) == 0))  {
    myMotor->run(RELEASE);
    myMotor1->run(RELEASE);
    Straight();
  }


  else if (digitalRead(9) == 0) {
    //enter what to do if sensor finds something
    Right();
    delay(100);
  }
  else if (digitalRead(8) == 0) {
    //enter what to do if sensor finds something
    Left();
    delay(100);
  }
  else {
    Right2();
    delay(10);


  }



}

// countdown code 1 blink a second
void StarterCount() {
  myMotor->run(RELEASE);
  myMotor1->run(RELEASE);
  for (counter = 0; counter < 5; ++counter) {


    tone(10, 523, 1000); // play tone 60 (C5 = 523 Hz)
    digitalWrite(7, HIGH);
    delay(500); // Wait for 500 millisecond(s)
    digitalWrite(7, LOW);
    noTone(10);
    delay(500); // Wait for 500 millisecond(s)


  }
}

// 3 different openning sequences
void seq_one() {

  delay(600);
  Left();
  delay(600);
  myMotor->run(RELEASE);
  myMotor1->run(RELEASE);
}

void seq_two() {
  Back();
  delay(600);
  Left();
  delay(600);
  myMotor->run(RELEASE);
  myMotor1->run(RELEASE);
}
void seq_three() {

  delay(600);
  Right();
  delay(600);
  myMotor->run(RELEASE);
  myMotor1->run(RELEASE);
}
void loop() {

    if (digitalRead(5) == HIGH) {
      for (counter = 0; counter < 5; ++counter) {
        StarterCount();
        // put 1 opening sequence here
  
  
        delay(1000);
        while (true) {
  
         CheckSensors();
  
        }
      }
    }
    else {
      digitalWrite(7, LOW);
      noTone(10);
      myMotor->run(RELEASE);
      myMotor1->run(RELEASE);
    }
  

  delay(10);

}
