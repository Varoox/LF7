// Aufgabe 2: LED Ein/Aus per kurzer oder langer Tastendruck

const int buttonPin = 2;   // Taster an Pin 2 (intern Pull-Up)
const int ledPin = 13;     // LED an Pin 13

unsigned long buttonPressTime = 0;
unsigned long buttonReleaseTime = 0;
const unsigned long longPressThreshold = 1000; // Schwelle für langen Tastendruck (in ms)
bool lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  bool reading = digitalRead(buttonPin);
  
  // Wenn der Taster gerade gedrückt wird
  if (lastButtonState == HIGH && reading == LOW) {
    buttonPressTime = millis();
    delay(50); // einfacher Entprell-Vorgang
  }
  
  // Wenn der Taster losgelassen wird
  if (lastButtonState == LOW && reading == HIGH) {
    buttonReleaseTime = millis();
    unsigned long pressDuration = buttonReleaseTime - buttonPressTime;
    if (pressDuration < longPressThreshold) {
      // Kurzer Tastendruck → LED einschalten
      digitalWrite(ledPin, HIGH);
    } else {
      // Langer Tastendruck → LED ausschalten
      digitalWrite(ledPin, LOW);
    }
    delay(50); // einfacher Entprell-Vorgang
  }
  
  lastButtonState = reading;
}