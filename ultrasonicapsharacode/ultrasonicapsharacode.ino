const int ultrasensorPin = 2;
int bit;
int code[8];
char letter; 
bool start = false;
char Name[9]; // increased size to accommodate the null terminator
char List[9]; // increased size to accommodate the null terminator
int data_read;
char bit2[2]; // increased size to accommodate the null terminator
char end_bits[9]; // increased size to accommodate the null terminator
int previous = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ultrasensorPin, INPUT);
  Serial.println("Hi");
  Name[0] = '\0'; // Initialize Name to an empty string
}

void loop() {
  Serial.println("Hi");
  int current = analogRead(ultrasensorPin);
  while (!((current > 410 && previous <= 410) || (current < 410 && previous >= 410))) {
    delay(17); // approx 0.0166667 seconds
    previous = current;
    current = analogRead(ultrasensorPin);
  }
  delay(833); // approx 0.833333 seconds
  start = false;

  int i = 0;
  while (!start) {
    data_read = analogRead(ultrasensorPin);
    delay(2); // approx 1.666667 milliseconds
    if (data_read >= 410) {
      bit2[0] = '1';
    } else {
      bit2[0] = '0';
    }
    bit2[1] = '\0'; // Null terminator for string

    List[i] = bit2[0];
    i++;
    if (i >= 8) {
      for (int l = 0; l < 8; l++) {
        end_bits[l] = List[i - l - 1];
      }
      end_bits[8] = '\0'; // Null terminator for string
    }
    if (strcmp(end_bits, "00100011") == 0) {
      start = true;
    }
    delay(2); // approx 1.666667 milliseconds
  }

  int j = 0;
  while (strcmp(Name, "Zen") != 0) {
    delay(2); // approx 1.666667 milliseconds
    for (int i = 0; i < 8; i++) {
      data_read = analogRead(ultrasensorPin);
      if (data_read >= 410) {
        bit = 1;
      } else {
        bit = 0;
      }
      delay(2); // approx 1.666667 milliseconds
      code[i] = bit;
    }
    delay(2); // approx 1.666667 milliseconds
    int decimal_code = binary_to_decimal(code);
    letter = (char)decimal_code;
    Serial.println(letter);
    Name[j] = letter;
    j++;
    Name[j] = '\0'; // Null terminator for string
  }

  Serial.println(Name);
  for (int s = 0; s < sizeof(Name) / sizeof(Name[0]); s++) {
    Name[s] = 0;
  }
}

int binary_to_decimal(int code[8]) {
  int decimal = 0;
  for (int j = 0; j < 8; j++) {
    decimal = decimal + code[j] * (1 << j); // 2^j is replaced with bit shift
  }
  return  decimal;
}