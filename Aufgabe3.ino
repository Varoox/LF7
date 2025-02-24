// Aufgabe 3: Fahrzeugblinker-Simulation

const int buttonPin = 2;  // Taster an Pin 2 (intern Pull-Up)
const int ledPins[5] = {3, 4, 5, 6, 7}; // 5 LEDs an Pins 3 bis 7
const int numLeds = 5;

// Blinkmuster (0-basiert): LED1, LED2, LED3, LED4, LED5, LED5, LED4, LED3, LED2, LED1
const int pattern[] = {0, 1, 2, 3, 4, 4, 3, 2, 1, 0};
const int patternLength = 10;

bool blinkActive = false;
int currentStep = 0;
unsigned long lastStepTime = 0;
const unsigned long stepInterval = 200; // Zeit pro Schritt in ms

// Variablen für Taster-Entprellung
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
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
      // Bei Tasterdruck (LOW)
      if (buttonState == LOW) {
        blinkActive = !blinkActive;  // Blinkerstatus umschalten
        if (blinkActive) {
          currentStep = 0; // Muster von vorne beginnen
        } else {
          // Alle LEDs ausschalten, wenn Blinker deaktiviert wird
          for (int i = 0; i < numLeds; i++) {
            digitalWrite(ledPins[i], LOW);
          }
        }
        delay(200); // kurze Pause zur Vermeidung mehrfacher Auslösungen
      }
    }
  }
  lastButtonState = reading;
  
  // Wenn Blinker aktiv, führe das Muster aus
  if (blinkActive && (millis() - lastStepTime >= stepInterval)) {
    // Schalte alle LEDs aus
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    // Schalte die aktuelle LED im Muster ein
    int ledIndex = pattern[currentStep];
    digitalWrite(ledPins[ledIndex], HIGH);
    
    currentStep = (currentStep + 1) % patternLength;
    lastStepTime = millis();
  }
}