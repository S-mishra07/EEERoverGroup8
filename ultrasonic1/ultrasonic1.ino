int ultrasensorPin = A5;
int bit;
int code[8];
int decimal_code;
char letter; 
int start_bit;
int end_bit;
bool start = false;
char Name[8] ;
char List[8] ;
char so_far;
int start_read;
int data_read;
char bit2[1];
bool found;
char end_bits[8];
int previous = 0;

void setup() {
  
  Serial.begin (9600);
  pinMode (ultrasensorPin, INPUT);
  Serial.println ("Hi");
}

void loop() {
  Serial.println ("Hi");
  int current = analogRead (ultrasensorPin);
  while (!((current> 410 && previous <= 410) || (current < 410 && previous >= 410))){
      delay (0.0166666666666667);
      previous = current;
      current = analogRead (ultrasensorPin);
  }
  delay (0.833333333333);
  start = false;

  int i = 0;
  while (start == false){
    data_read = analogRead (ultrasensorPin);
    delay (1.66666667);
    if (data_read > 410 || data_read == 410){
      bit2[0] = '1';
    }
    else{
      bit2[0] = '0';
    }
    
    List[i] = bit;
    i++;
    if (sizeof (List) > 8 || sizeof (List) == 8){
      for (int l =0; l<8;l++){
        
        end_bits[l] = List[sizeof(List)-l-1];
      }
    }
    if (strcmp(end_bits, "00100011") == 0){
      start = true;
    }
    delay (1.66666667); // reads end bit

  }

  int j = 0;  
  while (Name != "Abronia" && Name != "Elgaria" && Name != "Dixonius" && Name != "Cophotis" ){
      delay (1.66666667); // reads start bit
      for (int i = 0; i<8; i++){ 
        data_read = analogRead(ultrasensorPin);
        if (data_read > 410 || data_read == 410){
          bit = 1;
        }
        else{
          bit = 0;
        }
        delay (1.66666667);
        code[i]= bit;
      }
      delay (1.66666667) ;// reads end bit
      int decimal_code = binary_to_decimal(code);
      letter = decimal_code;

      Name[j]= letter;
      j++;
  }

  Serial.println (Name);  
  for (int s = 0; s< sizeof(Name); s++ ){
      Name[s] = 0;
    }
}


int binary_to_decimal(int code[8]){
  int decimal = 0;
  for (int j = 0; j<8; j++){
    decimal = decimal + code[j]*2^j;
  }
  return decimal;
}