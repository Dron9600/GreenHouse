#include "Wire.h"                                 // библиотека для протокола I2C
#include "LiquidCrystal_I2C.h"           // библиотека для дисплея
#include <Adafruit_Sensor.h>                            // Подключаем библиотеку Adafruit_Sensor
#include <Adafruit_BME280.h>
#include "GyverEncoder.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <GyverWDT.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <EEPROM.h>



// -------------------- ПИНЫ ---------------------
#define SW        0
#define RELAY_1   1
#define CLK       2
#define DT        3
#define RELAY_2   4                          // реле полива
#define RELAY_3   5                          //датчики темпиратуры ds18b20 (RELAY3)
#define RELAY_4   6                          // реле вентилятора
#define RELAY_5   7                          // Svet
#define RELAY_6   8                          // klapan
#define RELAY_7   9                          // vitezka
#define PWMB      11                         /////////////
#define BIN1      10                         //tb6612fng//
#define BIN2      12                         //         // 
#define STBY      13      //SERV1            /////////////
#define SERV_2    A0                        
#define SENS_VCC  A1      //ПИТАНИЕ
#define SENS_1    A2                         //сенсор влажности 1
#define SENS_2    A3                         //сенсор влажности 2
#define SENS_3    A6                         //лампочка
#define SENS_4    A7

#define POSMIN 0
#define POSMAX 3
#define POSMAX_2 5
#define TimeBS 15000
#define ENCODER_TYPE 1

Adafruit_BME280 bme;

LiquidCrystal_I2C LCD(0x27, 20, 4);   // присваиваем имя дисплею
Encoder enc1(CLK, DT, SW);  // для работы c кнопкой

boolean buttonWasUp = true, sboy = 0, motor = 0, nasos = 0;
int newPos = 0, lastPos, Lpos = 0, Lpos2 = 0, vlaznost = 600, humidity = 0, motorSpeed = 255, TimeFS, TimeDo = 3, TimeNa = 5, TimeOst = 0;
int TempZakr = 24, TempOtkr = 25, VentilatorT = 22, svet = 1, Chasi = 2, Minuti = 10, ObrOt = 0, address = 10;
int TempVitezka =22 , TempKlap = 18;
uint32_t last_time, time_poliv, sleepT = 0, period = 0, sensorTimer = 0, TBtw = 0, VentTimer = 0, periodVent = 0, WaitT = 0, Rtime, TimeSveta, TimeDoVkl, TimeRabotiLamp, NaSkolVkl = 21600000, TimeObnovlenie, vremaNasosa, TimeRec, sec;
byte w = 0, sensorMode = 0, VentMode = 0, VentPos = 0, Timer = 0;
float AvrTemp, BmeH, BmeT, TempV, TempN = 30, TempMin = 30 , TempMax, Min = 0;


OneWire oneWire(RELAY_3);
DallasTemperature ds(&oneWire);
DeviceAddress sensor1 = {0x28, 0xBA, 0x4F, 0x79, 0xA2, 0x1, 0x3, 0xF4};
DeviceAddress sensor2 = {0x28, 0xCF, 0x9D, 0x79, 0xA2, 0x1, 0x3, 0x5A};
DeviceAddress sensor3 = {0x28, 0x5F, 0x73, 0x79, 0xA2, 0x1, 0x3, 0x93};

///DS3132
   String inSer = "";
   boolean strFull = false;
   tmElements_t datetime;

 int  TempZakr_R, TempOtkr_R, VentilatorT_R, Chasi_R, Minuti_R, TempVitezka_R, TempKlap_R, TimeNa_R;
 int  EEMEM TempZakr_d, EEMEM TempOtkr_d, EEMEM VentilatorT_d, EEMEM Chasi_d, EEMEM Minuti_d, EEMEM NaSkolVkl_d, EEMEM TempVitezka_d, EEMEM TempKlap_d, EEMEM TimeNa_d;

void setup() {

  EEPROM.get((int)&TempZakr_d, TempZakr_R);
  TempZakr = TempZakr_R;
  EEPROM.get((int)&TempOtkr_d, TempOtkr_R);
  TempOtkr = TempOtkr_R;
  EEPROM.get((int)&VentilatorT_d, VentilatorT_R);
  VentilatorT = VentilatorT_R;
  EEPROM.get((int)&Chasi_d, Chasi_R);
  Chasi = Chasi_R;
  EEPROM.get((int)&Minuti_d, Minuti_R);
  Minuti = Minuti_R;
 // EEPROM.get((int)&NaSkolVkl_d, NaSkolVkl_R);
 // NaSkolVkl = NaSkolVkl_R;
  EEPROM.get((int)&TempVitezka_d, TempVitezka_R);
  TempVitezka = TempVitezka_R;
  EEPROM.get((int)&TempKlap_d, TempKlap_R);
  TempKlap = TempKlap_R;
  EEPROM.get((int)&TimeNa_d, TimeNa_R);
  TimeNa = TimeNa_R;
   
   EEPROM[0] += 10;

   
  LCD.init();            // инициализация LCD дисплея и подсветки
  LCD.backlight();
  Serial.begin(9600);
  enc1.setType(TYPE1);
  attachInterrupt(0, isrCLK, CHANGE);    // прерывание на 2 пине! CLK у энка
  attachInterrupt(1, isrDT, CHANGE);    // прерывание на 3 пине! DT у энка
  ds.begin();

  pinMode(SW, INPUT_PULLUP);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  pinMode(RELAY_5, OUTPUT);
  pinMode(RELAY_6, OUTPUT);
  pinMode(RELAY_7, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(SENS_VCC, OUTPUT);
  digitalWrite(STBY, LOW);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_4, HIGH);
  digitalWrite(RELAY_5, HIGH);
  digitalWrite(RELAY_6, HIGH);
  digitalWrite(RELAY_7, HIGH);
  


  if (!bme.begin(0x76)) {                                // Инициализация датчика BME280
    Serial.println("Could not find a valid BME280!");  // Печать сообщения об ошибки

  }
}
void isrCLK() { enc1.tick(); }
void isrDT() { enc1.tick(); }

 void print2(int nn,String str) {
      if (nn >= 0 && nn < 10)
         { Serial.print("0");}
      Serial.print(nn);
      Serial.print(str);
   }
   
   void serialEvent() {
      while (Serial.available()) {
         // получить очередной байт:
         char c = (char)Serial.read();
         // добавить в строку
         inSer += c;
         // /n - конец передачи
         if (c == '\n')
            { strFull = true;}
      }
   }

void loop() {
    
  while (w == 0) {
 WaitT = millis();
/*
 Serial.println(TempZakr);
 Serial.println(TempZakr_R);
 Serial.println(TempOtkr);
 Serial.println(TempOtkr_R);
 Serial.println(VentilatorT);
 Serial.println(VentilatorT_R);
 Serial.println(Chasi);
 Serial.println(Chasi_R);
 Serial.println(TempKlap);
 Serial.println(TempKlap_R);
 Serial.println(TempVitezka);
 Serial.println(TempVitezka_R);
 Serial.println(TimeNa);
 Serial.println(TimeNa_R);
*/
 NaSkolVkl = TimeNa*3600000;
 if (millis() - TimeRec > 3600000){
 EEPROM.put((int)&TempZakr_d, TempZakr);
 EEPROM.put((int)&TempOtkr_d, TempOtkr); 
 EEPROM.put((int)&VentilatorT_d, VentilatorT); 
 EEPROM.put((int)&Chasi_d, Chasi);
 EEPROM.put((int)&Minuti_d, Minuti);
// EEPROM.put((int)&NaSkolVkl_d, NaSkolVkl);
 EEPROM.put((int)&TempKlap_d, TempKlap);
 EEPROM.put((int)&TempVitezka_d, TempVitezka);
 EEPROM.put((int)&TimeNa_d, TimeNa);

/*
 TempZakr = 25;
 TempOtkr = 22;
 VentilatorT = 21;
 Chasi = 10;
// Minuti = 5;
// NaSkolVkl = 18000000;

TempKlap = 18;
TempVitezka = 22;
TimeNa = 5;
*/
    TimeRec = millis();   
   }

  



if ( millis() - TimeObnovlenie > 60000) {
  LCD.clear();
  TimeObnovlenie = millis();
}
    enc1.tick();
    if (enc1.isRight()) { newPos++; }
    if (enc1.isLeft()) { newPos--; }
    if (newPos > 5) {LCD.clear(); w = 7; newPos = 0; }

    if (millis() - sleepT > 30000) { LCD.noBacklight(); }
    if (lastPos != newPos) { sleepT = millis(); lastPos = newPos; LCD.backlight(); }

    

    ///////////////////////  Часы  //////////////////////////////////////////////////////////////////////////

        if (strFull) {
         datetime.Hour=(int(inSer[11])-48)*10+(int(inSer[12])-48);
         datetime.Minute=(int(inSer[14])-48)*10+(int(inSer[15])-48);
         datetime.Second=(int(inSer[17])-48)*10+(int(inSer[18])-48);
         datetime.Day=(int(inSer[0])-48)*10+(int(inSer[1])-48);
         datetime.Month=(int(inSer[3])-48)*10+(int(inSer[4])-48);
         datetime.Year=CalendarYrToTm((int(inSer[6])-48)*1000+(int(inSer[7])-48)*100+(int(inSer[8])-48)*10+(int(inSer[9])-48));
        RTC.write(datetime); // записать данные в DS3231
         // очистить строку
         inSer = "";
         strFull = false;
      }
      // получение данных из ds3231
      if (RTC.read(datetime)) {
         print2(datetime.Hour, ":");
         print2(datetime.Minute, ":");
         print2(datetime.Second, " ");
         print2(datetime.Day, "/");
         print2(datetime.Month, "/");
         print2(tmYearToCalendar(datetime.Year) ,"");
         Serial.println();
      }
      else {
            Serial.print("error");
      }


  

  /////////////// Ventilator //////////////////////////////////
       if (TempV > VentilatorT) {
         digitalWrite(RELAY_4, LOW);
       } else if (TempV < VentilatorT - 0.5) {
     if (millis() - VentTimer > periodVent) {
       VentTimer = millis();
       switch (VentMode) {
       case 0: 
        VentMode = 1;
        periodVent = 1200000;       /////выключение 
        digitalWrite(RELAY_4, HIGH);
        break;
      case 1:   // измеряем
        VentMode = 0;
        digitalWrite(RELAY_4, LOW);
        periodVent = 180000;      /////включение
         break;
    }

     }
       }
  
/////////////////////////////////////////////////////////////
     //Опрос сенсеров 
/////////////////////////////////////////////////////////////////////////////////////////////////////////
   if (millis() - sensorTimer >= period) {
    sensorTimer = millis();
    switch (sensorMode) {
      case 0:   // вкл питание
        sensorMode = 1;
        period = 100;
        digitalWrite(SENS_VCC, 1);
        
        break;
      case 1:   // измеряем
        sensorMode = 2;
        period = 25;
        BmeT = bme.readTemperature();
        BmeH = bme.readHumidity();
        analogRead(SENS_1);
        analogRead(SENS_2);
        TempV = ds.getTempC(sensor1);
        TempN = ds.getTempC(sensor2);
        ds.requestTemperatures();
        humidity = (analogRead(SENS_1) + analogRead(SENS_2))/2; 
        AvrTemp = (ds.getTempC(sensor1) + ds.getTempC(sensor2)) / 2;

      if(AvrTemp < TempZakr && millis() < 3000) {motor = 1;}
        break;
      case 2:   // выключаем
        sensorMode = 0;
        period = 3000;
        digitalWrite(SENS_VCC, 0);
        break;
        Rtime = millis();
    }
  }
 /* if (millis() - Rtime > 10000) {
  Watchdog.reset();  
  }
*/
  if (TempV > TempMax) { TempMax = TempV;}
  if (TempN < TempMin){TempMin = TempN;}

    ///////////////Okna////////////////////////////////

     
    if (AvrTemp > TempOtkr && motor == 0 && millis() > 10000) {
      digitalWrite(STBY, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMB, motorSpeed);
      delay(11000);
      digitalWrite(STBY, LOW);
      digitalWrite(BIN1, LOW);
      motor = 1;
    }
    else if (AvrTemp < TempZakr && motor == 1 && millis() > 10000) {
      digitalWrite(STBY, HIGH);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMB, motorSpeed);
      delay(18000);
      digitalWrite(STBY, LOW);
      digitalWrite(BIN2, LOW);
      motor = 0;
    }
    ////////////////////////////////////////////////////////////////////////////////////
    //////////// Свет 
    ////////////////////////////////////////////////////////////////////////////////////
    if (Chasi <= datetime.Hour && datetime.Hour < (Chasi+TimeNa) && svet == 1) {
       digitalWrite(RELAY_5, LOW);
       TimeRabotiLamp = millis();
       svet = 0;
       Timer = 0;
     } else if (millis() - TimeRabotiLamp > NaSkolVkl && svet == 0 ) {
      digitalWrite(RELAY_5, HIGH);
      TimeSveta = millis();
      svet = 1;
      Timer = 1;
      TimeDoVkl = 86400000 - NaSkolVkl;
     }

     /////////////////////// klapan /////////////////////////////

     if (AvrTemp > TempKlap ) { digitalWrite(RELAY_6, LOW);}
     else if (AvrTemp < TempKlap - 0.5 )  {digitalWrite(RELAY_6, HIGH);}

     ////////////////////// vitezka //////////////////////

     
     if (AvrTemp > TempVitezka )  {digitalWrite(RELAY_7, LOW);}
     else if (AvrTemp < TempVitezka - 0.5 )  {digitalWrite(RELAY_7, HIGH);}
    
