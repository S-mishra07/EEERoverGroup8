const int inputPin = A0; // Define the input pin for analog input
const float threshold = 0.1; // 30mV threshold
const int analogThreshold = threshold * 1023 / 5.0; // Convert to analog reading threshold

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(inputPin, INPUT); // Set the input pin as input
}

void loop() {
    Serial.println("hello");
  unsigned long startTime = 0;
  unsigned long pulseWidth = 0;
  bool pulseDetected = false;

  // Wait for the signal to go above the threshold
  while (analogRead(inputPin) < analogThreshold) {
    // Do nothing, just wait
  }

  // Start timing the pulse
  startTime = micros();

  // Wait for the signal to go below the threshold
  while (analogRead(inputPin) > analogThreshold) {
    // Do nothing, just wait
  }

  // Calculate pulse width
  pulseWidth = micros() - startTime;
  float frequency = 1000000.0 / pulseWidth;

  // Check if a valid pulse was detected
  if ((frequency/1.9)<250) { // Convert pulse width to frequency in Hz
    Serial.print("Frequency: ");
    Serial.print(frequency/1.9);
    Serial.println(" Hz");
  } else {
    float frequency = 1000000.0 / pulseWidth;
    Serial.println("No pulse detected.");

  }
  delay(1000); // Delay before taking the next measurement
}
