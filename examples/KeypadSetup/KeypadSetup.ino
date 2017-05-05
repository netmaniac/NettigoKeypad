/*
  In case Your keypad has different setup of keys, then You can use this sketch
  to read proper one and configure Your keypad.
*/
#include <NettigoKeypad.h>

#define KEYPAD A0

char* keys[] = {"RIGHT", "UP", "DOWN", "LEFT", "SELECT",  };

void setup() {
  Serial.begin(115200);
}

void printHelp(byte cnt) {
  for (byte i = 0; i <= cnt; i++ ) {
    Serial.print('.');
  }
  Serial.println(F("X <- here we will read analog input"));
}

void waitForInput(byte cnt, unsigned delayMs) {
  printHelp(cnt);
  for (byte i = 0; i <= cnt; i++ ) {
    Serial.print('.');
    delay(delayMs);
  }
  Serial.println("X");
}

void dumpTable(unsigned *t, byte sz) {
  for (byte i = 0; i < sz; i++) {
    Serial.print(t[i]);
    Serial.print(F(","));
  }
  Serial.println("");
}

unsigned readings[6];
unsigned sorted[6];

void sort(unsigned  *input , unsigned *output) {

  unsigned tmp;
  bool nextRound;
  //copy array
  for (byte i = 0; i < 6; i++ ) {
    output[i] = input[i];
  }


  do {
    //    dumpTable(output, 6);
    nextRound = false;
    for (byte i = 0; i < 5; i++ ) {
      if (output[i] > output[i + 1]) //wrong order
      {
        //        Serial.print("nextRound in: ");
        //        Serial.print(i);
        //        Serial.print(",");
        //        Serial.print(output[i]);
        //        Serial.print(",");
        //        Serial.println(output[i]);

        nextRound = true;
        tmp = output[i];
        output[i] = output[i + 1];
        output[i + 1] = tmp;
      }

    }
  } while (nextRound) ;


};

byte findInTable(unsigned val, unsigned *t, byte sz) {
  for (byte i = 0; i < sz; i++) {
    if (t[i] == val) {
      return i;
    }
  }
  return 255;
}


int getBoundary(byte idx, unsigned * t) {
  return (t[idx + 1] - t[idx]) / 2 + t[idx];
}

void loop() {
  Serial.println(F("Take keypad and be prepared...."));
  delay(3000);
  for (byte i = 0; i < 5; i++) {
    Serial.print(F("Press "));
    Serial.print(keys[i]);
    Serial.println(F(" and wait for X"));
    waitForInput(20, 100);
    readings[i] = analogRead(KEYPAD);
    Serial.print(F("Reading: "));
    Serial.println(readings[i]);
    delay(500);
  }
  Serial.println(F("Results:"));
  readings[5] = 1024;
  dumpTable(readings, 6);

  sort(readings, sorted);

  Serial.println(F("Sorted results:"));
  dumpTable(sorted, 6);

  for (byte i = 0; i < 5; i++) {
    byte idx = findInTable(sorted[i], readings, 6);
    Serial.print("Val for ");
    Serial.print(keys[idx]);
    Serial.print("/");
    Serial.print(idx);
    Serial.print(" is ");
    Serial.println(readings[idx]);
  }
  Serial.print(F("NG_Keypad keypad("));
  for (char i = 4; i >= 0; i--) {
    byte idx = findInTable(sorted[i], readings, 6);
    if (i != 0) {
      Serial.print(F(","));
    }
      Serial.print(F("\n  NG_Keypad::"));
    Serial.print(keys[idx]);
    Serial.print(",");
    Serial.print(getBoundary(i, sorted));
  }
  Serial.println(F(");"));
  while (true) {};


}