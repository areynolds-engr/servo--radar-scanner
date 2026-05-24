#include <Servo.h>
#include <LiquidCrystal.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 3

Servo radarServo;
LiquidCrystal lcd(12, 11, 8, 7, 6, 13);

long duration;
float distance;

bool objectFound = false;
int foundAngle = 0;
float foundDistance = 0;

const int MIN_ANGLE = 20;
const int MAX_ANGLE = 160;
const int CENTER_ANGLE = 90;
const int STEP_SIZE = 2;
const int SCAN_DELAY = 80;

const float MIN_DETECT_CM = 10;
const float MAX_DETECT_CM = 100;

void setup() {

  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  radarServo.attach(SERVO_PIN);

  radarServo.write(CENTER_ANGLE);

  delay(1000);

  lcd.begin(16, 2);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Radar Scanner");

  lcd.setCursor(0,1);
  lcd.print("Starting...");

  delay(1500);

  lcd.clear();
}

void loop() {

  scanRight();

  if (!objectFound) {

    scanLeft();
  }

  if (objectFound) {

    holdUntilReset();
  }
}

void scanRight() {

  for (int angle = CENTER_ANGLE; angle <= MAX_ANGLE; angle += STEP_SIZE) {

    checkAngle(angle);

    if (objectFound) return;
  }
}

void scanLeft() {

  for (int angle = MAX_ANGLE; angle >= MIN_ANGLE; angle -= STEP_SIZE) {

    checkAngle(angle);

    if (objectFound) return;
  }

  for (int angle = MIN_ANGLE; angle <= CENTER_ANGLE; angle += STEP_SIZE) {

    checkAngle(angle);

    if (objectFound) return;
  }
}

void checkAngle(int angle) {

  radarServo.write(angle);

  delay(SCAN_DELAY);

  distance = getDistance();

  displayScanning(angle, distance);

  if (distance >= MIN_DETECT_CM && distance <= MAX_DETECT_CM) {

    foundAngle = angle;

    foundDistance = distance;

    objectFound = true;
  }
}

void holdUntilReset() {

  displayFound();

  while (true) {

    if (Serial.available() > 0) {

      char command = Serial.read();

      if (command == 'r' || command == 'R') {

        objectFound = false;

        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Resetting...");

        delay(1000);

        lcd.clear();

        radarServo.write(CENTER_ANGLE);

        delay(500);

        return;
      }
    }
  }
}

float getDistance() {

  digitalWrite(TRIG_PIN, LOW);

  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);

  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {

    return -1;
  }

  return duration * 0.0343 / 2;
}

void displayScanning(int angle, float distance) {

  lcd.setCursor(0,0);

  lcd.print("Scanning...    ");

  lcd.setCursor(0,1);

  lcd.print("A:");

  lcd.print(angle);

  lcd.print((char)223);

  lcd.print(" D:");

  if (distance < 0) {

    lcd.print("---");
  }

  else {

    lcd.print(distance,1);
  }

  lcd.print("cm   ");

  Serial.print("Scanning | Angle: ");

  Serial.print(angle);

  Serial.print(" deg | Distance: ");

  Serial.print(distance);

  Serial.println(" cm");
}

void displayFound() {

  lcd.clear();

  lcd.setCursor(0,0);

  lcd.print("OBJECT FOUND");

  lcd.setCursor(0,1);

  lcd.print("A:");

  lcd.print(foundAngle);

  lcd.print((char)223);

  lcd.print(" D:");

  lcd.print(foundDistance,1);

  lcd.print("cm");

  Serial.print("OBJECT FOUND | Angle: ");

  Serial.print(foundAngle);

  Serial.print(" deg | Distance: ");

  Serial.print(foundDistance);

  Serial.println(" cm | Type r to reset");
}
