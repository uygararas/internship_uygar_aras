const int LED_PIN = 2;    // Pin number connected to the first LED
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
  while (Serial.available()) {
    String incomingString = Serial.readStringUntil('\n');
    incomingString.trim();

    if (incomingString.equals("ON1")) {
      Serial.print("HIGH1");
      digitalWrite(LED_PIN, HIGH);   // Turn on the first LED
    } else if (incomingString.equals("OFF1")) {
      Serial.print("LOW1");
      digitalWrite(LED_PIN, LOW);
    } else if (incomingString.equals("ON2")) {
      Serial.print("HIGH2");
      digitalWrite(LED_PIN2, HIGH);  // Turn on the second LED

    } else if (incomingString.equals("OFF2")) {
      Serial.print("LOW2");
      digitalWrite(LED_PIN2, LOW);   // Turn off the second LED
  
    } else if (incomingString.equals("ON3")) {
      Serial.print("HIGH3");
      digitalWrite(LED_PIN3, HIGH);  // Turn on the third LED

    } else if (incomingString.equals("OFF3")) {
      Serial.print("LOW3");
      digitalWrite(LED_PIN3, LOW);   // Turn off the third LED

    } else if (incomingString.equals("ON4")) {
      Serial.print("HIGH4");
      digitalWrite(LED_PIN4, HIGH);  // Turn on the fourth LED

    } else if (incomingString.equals("OFF4")) {
      Serial.print("LOW4");
      digitalWrite(LED_PIN4, LOW);   // Turn off the fourth LED

    }
    else{
      Serial.print("LOW4");
      Serial.print("LOW3");
      Serial.print("LOW2");
      Serial.print("LOW1");
    }
  }
}
