// Aufgabe 4: Minimalalarmsystem

const int buttonPin = 2;       // Taster zum Umschalten der Alarmanlage (intern Pull-Up)
const int alarmLedPin = 13;    // LED auf der Arduino-Platine (zeigt scharf)
const int proximityLedPin = 4; // LED, die bei Annäherung leuchtet
const int sensorPin = 7;       // Näherungssensor (z. B. PIR-Sensor, liefert HIGH bei Bewegung)

bool alarmArmed = false;

// Variablen zur Taster-Entprellung
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(alarmLedPin, OUTPUT);
  pinMode(proximityLedPin, OUTPUT);
  pinMode(sensorPin, INPUT);  // Annahme: Sensor gibt HIGH bei Erkennung aus
  digitalWrite(alarmLedPin, LOW);
  digitalWrite(proximityLedPin, LOW);
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
        alarmArmed = !alarmArmed; // Umschalten der Alarmanlage
        delay(200); // kurze Pause zur Vermeidung mehrfacher Auslösungen
      }
    }
  }
  lastButtonState = reading;
  
  // Wenn Alarmanlage scharf ist:
  if (alarmArmed) {
    digitalWrite(alarmLedPin, HIGH);  // Alarm-LED leuchtet
    // Prüfe den Näherungssensor
    if (digitalRead(sensorPin) == HIGH) {
      digitalWrite(proximityLedPin, HIGH);  // Proximity-LED leuchtet
    } else {
      digitalWrite(proximityLedPin, LOW);
    }
  } else {
    digitalWrite(alarmLedPin, LOW);
    digitalWrite(proximityLedPin, LOW);
  }
}