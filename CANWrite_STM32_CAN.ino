
//This is simple example to send random data to CAN bus in 20Hz rate, using delay (not recommended in real implementations).


#include "STM32_CAN.h"
STM32_CAN Can(CAN1, DEF);        //Use PA11/12 pins for CAN1.
//STM32_CAN Can( CAN1, ALT );    //Use PB8/9 pins for CAN1.
//STM32_CAN Can( CAN1, ALT_2 );  //Use PD0/1 pins for CAN1.
//STM32_CAN Can( CAN2, DEF );    //Use PB12/13 pins for CAN2.
//STM32_CAN Can( CAN2, ALT );    //Use PB5/6 pins for CAN2
//STM32_CAN Can( CAN3, DEF );    //Use PA8/15 pins for CAN3.
//STM32_CAN Can( CAN3, ALT );    //Use PB3/4 pins for CAN3

static CAN_message_t CAN_TX_msg;
uint8_t Counter = 0;

void setup() {
  pinMode(PC13, OUTPUT);
  Serial.begin(115200);
  Can.begin();
  Can.setBaudRate(500000);      //500KBPS
  //Can.setBaudRate(250000);    //250KBPS
  //Can.setBaudRate(1000000);   //1000KBPS
}

void loop() {
  if (Counter > 255) {Counter = 0;}

  delay(5000);
  digitalToggle(PC13);
  
  CAN_TX_msg.id = (0x1A5);
  CAN_TX_msg.len = 8;
  CAN_TX_msg.buf[0] = Counter;
  CAN_TX_msg.buf[1] = 0x01;
  CAN_TX_msg.buf[2] = 0x02;
  CAN_TX_msg.buf[3] = 0x03;
  CAN_TX_msg.buf[4] = 0x04;
  CAN_TX_msg.buf[5] = 0x05;
  CAN_TX_msg.buf[6] = 0x06;
  CAN_TX_msg.buf[7] = 0x07;

  Can.write(CAN_TX_msg);

  Serial.println("Sent: ");
  Serial.print("Msg ID: ");
  Serial.println(CAN_TX_msg.id, HEX);
  Serial.print("Msg Data: ");

  for (int i = 0; i < CAN_TX_msg.len; i++) {
    Serial.print(" 0x");
    Serial.print(CAN_TX_msg.buf[i], HEX);
  }

  Serial.println("");
  Serial.println("");


  delay(5000);
  digitalToggle(PC13);

  CAN_TX_msg.flags.extended = 1;  // To enable extended ID.
  CAN_TX_msg.id = (0x1AC32CF5);
  CAN_TX_msg.len = 8;
  CAN_TX_msg.buf[0] = Counter;
  CAN_TX_msg.buf[1] = 0x08;
  CAN_TX_msg.buf[3] = 0x09;
  CAN_TX_msg.buf[4] = 0x0A;
  CAN_TX_msg.buf[5] = 0x0B;
  CAN_TX_msg.buf[6] = 0x0C;
  CAN_TX_msg.buf[7] = 0x0D;

  Can.write(CAN_TX_msg);

  Serial.println("Sent: ");
  Serial.print("Msg ID: ");
  Serial.println(CAN_TX_msg.id, HEX);
  Serial.print("Msg Data: ");

  for (int i = 0; i < CAN_TX_msg.len; i++) {
    Serial.print(" 0x");
    Serial.print(CAN_TX_msg.buf[i], HEX);
  }

  Serial.println("");
  Serial.println("");


  delay(5000);
  digitalToggle(PC13);

  CAN_TX_msg.flags.extended = 0;  // Back to standard ID.
  CAN_TX_msg.id = (0x23);
  CAN_TX_msg.len = 8;
  CAN_TX_msg.buf[0] = Counter;
  CAN_TX_msg.buf[1] = 0x0E;
  CAN_TX_msg.buf[3] = 0x0F;
  CAN_TX_msg.buf[4] = 0x10;
  CAN_TX_msg.buf[5] = 0x11;
  CAN_TX_msg.buf[6] = 0x12;
  CAN_TX_msg.buf[7] = 0x13;

  Can.write(CAN_TX_msg);

  Serial.println("Sent: ");
  Serial.print("Msg ID: ");
  Serial.println(CAN_TX_msg.id, HEX);
  Serial.print("Msg Data: ");

  for (int i = 0; i < CAN_TX_msg.len; i++) {
    Serial.print(" 0x");
    Serial.print(CAN_TX_msg.buf[i], HEX);
  }

  Serial.println();
  Serial.println();

  Counter++;
}
