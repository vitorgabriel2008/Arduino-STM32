
//Este exemplo lê todos os dados da CAN Bus e os imprime no monitor serial.

#include "STM32_CAN.h"
STM32_CAN Can( CAN1, DEF );     //Use PA11/12 pins for CAN1.
//STM32_CAN Can( CAN1, ALT );   //Use PB8/9 pins for CAN1.
//STM32_CAN Can( CAN1, ALT_2 ); //Use PD0/1 pins for CAN1.
//STM32_CAN Can( CAN2, DEF );   //Use PB12/13 pins for CAN2.
//STM32_CAN Can( CAN2, ALT );   //Use PB5/6 pins for CAN2
//STM32_CAN Can( CAN3, DEF );   //Use PA8/15 pins for CAN3.
//STM32_CAN Can( CAN3, ALT );   //Use PB3/4 pins for CAN3

static CAN_message_t CAN_RX_msg;

void setup() {
  pinMode(PC13, OUTPUT);
  Serial.begin(115200);
  Can.begin();
  Can.setBaudRate(500000);     //500KBPS
  //Can.setBaudRate(1000000);  //1000KBPS
  //Can.setBaudRate(250000);   //250KBPS
}

void loop() {
   Can.read(CAN_RX_msg);
   
   Serial.print("Interface CAN:");
   Serial.print(CAN_RX_msg.bus);
    if (CAN_RX_msg.flags.extended == false) {
      Serial.print(" - ID Padrão:");
    }
    else {
      Serial.print(" - ID Extendido:");
    }
    Serial.print(CAN_RX_msg.id, HEX);

    Serial.print(" - Tamanho Msg Data:");
    Serial.print(CAN_RX_msg.len);
    Serial.print(" Bytes");
    if (CAN_RX_msg.flags.remote == false) {
       Serial.print(" - Msg Data:");
      for(int i=0; i<CAN_RX_msg.len; i++) {
        Serial.print("0x"); 
        Serial.print(CAN_RX_msg.buf[i], HEX); 
        if (i != (CAN_RX_msg.len-1))  Serial.print(" ");
      }
      Serial.println();
      Serial.println();
    } else {
       Serial.println(" Data: REMOTE REQUEST FRAME");
    }
    if(CAN_RX_msg.id==(0x1A5) && CAN_RX_msg.buf[0]==(0X03)){digitalToggle(PC13);}  //Se o Id da msg recebida for igual a 0x1A5 e o primeiro byte dos dados for igual a 0X03, pica o led da placa

    delay(300);

  }
