/*
RF-controlled remote for Leberg air conditioner
*/

#include <IRremote.h>
#include <RCSwitch.h>
#include <LebergAirConditioner.h>


#define IR_OUT_VCC_PIN  8
#define IR_OUT_GND_PIN  9
#define IR_OUT_DATA_PIN 3

#define RECV_VCC_PIN 10
#define RECV_GND_PIN 11

#define MAGIC           5
#define MAGIC_LENGTH    3
#define PAYLOAD_LENGTH 21

#define RF_MODE_FEEL 0
#define RF_MODE_COOL 1
#define RF_MODE_DRY  2
#define RF_MODE_FAN  3

unsigned short int code[IR_LENGTH];

IRsend irsend;

RCSwitch mySwitch = RCSwitch();


void setup() {
  Serial.begin(9600);   // Status message will be sent to PC at 9600 baud

  // GND
  pinMode(IR_OUT_GND_PIN, OUTPUT);
  digitalWrite(IR_OUT_GND_PIN, LOW); // Avoid any reverse polarity

  // VCC
  pinMode(IR_OUT_VCC_PIN, OUTPUT);
  digitalWrite(IR_OUT_VCC_PIN, HIGH);

  // GND
  pinMode(RECV_GND_PIN, OUTPUT);
  digitalWrite(RECV_GND_PIN, LOW); // Avoid any reverse polarity

  // VCC
  pinMode(RECV_VCC_PIN, OUTPUT);
  digitalWrite(RECV_VCC_PIN, HIGH);

  mySwitch.enableReceive(0);
}


unsigned short int extract_bits(unsigned long value, unsigned int start, unsigned int len) {
  unsigned long val = value;
  unsigned int pos = PAYLOAD_LENGTH - start;
  val %= (unsigned long)1 << pos;
  val >>= pos - len;
  return val;
}


void loop() {
  if (mySwitch.available()) {
    unsigned long value = mySwitch.getReceivedValue();
    unsigned int magic = value >> PAYLOAD_LENGTH;
    if (magic == MAGIC) { // This RF code is dedicated to our device
      // Extract state data from RF code
      unsigned long data = value % ((unsigned long)1 << PAYLOAD_LENGTH);
      unsigned short int power = extract_bits(data, 0, 1);
      unsigned short int eco = extract_bits(data, 1, 1);
      unsigned short int mode = extract_bits(data, 2, 2);
      unsigned short int super = extract_bits(data, 4, 1);
      unsigned short int temp = extract_bits(data, 5, 4);
      unsigned short int fan = extract_bits(data, 9, 3);
      unsigned short int swing = extract_bits(data, 12, 1);
      unsigned short int timer = extract_bits(data, 13, 8);

      // Log input state data
      Serial.print("power\t"); Serial.println(power);
      Serial.print("eco\t");   Serial.println(eco);
      Serial.print("mode\t");  Serial.println(mode);
      Serial.print("super\t"); Serial.println(super);
      Serial.print("temp\t");  Serial.println(temp);
      Serial.print("fan\t");   Serial.println(fan);
      Serial.print("swing\t"); Serial.println(swing);
      Serial.print("timer\t"); Serial.println(timer);

      // Build IR code from state data
      switch (mode) {
        case RF_MODE_FEEL:
          mode = MODE_FEEL;
          break;
        case RF_MODE_COOL:
          mode = MODE_COOL;
          break;
        case RF_MODE_DRY:
          mode = MODE_DRY;
          break;
        case RF_MODE_FAN:
          mode = MODE_FAN;
          break;
      }
      build_code(code, power, eco, mode, super, temp, fan, swing, timer);

      // Send IR code
      irsend.sendRaw(code, IR_LENGTH, 38);

      // Log sent IR code
      for (int i = 0; i < 226; i+=2) {
        Serial.print(code[i]);
        Serial.print(",");
        Serial.print(code[i + 1]);
        Serial.print(", ");
      }
      Serial.print(code[226]);
      Serial.println("");

      // Delay to skip repeated code
      delay(250);
    }

    mySwitch.resetAvailable();
  }
}
