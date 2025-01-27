#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* password = "password";

int ENA = D1; 
int ENB = D2;
int IN1 = D3;
int IN2 = D4;
int IN3 = D5;
int IN4 = D6;
int dutyCycleLeft = 128;
int dutyCycleRight = 128;
char input;

WiFiServer server(80);

void setup(){
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop(){
  WiFiClient client = server.available();
  
  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);

    int dutyA = getDutyCycle(request, "dutyA");
    int dutyB = getDutyCycle(request, "dutyB");

    if (request.indexOf("/STOP") >= 0) {
      stop(0,0);
    }else if (request.indexOf("/W") >= 0) {
    forward(dutyA, dutyB);
    } else if (request.indexOf("/A") >= 0) {
      left(dutyA, dutyB);
    } else if (request.indexOf("/S") >= 0) {
      backward(dutyA, dutyB);
    } else if (request.indexOf("/D") >= 0) {
      right(dutyA, dutyB);
    }
  }
}

void forward(int dutyA, int dutyB){
  analogWrite(ENA,dutyA);
  analogWrite(ENB,dutyB);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void backward(int dutyA, int dutyB){
  analogWrite(ENA,dutyA);
  analogWrite(ENB,dutyB);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void left(int dutyA, int dutyB){
  analogWrite(ENA,dutyA);
  analogWrite(ENB,dutyB);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void right(int dutyA, int dutyB){
  analogWrite(ENA,dutyA);
  analogWrite(ENB,dutyB);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void stop(int dutyA, int dutyB){
  analogWrite(ENA,dutyA);
  analogWrite(ENB,dutyB);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

int getDutyCycle(String request, String param) {
  int index = request.indexOf(param + "=");
  if (index >= 0) {
    int valueStart = index + param.length() + 1;
    int valueEnd = request.indexOf('&', valueStart);
    if (valueEnd == -1) valueEnd = request.indexOf(' ', valueStart);
    return request.substring(valueStart, valueEnd).toInt();
  }
  return 255; // Default to full speed
}