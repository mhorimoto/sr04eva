#define TRIG  2
#define ECHO  3

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
  Serial.println("OK V116");
  delay(200);
}

void loop() {
    digitalWrite(13,HIGH);
    digitalWrite(TRIG, LOW);
    //noInterrupts();
    delayMicroseconds( 1 ); 
    digitalWrite( TRIG, HIGH );
    delayMicroseconds( 11 );
    digitalWrite( TRIG, LOW );
    //  interrupts();
    //d1 = micros();
    //distance = -1;
    //  while(digitalRead(ECHO)==HIGH) {
    //    distance = 0;
    //  }
    //  d2 = micros();
    //  if (distance == -1) {
    //    Serial.println("ERROR");
    //  }
    duration = pulseInLong( ECHO, HIGH ); // 往復にかかった時間が返却される[マイクロ秒]
    digitalWrite(13,LOW);
    //duration = d2 - d1;
    if (duration > 0) {
      duration = duration / 2; // 往路にかかった時間
      distance = duration * speed_of_sound * 100 / 1000000;
      Serial.print("Distance:");
      Serial.print(distance);
      Serial.println(" cm");
      delay(500);
    }
    delay(500);
}
