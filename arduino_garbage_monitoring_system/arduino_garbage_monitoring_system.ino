void setup(){
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  while(Serial.available() == 0);

  String garb = Serial.readString();
  
  if(garb == "full"){
    digitalWrite(10, HIGH);
    Serial.println("Signal Full Sent...!!");
  }
  else if(garb == "empty"){
    digitalWrite(10, LOW); 
    Serial.println("Signal Empty Sent...!!");
  }
  else{
    Serial.println("INVALID COMMAND");
  }
  
}

