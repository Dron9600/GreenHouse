while (w == 6) {
time_poliv = millis();
  
    LCD.setCursor(0, 1);
    LCD.print("Poziciya");
    LCD.setCursor(15, 0);
    LCD.print("Otkr");
    LCD.setCursor(15, 1);
    LCD.print("Zakr");
    LCD.setCursor(0 , 3);
    LCD.print("Nazad");
    
     enc1.tick();
     delay(10);
    
  if (enc1.isRight()) {Serial.println(newPos++);}         // если был поворот
  if (enc1.isLeft()) {Serial.println(newPos--); }
  if (newPos < 0 ){newPos=0;  }
  if (newPos > 3 ){newPos=3;  }

     if (lastPos != newPos) {
      LCD.setCursor(13, lastPos);
      LCD.print("   ");
      LCD.setCursor(13 , newPos);
      LCD.print("==");
      lastPos = newPos;
      WaitT = millis();
      }

//    if (millis() - WaitT > 30000) {LCD.clear(); delay(500); w = 0; }


       boolean buttonIsUp = digitalRead(0);
    if (buttonWasUp && !buttonIsUp) {
      buttonIsUp = digitalRead(0);
      if (!buttonIsUp  && newPos == 0)  { 
      digitalWrite(STBY, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMB, motorSpeed);
      delay(8000);
      digitalWrite(BIN1, LOW);    // крутим моторы в противоположную сторону
      digitalWrite(BIN2, LOW);
      digitalWrite(STBY, LOW);
      motor = 1;}
      if (!buttonIsUp  && newPos == 1) {
      digitalWrite(STBY, HIGH);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMB, motorSpeed);
      delay(15000);
      digitalWrite(BIN1, LOW);    // крутим моторы в противоположную сторону
      digitalWrite(BIN2, LOW);
      digitalWrite(STBY, LOW);
      motor = 0;}
      if (!buttonIsUp  && newPos == 3) { LCD.clear(); delay(500); w = 2; }
}


}
