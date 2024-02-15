int x;
unsigned int y;  //y precisa ser unsigned, pois o pwm do stm32 é de 16bits e vamos trabalhar apenas c valores inteiros
void setup() {
 pinMode(PB1, INPUT_ANALOG); //deve ser usado quando a entrada for analógica
 pinMode(PA3, PWM);  //deve ser usado quando a saída for pwm
 Serial.begin(9600);
}

void loop() {
  x=analogRead(PB1);  //conversor ad do stm32 é de 12 bits  
  Serial.print("pot:");
  Serial.print(x);
  y=map(x, 0, 4095, 0, 65535);
  pwmWrite(PA3, y);  //equivalente ao analogWrite. Deve ser usado ao invés do analogwrite por conta da resolução do pwm do stm32
  Serial.print(" led:");
  Serial.println(y);
  //delay(500);
  
}
