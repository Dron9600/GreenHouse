while (w == 5) {
time_poliv = millis();
  
  LCD.setCursor(0, 0);
  LCD.print("TempVkl ");

  enc1.tick();
    
  if (enc1.isRight()) {newPos++;}       
  if (enc1.isLeft()) {newPos--; }

 if (lastPos != newPos) {
     LCD.clear();
     LCD.setCursor(12, 0);
     LCD.print(VentilatorT + 0.5 * newPos);
     lastPos=newPos;
     WaitT = millis();
     }

    if (millis() - WaitT > 30000) {LCD.clear(); delay(500); w = 0; }

     
    boolean buttonIsUp = digitalRead(0);
    if (buttonWasUp && !buttonIsUp) {
      delay(50);
      buttonIsUp = digitalRead(0);    
    }
      if (!buttonIsUp)  { LCD.clear(); delay(500); w = 1; VentilatorT = VentilatorT + 0.5 * newPos;}
  
}
