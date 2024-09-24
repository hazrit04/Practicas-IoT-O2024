#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int trigPin = 5;
const int echoPin = 18;
#define SOUND_SPEED 0.034

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicia el display OLED, verifica la conexión
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Bucle infinito si falla la inicialización
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Iniciando sensor...");
  display.display();
  delay(2000);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // Mide el tiempo del eco
  distanceCm = duration * SOUND_SPEED / 2; // Calcula la distancia

  // Muestra la distancia en el OLED
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Distancia: ");
  display.print(distanceCm);
  display.println(" cm");
  display.display();

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  delay(1000);
}
