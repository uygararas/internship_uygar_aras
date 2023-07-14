const int LED_PIN =  2;  // Pin number connected to the LED

void setup() {
  pinMode(LED_PIN, OUTPUT);     // Set the LED pin as output
  Serial.begin(9600);           // Start serial communication
    Serial.println("ARDUINO");
}

void loop() {

  while (Serial.available()) {
    String incomingString = Serial.readStringUntil('\n');
    incomingString.trim();
    if (incomingString.equals("ON")) {
      digitalWrite(LED_PIN, HIGH);   // Turn on the LED
    }
    else if (incomingString.equals("OFF")) {
      digitalWrite(LED_PIN, LOW);    // Turn off the LED
    }
  }
}
