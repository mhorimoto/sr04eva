#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET   -1  // OLED RESET pin sharing Arduino reset
#define SCREEN_ADDRESS 0x3C

#define TRIG  2
#define ECHO  3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long d1 = 0;
unsigned long d2 = 0;
unsigned long duration;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25; // 25℃の気温の想定

void setup() {
  Serial.begin( 9600 );

  pinMode(ECHO, INPUT );
  pinMode(TRIG, OUTPUT );
  digitalWrite(TRIG,LOW);
  digitalWrite(ECHO,LOW);
  pinMode(13,OUTPUT);
  Serial.println("OK V201");
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Distance V200");
  display.println("");
  display.setTextSize(3);
  display.println("450.00");
  display.setTextSize(2);
  display.println("       cm");
  display.display();
  delay(2000);
  
}

void loop() {
    digitalWrite(13,HIGH);
    digitalWrite(TRIG, LOW);
    delayMicroseconds( 1 ); 
    digitalWrite( TRIG, HIGH );
    delayMicroseconds( 11 );
    digitalWrite( TRIG, LOW );
    duration = pulseInLong( ECHO, HIGH ); // 往復にかかった時間が返却される[マイクロ秒]
    digitalWrite(13,LOW);
    if (duration > 0) {
      duration = duration / 2; // 往路にかかった時間
      distance = duration * speed_of_sound * 100 / 1000000;
      Serial.print("Distance:");
      Serial.print(distance);
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0,0);
      display.println("Distance V200");
      display.println("");
      display.setTextSize(3);
      display.println(distance);
      display.setTextSize(2);
      display.println("       cm");
      display.display();
      delay(500);
    } else {
      display.setCursor(0,24);
      display.setTextSize(2);
      display.print("0");
      display.display();
    }
    delay(500);
}
