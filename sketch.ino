#include <WiFi.h>
#include <HTTPClient.h>
#include <math.h>

// Pins
#define TRIG_PIN 5
#define ECHO_PIN 18
#define THERM_PIN 34
#define GREEN_LED 21
#define RED_LED 22
#define BUZZER 23

const char* ssid = "Wokwi-GUEST";
const char* password = "";
// Access Token apni device se replace karein
const char* serverName = "http://demo.thingsboard.io/api/v1/YOUR_ACCESS_TOKEN/telemetry";

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nConnected to Wokwi WiFi!");
}

void loop() {
  // 1. Sensor Readings
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int dist = pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;

  int adc = analogRead(THERM_PIN);
  float voltage = adc * (3.3 / 4095.0);
  float rT = (10000 * voltage) / (3.3 - voltage);
  float tempC = (1.0 / ((log(rT / 10000) / 3950) + (1.0 / 298.15))) - 273.15;

  // 2. Local Logic (Instant)
  if (dist > 0 && dist < 20) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    tone(BUZZER, 1000);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    noTone(BUZZER);
  }

  // 3. Serial Monitor Output
  Serial.printf("Dist: %d cm | Temp: %.2f C\n", dist, tempC);

  // 4. Send to ThingsBoard
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");
    String json = "{\"distance\":" + String(dist) + ", \"temperature\":" + String(tempC) + "}";
    int httpResponseCode = http.POST(json);
    http.end();
  }
  
  delay(1000); // 2 seconds delay
}