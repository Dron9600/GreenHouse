while (w == 7) {
time_poliv = millis();

if (ObrOt == 99 || ObrOt == 9 ) {LCD.clear();}
  
  LCD.setCursor(0, 1);
  LCD.print("NaSkolkoVkl");
  LCD.setCursor(14, 0);
  LCD.print("30sec");
  LCD.setCursor(14, 1);
  LCD.print(ObrOt);
  LCD.setCursor(14, 2);
  LCD.print("Otkl");
  LCD.setCursor(0 , 3);
  LCD.print("Nazad");

  enc1.tick();
  
  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;  }
  if (newPos > 3) {LCD.clear(); digitalWrite(RELAY_2, HIGH); delay(500); newPos = 0; w = 0; }
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

    if (millis() - WaitT > 600000) {LCD.clear(); delay(500); w = 0; }


  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) {
    buttonIsUp = digitalRead(0);
    if (!buttonIsUp  && newPos == 0)  {
      digitalWrite(RELAY_2, LOW);
      delay(30000); 
      digitalWrite(RELAY_2, HIGH);
    }
    if (!buttonIsUp  && newPos == 1)  {LCD.clear(); delay(500); w = 71;}
    /*  digitalWrite(RELAY_2, LOW);
      nasos = 1;
      vremaNasosa = millis();
    
    
    if (nasos == 1 && millis() - vremaNasosa > 60000){
      digitalWrite(RELAY_2, HIGH);
      nasos = 0;
    }*/
    if (!buttonIsUp  && newPos == 2) {
      LCD.clear();
      digitalWrite(RELAY_2, HIGH);
      ObrOt = 0;
    }
    if (!buttonIsUp  && newPos == 3) {
      LCD.clear();
      delay(500);
      w = 2;
      digitalWrite(RELAY_2, HIGH);
    }
  }

  if(ObrOt > 0){digitalWrite(RELAY_2, LOW); if (millis() - sec > 1000){ObrOt--; sec = millis();};}
  else if(ObrOt <= 1) {digitalWrite(RELAY_2, HIGH);}
  
  while (w == 71) {
    LCD.setCursor(0, 1);
  LCD.print("NaSkolkoVkl");
  enc1.tick();

  if (enc1.isRight()) { newPos++; }
  if (enc1.isLeft()) { newPos--;  }


  if (lastPos != newPos) {
    LCD.clear();
    LCD.setCursor(15, 1);
    LCD.print(Min + 0.5 * newPos);
    lastPos = newPos;
  }
  boolean buttonIsUp = digitalRead(0);
  if (buttonWasUp && !buttonIsUp) {
  if (!buttonIsUp)  { LCD.clear();  delay(500); w = 7; Min = Min + 0.5 * newPos; ObrOt = Min*60; newPos = 0; }
}
}

}
