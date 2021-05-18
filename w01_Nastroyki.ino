while (w == 1) {

    LCD.setCursor(0, 0);
    LCD.print("ViitezkaKlap");
    LCD.setCursor(0, 1);
    LCD.print("Okna");
    LCD.setCursor(0, 2);
    LCD.print("Ventilator");
    LCD.setCursor(0, 3);
    LCD.print("Nazad");
    enc1.tick();
    
  if (enc1.isRight()) {newPos++;}       
  if (enc1.isLeft()) {newPos--; }
  if (newPos < 0 ){newPos=0;  }
  if (newPos > 3 ){newPos=3;  }

     if (lastPos != newPos) {
      LCD.setCursor(17, lastPos);
      LCD.print("   ");
      LCD.setCursor(17 , newPos);
      LCD.print("-=");
      lastPos = newPos;
      WaitT = millis();
     }
      if (millis() - WaitT > 30000) {LCD.clear(); delay(500); w = 0; }
    
    boolean buttonIsUp = digitalRead(0);
    if (buttonWasUp && !buttonIsUp) {
      delay(20);
      buttonIsUp = digitalRead(0);
      if (!buttonIsUp  && newPos == 0) { LCD.clear(); delay(500); w = 3; }
      if (!buttonIsUp  && newPos == 1) { LCD.clear(); delay(500); w = 4; }
      if (!buttonIsUp  && newPos == 2) { LCD.clear(); delay(500); w = 5; }
      if (!buttonIsUp  && newPos == 3) { LCD.clear(); delay(500); w = 55; }
}
}
