//#include <Arduino.h>
#include "ST7567S.h"

#include "Console.h"
#include <DallasTemperature.h>

// контакт данных датчика подключен к контакту 2 платы Arduino 
#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS); 
// связываем наш объект oneWire с библиотекой Dallas Temperature. 
DallasTemperature sensors(&oneWire);
Console<ST7567S<0x3F>> lcd;

void setup() {
Serial.begin(9600); 
 Serial.println(F("Dallas Temperature IC Control Library Demo")); 
 // инициализируем датчик 
 sensors.begin(); 
  lcd.init();
  if (! lcd.begin()) {
    Serial.println(F("ST7567S display not found!"));
    Serial.flush();
    //ESP.deepSleep(0);
  }
//  lcd.flip(true);
  delay(1000);
  lcd.clear(); 
    delay(1000);
  //  lcd.inverse((i & 0x01) == 0);

    delay(100);
  /*for (int8_t contrast = 29; contrast >= 0; contrast -= 2) {
    delay(100);
    lcd.contrast(contrast);
  }*/
 // lcd.powerSave(true);
}

void loop() {
  //lcd.println();
  sensors.requestTemperatures(); // передаем команду на запрос температуры
  float tisp =sensors.getTempCByIndex(0);
  delay (1000);
  lcd.clear();
  lcd.print(F("Температура в комнате  "));//lcd.print(F("Kомнатa  Улица  Кухня  "));
  lcd.println(tisp); //lcd.println(tisp,"||",tul,"||",tkuh);
  

  delay (59900);
}

