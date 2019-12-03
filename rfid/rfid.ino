/*Student Bus RFID Tracking System
  Date Created: 04/07/2017
  Date Modified: 19/03/2018
  Author: ARVI
*/

#include <ESP8266WiFi.h>

#include "MySQL_Connection.h"
#include "MySQL_Cursor.h"

// Declaring MySQL Server Variables
IPAddress server_addr(192, 168, 43, 196); //Server IP Address
char user[] = "nik";
char password[] = "password";

// WiFi Connection Parameters
char ssid[] = "nitesh";
char pass[] = "12345678";

WiFiClient client;
MySQL_Connection conn((Client *)&client);

// Additional Variables
int count = 0;
char input[12];
boolean flag = 0;

// Main Query
char INSERT_SQL[] = "INSERT INTO test.student_info (name, rollno, rfid) VALUES ('%s', '%s', '%s')";
char query[128];
String s_id1 = "3E00674FBAAC";
String s_id2 = "student2";
String s_id3 = "student3";
String s_id4 = "student4";
String s_id5 = "student5";

String inputStr;

void setup()
{
  Serial.begin(9600);

  // Connecting to WiFi
  WiFi.begin(ssid, pass);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay (500);
    Serial.print (".");
  }
  Serial.println ("");
  Serial.print ("Connected to ");
  Serial.println (ssid);
  Serial.print ("IP address: ");
  Serial.println (WiFi.localIP());

  // Connecting to the Database
  Serial.println("DB - Connecting...");
  if (conn.connect(server_addr, 3306, user, password) == true) {
    delay(500);
  } else {
    Serial.println("Error Connecting to the database");
    ESP.restart();
  }
}

void loop() {

  if (Serial.available()) {
    count = 0;

    while (Serial.available() && count < 12) {
      input[count] = Serial.read();
      inputStr += input[count];
      count++;
      delay(5);
    }

    Serial.print(input);

    //Verifying the RF Card
    if ((input[0] ^ input[2] ^ input[4] ^ input[6] ^ input[8] == input[10]) &&
        (input[1] ^ input[3] ^ input[5] ^ input[7] ^ input[9] == input[11])) {
      Serial.print("Card Enterted: ");
      Serial.println(inputStr);
    }
    else {
      Serial.println("Error, Invalid card");
    }

    enterDataIntoDB(inputStr);
  }
}

void enterDataIntoDB(String input) {
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

  if (input == s_id1) {
    Serial.println("Entered, Database Updated");
    sprintf(query, INSERT_SQL, "Chetan Singh", "48", "one");
    cur_mem->execute(query);
    inputStr = "";
  } else if (input == s_id2) {
    Serial.println("Entered, Database Updated");
    sprintf(query, INSERT_SQL, "Student 2", "49", "two");
    cur_mem->execute(query);
    inputStr = "";
  } else if (input == s_id3) {
    Serial.println("Entered, Database Updated");
    sprintf(query, INSERT_SQL, "Student 3", "50", "three");
    cur_mem->execute(query);
    inputStr = "";
  } else if (input == s_id4) {
    Serial.println("Entered, Database Updated");
    sprintf(query, INSERT_SQL, "Student 4", "51", "four");
    cur_mem->execute(query);
    inputStr = "";
  } else if (input == s_id5) {
    Serial.println("Entered, Database Updated");
    sprintf(query, INSERT_SQL, "Student 5", "52", "five");
    cur_mem->execute(query);
    inputStr = "";
  }
  delete cur_mem;
}
