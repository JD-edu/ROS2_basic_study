// Virtual lidar -> Arduino -> USB serial -> ROS2 / Tkinter.
// One scan: SCAN,<scan period in milliseconds>,<360 distances in mm>\n
// Angles: 0 = forward, 90 = left, counterclockwise; no physical sensor needed.
#include <Arduino.h>
#include <math.h>

const unsigned long SCAN_PERIOD_MS = 200;
unsigned long lastScan = 0;

// Room walls at x/y = +/-3 m and a moving circular obstacle.
float readVirtualLidar(float angle, float seconds) {
  float dx = cos(angle), dy = sin(angle);
  float wallX = fabs(dx) > 0.0001f ? 3.0f / fabs(dx) : 100.0f;
  float wallY = fabs(dy) > 0.0001f ? 3.0f / fabs(dy) : 100.0f;
  float distance = min(wallX, wallY);
  float cx = 1.5f, cy = 0.8f * sin(seconds * 0.6f), radius = 0.4f;
  float projection = cx * dx + cy * dy;
  float discriminant = projection * projection - (cx * cx + cy * cy - radius * radius);
  if (discriminant >= 0.0f) {
    float hit = projection - sqrt(discriminant);
    if (hit > 0.0f) distance = min(distance, hit);
  }
  return distance;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long now = millis();
  if (now - lastScan < SCAN_PERIOD_MS) return;
  unsigned long elapsed = now - lastScan;
  lastScan = now;
  Serial.print("SCAN,");
  Serial.print(elapsed);
  for (int degree = 0; degree < 360; ++degree) {
    Serial.print(',');
    Serial.print((unsigned int)(1000.0f * readVirtualLidar(
      degree * PI / 180.0f, now / 1000.0f)));
  }
  Serial.println();
}
