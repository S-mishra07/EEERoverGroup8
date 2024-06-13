#include <Servo.h>

Servo myservo1; // create servo object to control the first servo
Servo myservo2; // create servo object to control the second servo

int pos1 = 75;  // initial position of the first servo
int pos2 = 75;  // initial position of the second servo

void setup() {
  myservo1.attach(9); // attaches the first servo to pin 9
  myservo2.attach(10); // attaches the second servo to pin 10
}

void loop() {
  // Sweep both servos simultaneously
  for (int i = 75; i <= 115; i++) { // sweep from 75 to 115 degrees
    myservo1.write(i); // set position of the first servo
    myservo2.write(i+30); // set position of the second servo
    delay(15); // delay for smoother movement
  }
  for (int i = 115; i >= 75; i--) { // sweep from 115 to 75 degrees
    myservo1.write(i); // set position of the first servo
    myservo2.write(i+30); // set position of the second servo
    delay(15); // delay for smoother movement
  }
}

