const int ledPin = 13; 
char receivedChar; 
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    if (receivedChar == 'a') {
      digitalWrite(ledPin, HIGH);
    }
    else if (receivedChar == 'b') {
      digitalWrite(ledPin, LOW);
    }
    else {
      //Serial.print("Received unknown command: ");
    }
  }
}
