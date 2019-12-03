#include <ESP8266WiFi.h>

const int sen1 = 12; //pin D6
const int sen2 = 13; //pin D7
const char* ssid = "Nik";
const char* password = "pramukhmahant86";
const int motorpin1 = 16; //pin D0
const int motorpin2 = 5; //pin D1

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);
  digitalWrite(motorPin, HIGH);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
}

void loop() {

  String stat1, stat2;

  int sen1val = digitalRead(sen1);
  int sen2val = digitalRead(sen2);

  if (sen1val == 0 && sen2val == 0) {
    stat1 = "Free of Gas";
    stat2 = ", Free of Alcohol";
  } else if (sen1val == 0 && sen2val == 1) {
    stat1 = "Free of Gas";
    stat2 = ", Alcohol Detected";
  } else if (sen1val == 1 && sen2val == 0) {
    stat1 = "Gas Leakage Detected";
    stat2 = ", Free of Alcohol";
  } else if (sen1val == 1 && sen2val == 1) {
    stat1 = "Gas Leakage Detected";
    stat2 = ", Alcohol Detected";
  }

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  //Matching the request
  if (req.indexOf("/stopcar") != -1) {
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, LOW);
  } else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  client.flush();

  //Message on Browser
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nEnvironment Status: ";
  s += stat1;
  s += stat2;

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}

