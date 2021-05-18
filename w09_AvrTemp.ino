while (w == 9) {
time_poliv = millis();
  
   ds.requestTemperatures();

  enc1.tick();
    
  if (enc1.isRight()) {newPos++;}       
  if (enc1.isLeft()) {newPos--; }
  if (newPos < 0 ){newPos=0;  }
  if (newPos > 1 ){newPos=1;  }

  if (lastPos != newPos) { WaitT = millis(); }
  
  if (newPos == 0) {
  LCD.setCursor(0, 0);
  LCD.print("VverhuT: ");
  LCD.setCursor(15, 0);
  LCD.print(ds.getTempC(sensor1));
  LCD.setCursor(19, 0);
  LCD.print("C");

  LCD.setCursor(0, 1);
  LCD.print("PodBochkoyT: ");
  LCD.setCursor(15, 1);
  LCD.print(ds.getTempC(sensor2));
  LCD.setCursor(19, 1);
  LCD.print("C");

  LCD.setCursor(0, 2);
  LCD.print("PochvaT:     ");
  LCD.setCursor(15, 2);
  LCD.print(ds.getTempC(sensor3));
  LCD.setCursor(19, 2);
  LCD.print("C");
  }
  else if (newPos == 1) {
    digitalWrite(SENS_VCC, 1);
  LCD.setCursor(0, 0);
  LCD.print("VverhniyS   ");
  LCD.setCursor(15, 0);
  LCD.print(analogRead(SENS_1));
  LCD.setCursor(18, 0);
  LCD.print(" p");

  LCD.setCursor(0, 1);
  LCD.print("NizniyS     ");
  LCD.setCursor(15, 1);
  LCD.print(analogRead(SENS_2));
  LCD.setCursor(18, 1);
  LCD.print(" p");

  LCD.setCursor(0, 2);
  LCD.print("                     ");
  }

  

   boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) {
    delay(20);
    buttonIsUp = digitalRead(0);
    if (!buttonIsUp )  {
      LCD.clear();
      delay(500);
      digitalWrite(SENS_VCC, 0);
      w = 55;
    }
}

}

/*
  Serial.print("Sensor 1: ");
  Serial.print(ds.getTempC(sensor1)); // отправляем температуру
  Serial.println("C");
  Serial.print("Sensor 2: ");
  Serial.print(ds.getTempC(sensor2)); // отправляем температуру
  Serial.println("C");
  Serial.print("Sensor 3: ");
  Serial.print(ds.getTempC(sensor3)); // отправляем температуру
  Serial.println("C");
  Serial.print("Sensor 4: ");
  Serial.print(ds.getTempC(sensor4)); // отправляем температуру
  Serial.println("C");
  Serial.print("AvrTemp ");
  Serial.print(AvrTemp); // отправляем температуру
  Serial.println("C");
  Serial.println();
*/
