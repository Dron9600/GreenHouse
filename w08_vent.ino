while (w == 8) {
time_poliv = millis();
  
  LCD.setCursor(0, 1);
  LCD.print("Ventilator ");
   LCD.setCursor(16, 0);
  LCD.print("On");
  LCD.setCursor(16, 1);
  LCD.print("Off");
  LCD.setCursor(0, 3);
  LCD.print("Nazad");

  enc1.tick();

  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;  }
  if (newPos < 0 ) { newPos = 0; }
  if (newPos > 3 ) { newPos = 3; }

  if (lastPos != newPos) {
    LCD.setCursor(12, lastPos);
    LCD.print("   ");
    LCD.setCursor(12 , newPos);
    LCD.print("==");
    lastPos = newPos;
    WaitT = millis();
  }

    if (millis() - WaitT > 30000) {LCD.clear(); delay(500); w = 0; }


  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) {
    buttonIsUp = digitalRead(0);
    if (!buttonIsUp  && newPos == 0)  { digitalWrite(RELAY_4, LOW), VentPos = 1; }
    if (!buttonIsUp  && newPos == 1)  { digitalWrite(RELAY_4, HIGH), VentPos = 0; }
    if (!buttonIsUp  && newPos == 3) { LCD.clear(); delay(500); w = 2; }
  }

}
