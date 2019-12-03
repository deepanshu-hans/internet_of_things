#include <ESP8266WiFi.h>

const int sen1 = 12;
const int sen2 = 13;
const char* ssid = "Nik";
const char* password = "pramukhmahant86";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);

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
}

void loop() {

  String stat1, stat2;

  int sen1val = digitalRead(sen1);
  int sen2val = digitalRead(sen2);

  if (sen1val == 0 && sen2val == 0) {
    stat1 = "T1 is NORMAL";
    stat2 = ", T2 is NORMAL";
  } else if (sen1val == 0 && sen2val == 1) {
    stat1 = "T1 is NORMAL";
    stat2 = ", T2 passed THRESHOLD";
  } else if (sen1val == 1 && sen2val == 0) {
    stat1 = "T1 passed THRESHOLD";
    stat2 = ", T2 is NORMAL";
  } else if (sen1val == 1 && sen2val == 1) {
    stat1 = "T1 passed THRESHOLD";
    stat2 = ", T2 passed THRESHOLD";
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

  //Message on Browser
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nTemperature Status: ";
  s += stat1;
  s += stat2;

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
}

