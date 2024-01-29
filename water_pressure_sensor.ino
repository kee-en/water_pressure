#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);  // Adjust the parameters based on your display
const float Offset = 0.480;
int psensor = A0;
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
float V, P;

void setup() {
  Serial.begin(9600);
  pinMode(psensor, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);

  Serial.println("/** Water pressure sensor demo **/");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Water Pressure");
  display.display();
}

void loop() {
  V = analogRead(psensor) * 5.00 / 1024;  // Sensor output voltage
  P = (V - Offset) * 250;                 // Calculate water pressure

  Serial.print("Voltage:");
  Serial.print(V, 3);
  Serial.println("V");

  Serial.print(" Pressure:");
  Serial.print(P, 1);
  Serial.println(" KPa");
  Serial.println();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Pressure: ");
  display.print(P, 1);
  display.print(" KPa");

  display.setCursor(0, 10);
  display.print("Voltage: ");
  display.print(V, 3);
  display.print("V");

  displayPressureIndicator(P);

  display.display();
  delay(100);
}

void displayPressureIndicator(float pressure) {
  if (pressure > 0 && pressure <= 10) {
    setLEDs(LOW, LOW, LOW, LOW, LOW);
  } else if (pressure > 10 && pressure <= 20) {
    setLEDs(HIGH, LOW, LOW, LOW, LOW);
  } else if (pressure > 20 && pressure <= 40) {
    setLEDs(HIGH, HIGH, LOW, LOW, LOW);
  } else if (pressure > 40 && pressure <= 60) {
    setLEDs(HIGH, HIGH, HIGH, LOW, LOW);
  } else if (pressure > 60 && pressure <= 80) {
    setLEDs(HIGH, HIGH, HIGH, HIGH, LOW);
  } else if (pressure >= 95) {
    setLEDs(HIGH, HIGH, HIGH, HIGH, HIGH);
  }
}

void setLEDs(int led1State, int led2State, int led3State, int led4State, int led5State) {
  digitalWrite(led1, led1State);
  digitalWrite(led2, led2State);
  digitalWrite(led3, led3State);
  digitalWrite(led4, led4State);
  digitalWrite(led5, led5State);
}
