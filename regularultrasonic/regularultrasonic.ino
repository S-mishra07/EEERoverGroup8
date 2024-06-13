#define RX_PIN 1
#define BAUD_RATE 600
#define BIT_DURATION (1000000 / BAUD_RATE) // Duration of one bit in microseconds

void setup() {
  Serial.begin(9600); // Serial monitor communication
  pinMode(RX_PIN, INPUT);
}

void loop() {
  ultra();
}

void ultra() {
  static int index = 0; 
  if (index<4){
    
    static char buffer[4]; // Buffer to store received characters
    static int index = 0;  // Index to keep track of buffer position

    if (digitalRead(RX_PIN) == LOW) { // Start bit detected
      delayMicroseconds(BIT_DURATION / 2); // Wait to the middle of the start bit

      char c = 0;
      for (int i = 0; i < 8; i++) { // Read each bit
        delayMicroseconds(BIT_DURATION);
        c |= (digitalRead(RX_PIN) << i);
      }
      delayMicroseconds(BIT_DURATION); // Wait for stop bit

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
  ultra();
}

}
