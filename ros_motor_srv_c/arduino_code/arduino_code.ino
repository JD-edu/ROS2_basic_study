int motorPin1 = 5;  // IN1
int motorPin2 = 6;  // IN2

String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(115200);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
    if (Serial.available()) {
      String cmd = Serial.readStringUntil('\n'); 
      cmd.trim();  
      handleCommand(cmd);
    }
    
}

void handleCommand(String cmd) {
  int speed = 0;

  if (cmd.startsWith("a") && cmd.endsWith("b")) {
    // CW
    speed = cmd.substring(1, cmd.length() - 1).toInt();
    Serial.println("cw");
    runMotor(true, speed);
  } else if (cmd.startsWith("c") && cmd.endsWith("d")) {
    // CCW
    speed = cmd.substring(1, cmd.length() - 1).toInt();
    runMotor(false, speed);
    Serial.println("ccw");
  } else if (cmd.startsWith("e") && cmd.endsWith("f")) {
    // CCW
    speed = cmd.substring(1, cmd.length() - 1).toInt();
    Serial.println("stop");
    stopMotor();
  }
}

void runMotor(bool cw, int speed) {
  speed = constrain(speed, 0, 255);
  if (cw) {
    digitalWrite(13, HIGH);
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  } else {
    digitalWrite(13, LOW);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  }
}

void stopMotor(){
  digitalWrite(13, LOW);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
