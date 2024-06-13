#define USE_WIFI_NINA         false
#define USE_WIFI101           true
#include <WiFiWebServer.h>
#include <WiFi101.h>


const char ssid[] = "LEVINE 7388";
const char pass[] = "40Jt798?";
const int groupNumber = 8; // Set your group number to make the IP address constant - only do this on the EEERover network
const int motor1DirPin = 6;
const int motor1PwmPin = A1;
const int motor2DirPin = 4;
const int motor2PwmPin = A2;


WiFiWebServer server(80);


String currentState = "OFF";


//Return the web page
void handleRoot()
{
  server.send(200, F("text/html"), "Arduino");
}


void turnLeft() {
    Serial.println("TURNING LEFT");
    digitalWrite(motor1DirPin, HIGH);
    analogWrite(motor1PwmPin, 128);
    digitalWrite(motor2DirPin, LOW);
    analogWrite(motor2PwmPin, 128);
    currentState = "LEFT";
    server.send(200, F("text/plain"), currentState);
}


void turnRight() {
  Serial.println("TURNING RIGHT");
    digitalWrite(motor1DirPin, LOW);
    analogWrite(motor1PwmPin, 128);
    digitalWrite(motor2DirPin, HIGH);
    analogWrite(motor2PwmPin, 128);
    currentState = "RIGHT";
    server.send(200, F("text/plain"), currentState);
}


void moveBackward() {
    digitalWrite(motor1DirPin, HIGH);
    analogWrite(motor1PwmPin, 255);
    digitalWrite(motor2DirPin, HIGH);
    analogWrite(motor2PwmPin, 255);
    server.send(200, F("text/plain"), F("BACK"));
}


void moveForward() {
    digitalWrite(motor1DirPin, LOW);
    analogWrite(motor1PwmPin, 255);
    digitalWrite(motor2DirPin, LOW);
    analogWrite(motor2PwmPin, 255);
    server.send(200, F("text/plain"), F("FORW"));
}


void stop() {
    analogWrite(motor1PwmPin, 0);
    analogWrite(motor2PwmPin, 0);
    server.send(200, F("text/plain"), F("OFF"));
}


//Generate a 404 response with details of the failed request
void handleNotFound()
{
  String message = F("File Not Found\n\n");
  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, F("text/plain"), message);
}


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);


  pinMode(motor1DirPin, OUTPUT);
  pinMode(motor1PwmPin, OUTPUT);
  pinMode(motor2DirPin, OUTPUT);
  pinMode(motor2PwmPin, OUTPUT);


  Serial.begin(9600);


  //Wait 10s for the serial connection before proceeding
  //This ensures you can see messages from startup() on the monitor
  //Remove this for faster startup when the USB host isn't attached
  while (!Serial && millis() < 10000);  


  Serial.println(F("\nStarting Web Server"));


  //Check WiFi shield is present
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    while (true);
  }


  //Configure the static IP address if group number is set
  if (groupNumber)
  WiFi.config(IPAddress(146,169,158,87));
 
  // attempt to connect to WiFi network
  Serial.print(F("Connecting to WPA SSID: "));
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }


  Serial.println("Connected to WiFi");


  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address:");
  Serial.println(ip);


  //Register the callbacks to respond to HTTP requests
  server.on(F("/"), handleRoot);
  server.on(F("/forw"), moveForward);
  server.on(F("/back"), moveBackward);
  server.on(F("/stop"), stop);
  server.on(F("/right"), turnRight);
  server.on(F("/left"), turnLeft);


  server.onNotFound(handleNotFound);
 
  server.begin();
 
  Serial.print(F("HTTP server started @ "));
  Serial.println(static_cast<IPAddress>(WiFi.localIP()));
}


//Call the server polling function in the main loop
void loop()
{
  server.handleClient();
}
