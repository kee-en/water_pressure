#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//const float OffSet = 0.254;  // adjust this value
const float OffSet = 0.480;

float avgV = 0.0;

float V = 0;
float P;

void setup() {
  Serial.begin(9600);  // open serial port, set the baud rate to 9600 bps
  Serial.println("/** Water pressure sensor demo **/");
  Serial.println("/** Water pressure sensor demo **/");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}
void loop() {
  //Connect sensor to Analog 0

  V = analogRead(0) * 5.00 / 1024;  //Sensor output voltage


  P = (V - OffSet) * 250;  //Calculate water pressure

  Serial.print("Voltage:");
  Serial.print(V, 3);
  Serial.println("V");

  Serial.print(" Pressure:");
  Serial.print(P, 1);
  Serial.println(" KPa");
  Serial.println();
  display.clearDisplay();
  display.setCursor(25, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" Caliberation");
  display.setCursor(10, 20);
  display.setTextSize(2);
  display.print("P:" + String(P));
  display.print("KPa");

  display.setCursor(10, 45);
  display.setTextSize(2);
  display.print("V: ");
  display.print(V);
  display.display();
  delay(1000);
}