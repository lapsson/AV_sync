
int vRead;
int aRead;
int tHold = 200;


long interval = 2000; // interval at which to do something (milliseconds)

void setup() {
  Serial.begin(9600);
  pinMode(P1_4, INPUT);
  pinMode(P1_5, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();
  static unsigned long previousEvent = currentTime; // last time an event triggered

  static bool vTrig = 0;
  static bool aTrig = 0;
  digitalWrite(RED_LED, vTrig);
  digitalWrite(GREEN_LED, aTrig);

  // Get sensor readings and do first loop setup with _Old vars
  vRead = analogRead(P1_4);
  static int vReadOld = vRead;
  aRead = analogRead(P1_5);
  static int aReadOld = aRead;

  // Debug output.
  // Serial.println(vRead);
  Serial.println(aRead);

  // Buissness logic TBD...
  // if(vTrig = 0 && vRead > vReadOld + tHold){
  //   vTrig = 1;
  //   previousEvent = currentTime;
  //   vReadOld = vRead;
  // }
  // else{
  //   vReadOld = vRead;
  // }


  // if(currentMillis - previousMillis > interval) {
  //    previousMillis = currentMillis;
  //
  //    // do something
  // }

  delay(200);

}
