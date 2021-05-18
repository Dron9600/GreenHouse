

if (millis() - last_time > 2000 ) {

  if (sboy == 1 /* || AvrTemp < 10 */) {
    LCD.backlight();
    LCD.clear();
    LCD.setCursor(7, 2);
    LCD.print("SBOY!!");
    delay(2000);
  }

  LCD.setCursor(0, 0);
  LCD.print("VverhuT: ");
  LCD.setCursor(15, 0);
  LCD.print(TempV);
  LCD.setCursor(12, 0);
  LCD.print(datetime.Hour);
  LCD.setCursor(19, 0);
  LCD.print("C");

  LCD.setCursor(0, 1);
  LCD.print("PodBochkoyT:");
  LCD.setCursor(15, 1);
  LCD.print(ds.getTempC(sensor2));
  LCD.setCursor(12, 1);
  LCD.print(datetime.Minute);
  LCD.setCursor(19, 1);
  LCD.print("C");

  LCD.setCursor(0, 2);
  LCD.print("VlazVozd -");
  LCD.setCursor(15, 2);
  LCD.print(BmeH);
  LCD.setCursor(12, 2);
  LCD.print(datetime.Second);
  LCD.setCursor(19, 2);
  LCD.print("%");

  LCD.setCursor(0, 3);
  LCD.print("VlazPoch -   ");
  LCD.setCursor(15, 3);
  LCD.print(humidity);
  LCD.setCursor(19, 3);
  LCD.print("p");

  last_time = millis();


}

boolean buttonIsUp = digitalRead(0);
if (buttonWasUp && !buttonIsUp) {
  delay(20);
  buttonIsUp = digitalRead(0);
  if (!buttonIsUp )  {
    LCD.clear();
    delay(500);
    w = 55;
  }
}
}


while (w == 55) {
    if (millis() - WaitT > 30000) {LCD.clear(); delay(500); w = 0; }

LCD.backlight();
time_poliv = millis();  
TimeFS = millis() / 3600000;

  if (newPos < 4) {
    LCD.setCursor(0, 0);
    LCD.print("Nastroyki    ");
    LCD.setCursor(0, 1);
    LCD.print("Servis            ");
    LCD.setCursor(0, 2);
    LCD.print("Obnulenie      ");
    LCD.setCursor(0, 3);
    LCD.print("Nazad          ");
    LCD.setCursor(15, 3);
    LCD.print(TimeFS);


    if (Timer == 1) {
    TimeOst =24 + Chasi - datetime.Hour;
    LCD.setCursor(15, 2);
    LCD.print(abs(TimeOst));
      }

  } else  {
    LCD.setCursor(0, 0);
    LCD.print("AvrTemp     ");
    LCD.setCursor(0, 1);
    LCD.print("Svet      ");

  LCD.setCursor(0, 2);
  LCD.print("TempMax  ");
  LCD.setCursor(9, 2);
  LCD.print(TempMax);
  LCD.setCursor(14, 2);
  LCD.print("C    ");

  LCD.setCursor(0, 3);
  LCD.print("TempMin  ");
  LCD.setCursor(9, 3);
  LCD.print(TempMin);
  LCD.setCursor(14, 3);
  LCD.print("C     ");
  }

  enc1.tick();
  
  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--; }
  if (newPos < 0 ) { newPos = 0; }
  if (newPos > 5 ) { newPos = 5; }

  if (lastPos != newPos) {
    if (newPos > 3) {
      LCD.setCursor(18 , lastPos - 4);
      LCD.print("  ");
      LCD.setCursor(18 , newPos - 4);
      LCD.print("-=");
      lastPos = newPos;
    } else {
      LCD.setCursor(18 , lastPos);
      LCD.print("  ");
      LCD.setCursor(18 , newPos);
      LCD.print("-=");
      lastPos = newPos;
    }
       WaitT = millis();
  }
  
  boolean buttonIs = digitalRead(0);
  if (buttonWasUp && !buttonIs) {
    delay(20);
    buttonIs = digitalRead(0);
    if (!buttonIs  && newPos == 0) { LCD.clear(); delay(500); w = 1;  }
    if (!buttonIs  && newPos == 1) { LCD.clear(); delay(500); w = 2;}
    if (!buttonIs  && newPos == 2) { LCD.clear(); delay(500); sboy = 0; w = 0; TempMax = TempV ; TempMin = TempN ; }
    if (!buttonIs  && newPos == 3) { LCD.clear(); delay(500); w = 0; }
    if (!buttonIs  && newPos == 4) { LCD.clear(); delay(500); w = 9; }
    if (!buttonIs  && newPos == 5) { LCD.clear(); delay(500); w = 20; }
  }
}
