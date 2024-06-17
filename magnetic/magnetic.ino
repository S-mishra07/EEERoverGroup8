// Define the analog pin
const int analogPin = A0;


// Constants for voltage thresholds assuming a 5V reference and a 10-bit ADC (0-1023)
const float highThreshold = 0.20; // 0.5V threshold for negative polarity


void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}


void loop() {
  // Read the input on analog pin A0 (value between 0 and 1023)
  int sensorValue = analogRead(analogPin);
 
  // Calculate the voltage from the sensor value
  // 5.0 is the reference voltage for the ADC
  float voltage = sensorValue * (3.3 / 1023.0);
 
  // Determine the polarity based on the voltage thresholds
  if (voltage > highThreshold) {
    Serial.println("DOWN");
  } else {
    Serial.println("UP");
  }
  // Add a small delay to avoid flooding the serial monitor
  delay(500);
}
