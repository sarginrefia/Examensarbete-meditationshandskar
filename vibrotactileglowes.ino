#include <math.h>

const int motorPins[6] = {3, 5, 6, 11, 10, 9};
const int touchMulti = 2; 
const int touchSingle = 8; 

enum State {
  IDLE,
  RUN_MULTI,
  RUN_SINGLE
};

State state = IDLE;
const unsigned long cycleTime = 16000;

bool touched(int pin) {
  return digitalRead(pin) == LOW;
}

int smoothPulse(unsigned long t, unsigned long start, int strength) {

  long x = t - start;

  if (x < 0 || x > 2600) return 0;

  float phase = (float)x / 2600.0;
  float wave = sin(phase * PI);

  return (int)((0.2 + wave * 0.8) * strength);
}

void runWave(unsigned long t, unsigned long offset) {

  const unsigned long inhale = 0 + offset;
  const unsigned long exhale = 8000 + offset;

  for (int i = 0; i < 3; i++) {

    int m1 = i;
    int m2 = i + 3;

    int pwm1 = smoothPulse(t, inhale + i * 700, 160);
    int pwm2 = smoothPulse(t, exhale + i * 700, 160);

    analogWrite(motorPins[m1], pwm1);
    analogWrite(motorPins[m2], pwm2);
  }
}

void allOff() {
  for (int i = 0; i < 6; i++) {
    analogWrite(motorPins[i], 0);
  }
}

  void endFeedback() {

  for (int j = 0; j < 3; j++) {

    for (int i = 0; i < 6; i++) {
      analogWrite(motorPins[i], 180);
    }

    delay(120);

    for (int i = 0; i < 6; i++) {
      analogWrite(motorPins[i], 0);
    }

    delay(120);
  }

  allOff();
}

void setup() {

  for (int i = 0; i < 6; i++) {
    pinMode(motorPins[i], OUTPUT);
  }

  pinMode(touchMulti, INPUT_PULLUP);
  pinMode(touchSingle, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  bool multiTouch = touched(touchMulti);
  bool singleTouch = touched(touchSingle);

  static unsigned long startTime = 0;
  static int cyclesDone = 0;

  unsigned long t = millis();

  if (state == IDLE) {

    allOff();

    if (multiTouch) {
      state = RUN_MULTI;
      startTime = millis();
      cyclesDone = 0;
      Serial.println("START 4 CYKLER");
      delay(300); // debounce
    }

    else if (singleTouch) {
      state = RUN_SINGLE;
      startTime = millis();
      Serial.println("START 1 CYKEL");
      delay(300);
    }
  }

  else if (state == RUN_SINGLE) {

    runWave(t - startTime, 0);

    // STOPP (pin 8 igen)
    if (singleTouch) {
      state = IDLE;
      allOff();
      Serial.println("STOP SINGLE");
      delay(300);
      return;
    }

    if (t - startTime >= cycleTime) {
      endFeedback();
      state = IDLE;
      Serial.println("SINGLE KLAR");
    }
  }

  else if (state == RUN_MULTI) {

    unsigned long elapsed = t - startTime;

    runWave(elapsed % cycleTime, 0);

    if (multiTouch) {
      state = IDLE;
      allOff();
      Serial.println("STOP MULTI");
      delay(300);
      return;
    }

    if (elapsed >= cycleTime * 4) {
      endFeedback();
      state = IDLE;
      Serial.println("4 CYKLER KLARA");
    }
  }
}