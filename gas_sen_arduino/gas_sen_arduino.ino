void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sen1 = analogRead(0);
  int sen2 = analogRead(1);
  Serial.print("sen1=");
  Serial.print(sen1);
  Serial.print(", ");
  Serial.print("sen2=");
  Serial.println(sen2);

  if (sen1 < 400 && sen2 < 600) {
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  } else if (sen1 > 400 && sen2 < 600) {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  } else if (sen1 < 400 && sen2 > 600) {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  } else if (sen1 > 400 && sen2 > 600) {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
  }
  delay(300);
}

