const int signalPin = 3;  // Digital pin where the signal is connected
volatile unsigned int radiopulsecount = 0;
const unsigned long radiosampleInterval = 1000000; // Measurement interval in microseconds
unsigned long radiostartTime;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(signalPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(signalPin), radiocountPulse, RISING); // Interrupt on rising edge
  radiostartTime = micros();
}

void loop() {
  // Measurement interval
  if (micros() - radiostartTime >= radiosampleInterval) {
    noInterrupts(); // Disable interrupts while calculating radiofrequency
    float radiofrequency = (radiopulsecount / (radiosampleInterval / 1000000.0));
    interrupts(); // Re-enable interrupts

    Serial.print("Frequency: ");
    Serial.print(radiofrequency);
    Serial.println(" Hz");

    // Reset for the next interval
    radiostartTime = micros();
    radiopulsecount = 0;
  }
}

void radiocountPulse() {
  radiopulsecount++;
}