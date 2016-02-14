#include <CHAR_MAP_LCD.h>
#include <SPI.h>

// define pin numbers for audio video sensors
#define VSENSE 6
#define ASENSE 7

// trigger state needs to be volatile since they are modified by interrupt
volatile bool vTrig = 0;
volatile bool aTrig = 0;

unsigned long currentTime;
unsigned long aTime;
unsigned long vTime;
unsigned long triggerTime;
long diffTime;
unsigned long triggerTimeOut = 1000;

// timeout logic
// if(currentTime - triggerTime > triggerTimeOut){ -- re-enable ISR -- }

void setup() {
  Serial.begin(9600);
  pinMode(VSENSE, INPUT);
  pinMode(ASENSE, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  enableIntV();
  enableIntA();
  // attachInterrupt(P1_5, toggleLed, RISING);
}

void loop() {

  currentTime = millis();

  digitalWrite(RED_LED, vTrig);
  digitalWrite(GREEN_LED, aTrig);

  if ((aTrig == 1) && (vTrig == 1)){
    // vTrig = 0;   // need to move this somewhere to keep the leds on
    // aTrig = 0;
    diffTime = (long) (aTime - vTime);
    Serial.print("Audio - Video delay ms:");
    Serial.println(diffTime);
    delay(40);
    enableIntV();
    enableIntA();
  }

  if(((aTrig == 1) || (vTrig == 1)) && (currentTime - triggerTime > triggerTimeOut)){
    Serial.println("Trigger timeout. Resetting.");
    enableIntV();
    enableIntA();
  }

}

void enableIntV(){
  attachInterrupt(VSENSE, triggerV, RISING);
  vTrig = 0;
}

void enableIntA(){
  attachInterrupt(ASENSE, triggerA, RISING);
  aTrig = 0;
}

void triggerV(){
  detachInterrupt(VSENSE);
  digitalWrite(RED_LED, vTrig);
  vTrig = 1;
  vTime = currentTime;
  triggerTime = currentTime;
}

void triggerA(){
  detachInterrupt(ASENSE);
  digitalWrite(GREEN_LED, aTrig);
  aTrig = 1;
  aTime = currentTime;
  triggerTime = currentTime;
}
