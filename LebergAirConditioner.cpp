#include "LebergAirConditioner.h"


void insert_value(unsigned short int* data, unsigned int value, unsigned int pos, unsigned int len) {
  unsigned int val = value;
  for (int i = 0; i < len; i++) {
    data[(1 + pos + i) * 2 + 1] = (val % 2) ? IR1 : IR0;
    val >>= 1;
  }
}


void build_code(unsigned short int* dst,
                unsigned short int power, unsigned short int eco,
                unsigned short int mode, unsigned short int super,
                unsigned short int temp, unsigned short int fan,
                unsigned short int swing, unsigned short int timer) {
  // Insert initial constant values
  dst[0] = IR_INIT1;
  dst[1] = IR_INIT2;
  for (int i = 2; i < IR_LENGTH - 1; i += 2) {
    dst[i] = IRS;
    dst[i + 1] = IR0;
  }
  dst[IR_LENGTH - 1] = IRS;

  // Insert leberg magic header
  insert_value(dst, LEBERG_INIT_1, 0, 8);
  insert_value(dst, LEBERG_INIT_2, 8, 8);
  insert_value(dst, LEBERG_INIT_3, 16, 8);
  insert_value(dst, LEBERG_INIT_4, 24, 8);
  insert_value(dst, LEBERG_INIT_5, 32, 8);

  // Insert state data
  insert_value(dst, power, IR_OFFSET + 2, 1);
  insert_value(dst, timer > 0 ? (power ? TIMER_ON : TIMER_STANDBY) : TIMER_OFF, IR_OFFSET + 3, 2);
  insert_value(dst, PARAM1_ON, IR_OFFSET + 5, 1);
  insert_value(dst, eco, IR_OFFSET + 7, 1);
  insert_value(dst, mode, IR_OFFSET + 8, 4);
  insert_value(dst, super, IR_OFFSET + 14, 1);
  insert_value(dst, temp, IR_OFFSET + 16, 4);
  insert_value(dst, fan, IR_OFFSET + 24, 3);
  insert_value(dst, swing ? SWING_ON : SWING_OFF, IR_OFFSET + 27, 3);
  if (power) {
    insert_value(dst, timer, IR_OFFSET + 32, 8);
    insert_value(dst, 0, IR_OFFSET + 40, 8);
  } else {
    insert_value(dst, 0, IR_OFFSET + 32, 8);
    insert_value(dst, timer, IR_OFFSET + 40, 8);
  }
  insert_value(dst, super, IR_OFFSET + 59, 1);
  insert_value(dst, (unsigned short int)(mode != MODE_FEEL), IR_OFFSET + 63, 1);

  // Calculate checksum for built state and insert it
  unsigned long checksum = 0;
  for (int i = 2; i < 210; i += 16) {
    unsigned short int part = 0;
    for (int j = 0; j < 8; j++) {
      part |= ((int)(dst[i + j * 2 + 1] > (IR0 + IR1) / 2)) << j;
    }
    checksum += part;
  }
  insert_value(dst, checksum, 13 * 8, 8);
}
