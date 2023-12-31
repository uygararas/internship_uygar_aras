const int LED_PIN = 2;  
const int LED_PIN2 = 3;   // Pin number connected to the second LED
const int LED_PIN3 = 4;   // Pin number connected to the third LED
const int LED_PIN4 = 5;   // Pin number connected to the fourth LED

void setup() {
  pinMode(LED_PIN, OUTPUT);   // Set the first LED pin as output
  pinMode(LED_PIN2, OUTPUT);  // Set the second LED pin as output
  pinMode(LED_PIN3, OUTPUT);  // Set the third LED pin as output
  pinMode(LED_PIN4, OUTPUT);  // Set the fourth LED pin as output
  
  Serial.begin(9600);         // Start serial communication
}
void loop() {
  // Print the status of each LED
  Serial.print(digitalRead(LED_PIN) == HIGH ? "HIGH1" : "LOW1");
  Serial.print(digitalRead(LED_PIN2) == HIGH ? "HIGH2" : "LOW2");
  Serial.print(digitalRead(LED_PIN3) == HIGH ? "HIGH3" : "LOW3");
  Serial.println(digitalRead(LED_PIN4) == HIGH ? "HIGH4" : "LOW4");

  while (Serial.available()) {
    String incomingString = Serial.readStringUntil('\n');
    incomingString.trim();

    if (incomingString.equals("ON1")) {
      digitalWrite(LED_PIN, HIGH); // Turn ON LED
    } else if (incomingString.equals("OFF1")) {
      digitalWrite(LED_PIN, LOW);  // Turn OFF LED
    } else if (incomingString.equals("ON2")) {
      digitalWrite(LED_PIN2, HIGH); // Turn ON LED
    } else if (incomingString.equals("OFF2")) {
      digitalWrite(LED_PIN2, LOW);  // Turn OFF LED
    } else if (incomingString.equals("ON3")) {
      digitalWrite(LED_PIN3, HIGH); // Turn ON LED
    } else if (incomingString.equals("OFF3")) {
      digitalWrite(LED_PIN3, LOW);  // Turn OFF LED
    } else if (incomingString.equals("ON4")) {
      digitalWrite(LED_PIN4, HIGH); // Turn ON LED
    } else if (incomingString.equals("OFF4")) {
      digitalWrite(LED_PIN4, LOW);  // Turn OFF LED
    }
  }
}
