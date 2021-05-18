while (w == 20) {
time_poliv = millis();
  
  LCD.setCursor(0, 0);
  LCD.print("VoSkolkoVkl ");
  LCD.setCursor(0, 1);
  LCD.print("NaSkolkoVkl");
  LCD.setCursor(16, 2);
  LCD.print("Otkl");
  LCD.setCursor(0, 3);
  LCD.print("Nazad");

  enc1.tick();

  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;  }
  if (newPos < 0 ) { newPos = 0; }
  if (newPos > 3 ) { newPos = 3; }

  if (lastPos != newPos) {
    LCD.setCursor(14, lastPos);
    LCD.print("   ");
    LCD.setCursor(14 , newPos);
    LCD.print("==");
    lastPos = newPos;
    WaitT = millis();
  }

    if (millis() - WaitT > 30000) {LCD.clear(); delay(500); w = 0; }


  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) {
    buttonIsUp = digitalRead(0);
    if (!buttonIsUp  && newPos == 0)  {LCD.clear();  delay(500); w = 21; }
    if (!buttonIsUp  && newPos == 1)  {LCD.clear();  delay(500); w = 22; }
    if (!buttonIsUp  && newPos == 2)  {Timer = 2; digitalWrite(RELAY_5, HIGH); }
    if (!buttonIsUp  && newPos == 3) { LCD.clear(); delay(500); w = 55; }
  }

while (w == 21) {
  LCD.setCursor(0, 0);
  LCD.print("VoSkolkoVkl");
  enc1.tick();

  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;  }


  if (lastPos != newPos) {
    LCD.clear();
    LCD.setCursor(14, 0);
    LCD.print(Chasi +  newPos);
    LCD.setCursor(16, 0);
    LCD.print("h");
    lastPos = newPos;
  }
  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) { delay(50); buttonIsUp = digitalRead(0); }
  if (!buttonIsUp)  { LCD.clear();  delay(100); w = 20; TimeSveta = millis(); svet = 1; Timer = 1; Chasi = Chasi +  newPos; }
}

while (w == 23) {
  LCD.setCursor(0, 0);
  LCD.print("VoSkolkoVkl");
  enc1.tick();

  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;  }


  if (lastPos != newPos) {
    LCD.clear();
    LCD.setCursor(16, 0);
    LCD.print(Minuti +  5*newPos);
    LCD.setCursor(18, 0);
    LCD.print("m");
    lastPos = newPos;
  }
  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) { delay(50); buttonIsUp = digitalRead(0); }
  if (!buttonIsUp)  { LCD.clear();  delay(500); w = 20; TimeSveta = millis(); svet = 1; Minuti = Minuti +  5*newPos; }
}

while (w == 22) {
  LCD.setCursor(0, 1);
  LCD.print("NaSkolVkl");
  enc1.tick();

  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;  }


  if (lastPos != newPos) {
    LCD.clear();
    LCD.setCursor(15, 1);
    LCD.print(TimeNa + 0.5 * newPos);
    lastPos = newPos;
  }
  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) { delay(50); buttonIsUp = digitalRead(0); }
  if (!buttonIsUp)  { LCD.clear();  delay(500); w = 20; Timer = 1; TimeSveta = millis(); NaSkolVkl = (TimeNa + 0.5 * newPos)*3600000 ; svet = 1; TimeNa = TimeNa + 0.5 * newPos; }
}
}
}
