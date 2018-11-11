/*
Copyright (c) 2018 Oleg Krasnikov <a.insolite@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _LebergAirConditioner_h
#define _LebergAirConditioner_h

#define LEBERG_INIT_1 0b00100011
#define LEBERG_INIT_2 0b11001011
#define LEBERG_INIT_3 0b00100110
#define LEBERG_INIT_4 0b00000001
#define LEBERG_INIT_5 0b00000000

#define POWER_ON  0b1
#define POWER_OFF 0b0

// IDK what is it
#define PARAM1_ON  0b1
#define PARAM1_OFF 0b0

#define ECO_ON  0b1
#define ECO_OFF 0b0

#define TIMER_ON      0b01
#define TIMER_OFF     0b00
#define TIMER_STANDBY 0b10

#define MODE_FEEL 0b1000
#define MODE_COOL 0b0011
#define MODE_DRY  0b0010
#define MODE_FAN  0b0111

#define SUPER_ON  0b1
#define SUPER_OFF 0b0

#define TEMP_16C  0b0000
#define TEMP_17C  0b0001
#define TEMP_18C  0b0010
#define TEMP_19C  0b0011
#define TEMP_20C  0b0100
#define TEMP_21C  0b0101
#define TEMP_22C  0b0110
#define TEMP_23C  0b0111
#define TEMP_24C  0b1000
#define TEMP_25C  0b1001
#define TEMP_26C  0b1010
#define TEMP_27C  0b1011
#define TEMP_28C  0b1100
#define TEMP_29C  0b1101
#define TEMP_30C  0b1110
#define TEMP_31C  0b1111

#define FAN_AUTO  0b000
#define FAN_LOW   0b010
#define FAN_MID   0b011
#define FAN_HIGH  0b101
#define FAN_SLEEP 0b001

#define SWING_OFF 0b000
#define SWING_ON  0b111

#define IR_INIT1         3100 // IR init: led is ON for (IR_INIT1)μs
#define IR_INIT2 IR_INIT1 / 2 // IR init: led is OFF for (IR_INIT2)μs
#define IRS               550 // IR led is ON for (IRS)μs
#define IR0               300 // IR led is OFF for (IR0)μs - means 0
#define IR1              1050 // IR led is OFF for (IR1)μs - means 1
#define IRX                 0 // IR led is OFF for (IR0 or IR1)μs - means 0 or 1 (placeholder)

#define IR_OFFSET  40 // Start of the State data in the IR code
#define IR_LENGTH 227 // IR code length


void insert_value(unsigned short int* data, unsigned int value, unsigned int pos, unsigned int len);
void build_code(unsigned short int* dst,
                unsigned short int power=POWER_OFF, unsigned short int eco=ECO_OFF,
                unsigned short int mode=MODE_FEEL, unsigned short int super=SUPER_OFF,
                unsigned short int temp=TEMP_16C, unsigned short int fan=FAN_AUTO,
                unsigned short int swing=SWING_OFF, unsigned short int timer=0);

#endif
