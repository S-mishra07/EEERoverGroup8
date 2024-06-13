  void setup() {
  //Initialise pin modes and serial
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  //Read both input voltages
  int VA0 = analogRead(A0);
  int VA1 = analogRead(A1);
  int VA2 = VA0 - VA1;

  //Write ADC values to serial
  Serial.print(VA0);
  Serial.write(' ');
  Serial.print(VA1);
  Serial.write(' ');
  Serial.println(VA2);

  //Pause before next calculation
  delay(100);
} 