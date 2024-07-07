//https://kit.alexgyver.ru/tutorials/ir-remote/?ysclid=lxkqogijop430602806
//https://alexgyver.ru/lessons/pwm-signal/
// https://kit.alexgyver.ru/tutorials/ds18b20/?ysclid=lxlkrskf6w618018544
#define IR_1    0xC8
#define IR_2    0xD8
#define IR_3    0xE0
#define IR_4    0xE8
#define IR_5    0xF8
#define IR_6    0xC0
#define IR_7    0x68
#define IR_8    0x78
#define IR_9    0x40
#define IR_STAR 0xCA
#define IR_0    0x58
#define IR_HASH 0x6A
#define IR_UP   0x9A
#define IR_LEFT 0xB2
#define IR_OK   0xBA
#define IR_RIGHT 0x7A
#define IR_DOWN 0xAA
#define IR_ZVK 0xC2
#include <NecDecoder.h>
#include <microDS18B20.h>
#define DS_PIN 7 // пин для термометров
// Уникальные адреса датчиков - считать можно в примере address_read
uint8_t s1_addr[] = {0x28, 0xFF, 0xCD, 0x59, 0x51, 0x17, 0x4, 0xFE};
uint8_t s2_addr[] = {0x28, 0xFF, 0x36, 0x94, 0x65, 0x15, 0x2, 0x80};
MicroDS18B20<DS_PIN, s1_addr> sensor1;  // Создаем термометр с адресацией
MicroDS18B20<DS_PIN, s2_addr> sensor2;  // Создаем термометр с адресацией

NecDecoder ir;

byte on_off = 5;
byte on_vntltr = 6;
byte tprtr = 8;
uint8_t my_per = LOW;
uint8_t my_dv = LOW;

void ds_tmpr () {
   // асинхронное чтение нескольких датчиков смотри в примере async_read_many
  sensor1.requestTemp();      // Запрашиваем преобразование температуры
  sensor2.requestTemp();
  delay(1000);           // ожидаем результат 
  
  Serial.print("t1: ");
  if (sensor1.readTemp()) Serial.println(sensor1.getTemp());
  else Serial.println("error");
  Serial.print("t2: ");
  if (sensor2.readTemp()) Serial.println(sensor2.getTemp());
  else Serial.println("error");
 }

 /*volatile uint32_t debounce1;
 void awr() {
  // оставим 100 мс таймаут на гашение дребезга
  // CHANGE не предоставляет состояние пина, 
  // придётся узнать его при помощи digitalRead
   if (millis() - debounce1 >= 100 && digitalRead(3)) {
    debounce = millis();}
    isWorkKlap = !isWorkKlap; // понижение температуры испарителя
    digitalWrite ( compr, HIGH);
    delay (500);
    wrk = "awr";
    com = "IMP";
    DoorNew = 1; 
      digitalWrite ( 7, HIGH);
      delay (3);
      digitalWrite ( 7, LOW);
      delay (500);
    // ваш код по прерыванию по высокому сигналу
    во как
 } */

void pusk_Bp () {
   unsigned long heatTimeStamp=millis(); //Время включения вентилятора
      //wrk = "zPaus"; // "freeze"
     // provH="paus";
       my_per = !my_per;
  digitalWrite (on_off, my_per);
      while ( millis() - heatTimeStamp < 2000){ 
       // heatTimeStamp = millis();
       // break;}
  // my_per = !my_per;
  // digitalWrite (on_off, my_per);
  }
}
void pusk_Dv () {
  if (my_per == LOW) {
   // unsigned long heatTimeStamp=millis(); //Время включения вентилятора
  my_dv = !my_dv;
  //while ( millis() - heatTimeStamp < 1000){ 
     //   heatTimeStamp = millis();break;}
    while (my_per == HIGH && my_dv == HIGH) {
    digitalWrite (on_vntltr, my_dv); 
     ir.readCommand();
     if (ir.available()){
      if (my_per == HIGH ) {
  my_dv = !my_dv;}
      break;
     }
     
    }
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(on_off, OUTPUT);
  digitalWrite(on_off, HIGH);
  pinMode(on_vntltr, OUTPUT);
  digitalWrite(on_vntltr, HIGH);
  pinMode(tprtr, INPUT);
  attachInterrupt(0, irIsr, FALLING);
}
void irIsr() {
  ir.tick();
}
void loop() {
   ds_tmpr ();
  const unsigned long prekrRab = 30000;  //300000; Интервал считывания температуры 5 минуты паузы
     unsigned long heatTimeStamp=millis(); //Время включения вентилятора

      while ( millis() - heatTimeStamp < prekrRab){ 
      
//ds_tmpr ();
      if (ir.available()) {
        switch (ir.readCommand()) {
          // выводим в порт, тут может быть ваш код
          case IR_1: Serial.println("Pressed 1"); break;
          case IR_2: Serial.println("Pressed 2"); break;
          case IR_3: Serial.println("Pressed 3"); break;
          case IR_4: Serial.println("Pressed 4"); break;
          case IR_5: Serial.println("Pressed 5"); break;
          case IR_6: Serial.println("Pressed 6"); break;
          case IR_7: Serial.println("Pressed 7"); break;
          case IR_8: Serial.println("Pressed 8"); break;
          case IR_9: Serial.println("Pressed 9"); break;
          case IR_STAR: pusk_Bp (); break;
          case IR_0: Serial.println("Pressed 0"); break;
          case IR_HASH: pusk_Dv (); break;
          case IR_UP: Serial.println("Pressed up"); break;
          case IR_LEFT: Serial.println("Pressed left"); break;
          case IR_OK: Serial.println("Pressed ok"); break;
          case IR_RIGHT: Serial.println("Pressed right"); break;
          case IR_DOWN: Serial.println("Pressed down"); break;
        }
      }//break;
  } 
  // ds_tmpr ();
}
/* prd = imps
if (prd <= 200) prd = 200;
if (prd >= 252) prd = 256;
if ()
Нужно как-то доделать...*/