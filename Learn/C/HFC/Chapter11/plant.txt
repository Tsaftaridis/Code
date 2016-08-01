// setup variables
const int analogPin = 0;
const int LED = 13;

// sensor data
int value = 0;
bool was_thirsty = 1;

// variables for blinking without delay
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup()
{
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  value = analogRead(analogPin);
  
  if(value > 800)
  {
    if(was_thirsty)
    { 
      Serial.println("Thank you, Seymour!");
      was_thirsty = 0;
      digitalWrite(LED, LOW);
    }
  }
    
  else
  {
    Serial.println("FEED ME!");
    blink_fn();
    was_thirsty = 1;
  }
  delay(1000);
}

void blink_fn()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
  }

  if(ledState == LOW)
  {
    ledState = HIGH;
  }
  else
  {
    ledState = LOW;
  }

  digitalWrite(LED, ledState);
}