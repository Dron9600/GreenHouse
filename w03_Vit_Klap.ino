while (w == 3) {
LCD.setCursor(0, 0);
  LCD.print("TempKlap ");
  LCD.setCursor(0, 1);
  LCD.print("TempVitezki ");
  LCD.setCursor(0, 2);
  LCD.print("Otkl");
  LCD.setCursor(0, 3);
  LCD.print("Nazad");
  enc1.tick();

  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;}
  if (newPos < 0 ) { newPos = 0; }
  if (newPos > 3 ) { newPos = 3; }


  if (lastPos != newPos) {
    LCD.setCursor(17, lastPos);
    LCD.print("  ");
    LCD.setCursor(17, newPos);
    LCD.print("-=");
    lastPos = newPos;
    WaitT = millis();
  }

    if (millis() - WaitT > 30000) {LCD.clear(); delay(500); w = 0; }

  
  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) {
    delay(20);
    buttonIsUp = digitalRead(0);
    if (!buttonIsUp  && newPos == 0)  { LCD.clear(); delay(500); w = 31;  }
    if (!buttonIsUp  && newPos == 1)  { LCD.clear();  delay(500); w = 32; }
    if (!buttonIsUp  && newPos == 2)  { LCD.clear();  delay(500); digitalWrite(RELAY_6, HIGH); digitalWrite(RELAY_7, HIGH); }
    if (!buttonIsUp  && newPos == 3)  { LCD.clear();  delay(500); w = 1;  }
  }

while (w == 31) {
  LCD.setCursor(0, 0);
  LCD.print("TempKlap ");
  enc1.tick();

  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;  }


  if (lastPos != newPos) {
    LCD.clear();
    LCD.setCursor(15, 0);
    LCD.print(TempKlap + 0.5 * newPos);
    lastPos = newPos;
  }
  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) { delay(50); buttonIsUp = digitalRead(0); }
  if (!buttonIsUp)  { LCD.clear();  delay(500); w = 3; TempKlap = TempKlap + 0.5 * newPos; }
}
while (w == 32) {
    LCD.setCursor(0, 1);
    LCD.print("TempVitezki ");
    enc1.tick();

  if (enc1.isRight()) { newPos++; }         // если был поворот
  if (enc1.isLeft())  { newPos--; }


     if (lastPos != newPos) {
     LCD.clear();
     LCD.setCursor(15, 1);
     LCD.print(TempVitezka + 0.5*newPos);
     lastPos=newPos;
     }
    boolean buttonIsUp = digitalRead(0);
    if (buttonWasUp && !buttonIsUp) {
      delay(50);
      buttonIsUp = digitalRead(0);
    }
      if (!buttonIsUp)  { LCD.clear(); delay(500); w = 3; TempVitezka = TempVitezka + 0.5*newPos;}

  }
}
