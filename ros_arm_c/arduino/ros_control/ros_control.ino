/*MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.*/

#include <Servo.h>

// 1. 서보 객체 선언 (관절 이름)
Servo base;      // 3번 핀
Servo shoulder;  // 5번 핀
Servo upperarm;  // 6번 핀
Servo lowerarm;  // 9번 핀

String inputString = "";         
bool stringComplete = false;     

void setup() {
  Serial.begin(115200);
  
  // readStringUntil의 반응 속도를 높이기 위해 타임아웃을 10ms로 설정
  Serial.setTimeout(10); 
  
  inputString.reserve(50); 

  // 2. 서보 핀 연결
  base.attach(3);
  shoulder.attach(5);
  upperarm.attach(6);
  lowerarm.attach(9);

  // 3. 초기 위치 설정
  base.write(90);
  shoulder.write(90);
  upperarm.write(90);
  lowerarm.write(90);

  Serial.println("Robot Arm Ready. Format: a90b90c90d90e");
}

void loop() {
  // 시리얼 버퍼에 데이터가 있을 때만 읽기 실행
  if (Serial.available() > 0) {
    // 'e' 문자가 올 때까지 읽어옴
    inputString = Serial.readStringUntil('e');
    
    // readStringUntil은 'e'를 제외하고 반환하므로, 
    // 기존 파싱 로직(indexOf('e'))을 유지하기 위해 'e'를 다시 붙여줌
    inputString += 'e';
    stringComplete = true;
  }

  if (stringComplete) {
    parseAndMove(inputString);
    
    inputString = "";
    stringComplete = false;
  }
}

void parseAndMove(String command) {
  // 수신 데이터 예시: "a90b45c120d10e"
  
  int aPos = command.indexOf('a');
  int bPos = command.indexOf('b');
  int cPos = command.indexOf('c');
  int dPos = command.indexOf('d');
  int ePos = command.indexOf('e');

  // 각 관절별 데이터 추출 및 이동
  // base (a ~ b 사이 값)
  if (aPos != -1 && bPos != -1) {
    int valBase = command.substring(aPos + 1, bPos).toInt();
    base.write(constrain(valBase, 0, 180));
  }
  
  // shoulder (b ~ c 사이 값)
  if (bPos != -1 && cPos != -1) {
    int valShoulder = command.substring(bPos + 1, cPos).toInt();
    shoulder.write(constrain(valShoulder, 0, 180));
  }
  
  // upperarm (c ~ d 사이 값)
  if (cPos != -1 && dPos != -1) {
    int valUpper = command.substring(cPos + 1, dPos).toInt();
    upperarm.write(constrain(valUpper, 0, 180));
  }
  
  // lowerarm (d ~ e 사이 값)
  if (dPos != -1 && ePos != -1) {
    int valLower = command.substring(dPos + 1, ePos).toInt();
    lowerarm.write(constrain(valLower, 0, 180));
  }

  // 피드백 출력
  Serial.print("Applied Command: ");
  Serial.println(command);
}