// Aufgabe 5: LCD Countdown mit Melodie (Version A: Zahlenanzeige)

#include <LiquidCrystal.h>

// Initialisiere das LCD:
// Anschlüsse: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin = 7;    // Taster an Pin 7 (intern Pull-Up)
const int buzzerPin = 8;    // Summer (Buzzer) an Pin 8

// Variablen zur Taster-Entprellung
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  lcd.begin(16, 2);          // LCD initialisieren (16 Zeichen, 2 Zeilen)
  lcd.clear();
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);
  
  // Entprellung des Tasters
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        startCountdown();
      }
    }
  }
  lastButtonState = reading;
}

void startCountdown() {
  // Countdown von 10 bis 0
  for (int i = 10; i >= 0; i--) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(i); // Anzeige der Zahl (Version A)
    delay(1000);  // 1 Sekunde pro Schritt
  }
  playMelody();
}

void playMelody() {
  // Einfache Melodie (Beispielhafte Tonfolge)
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523}; // Frequenzen in Hz
  int noteDurations[] = {200, 200, 200, 200, 200, 200, 200, 200}; // Dauer in ms
  for (int i = 0; i < 8; i++) {
    tone(buzzerPin, melody[i], noteDurations[i]);
    delay(noteDurations[i] * 1.30);
    noTone(buzzerPin);
  }
}