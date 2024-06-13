#include <SoftwareSerial.h>

#define RX_PIN 2

SoftwareSerial uart(RX_PIN, -1); // No TX pin needed

void setup() {
  Serial.begin(9600);
  uart.begin(600);
}

void loop() {
  static char buffer[4]; // Buffer to store received characters
  static int index = 0;  // Index to keep track of buffer position
  //erial.println("Zen");
 // delay(1000);

  while (uart.available()) {
    char c = uart.read();
    
    if (c == '#') { // If character is hash, reset buffer
      index = 0;
    } else {
      buffer[index++] = c;
      if (index == 3) { // Name received completely, print it
        buffer[index] = '\0'; // Null terminate the string
        Serial.println(buffer);
        index = 0; // Reset index for the next name
        }
      }
  }
}