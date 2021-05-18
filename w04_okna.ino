while (w == 4) {
time_poliv = millis();
  
  LCD.setCursor(0, 0);
  LCD.print("TempOtkritiya ");
  LCD.setCursor(0, 1);
  LCD.print("TempZakritiya ");
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
    if (!buttonIsUp  && newPos == 0)  { LCD.clear(); delay(500); w = 10;  }
    if (!buttonIsUp  && newPos == 1)  { LCD.clear();  delay(500); w = 11; }
    if (!buttonIsUp  && newPos == 3)  { LCD.clear();  delay(500); w = 1;  }
  }

while (w == 10) {
  LCD.setCursor(0, 0);
  LCD.print("TempOtkritiya ");
  enc1.tick();

  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;  }


  if (lastPos != newPos) {
    LCD.clear();
    LCD.setCursor(15, 0);
    LCD.print(TempOtkr + 0.5 * newPos);
    lastPos = newPos;
  }
  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) { delay(50); buttonIsUp = digitalRead(0); }
  if (!buttonIsUp)  { LCD.clear();  delay(500); w = 4; TempOtkr = TempOtkr + 0.5 * newPos; }
}
while (w == 11) {
    LCD.setCursor(0, 1);
    LCD.print("TempZakritiya ");
    enc1.tick();

  if (enc1.isRight()) { newPos++; }         // если был поворот
  if (enc1.isLeft())  { newPos--; }


     if (lastPos != newPos) {
     LCD.clear();
     LCD.setCursor(15, 1);
     LCD.print(TempZakr + 0.5*newPos);
     lastPos=newPos;
     }
    boolean buttonIsUp = digitalRead(0);
    if (buttonWasUp && !buttonIsUp) {
      delay(50);
      buttonIsUp = digitalRead(0);
    }
      if (!buttonIsUp)  { LCD.clear(); delay(500); w = 4; TempZakr = TempZakr + 0.5*newPos;}

  }
}
