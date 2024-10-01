#include <Wire.h>                 // Librería para la comunicación I2C
#include <Adafruit_GFX.h>          // Librería gráfica para manejar displays
#include <Adafruit_SSD1306.h>      // Librería para el display OLED SSD1306
#include <Adafruit_Sensor.h>       // Librería base para sensores de Adafruit
#include <DHT.h>   

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  dht.begin();

  // Inicializar el display OLED y verificar si está conectado correctamente
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                     // Bucle infinito si falla el OLED
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  delay(5000);                     // Esperar 5 segundos entre lecturas

  // Leer temperatura y humedad desde el sensor DHT
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Mostrar los valores de temperatura y humedad en el monitor serial
  Serial.println("Temperatura:");
  Serial.println(t);
  Serial.println("Humedad:");
  Serial.println(h);

  // Verificar si las lecturas son válidas
  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo al leer datos del sensor DHT1!");
  }

  // Limpiar el display antes de actualizarlo
  display.clearDisplay();
  
  // Mostrar la temperatura en el display OLED
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temperatura: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(t);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);              // Habilitar el conjunto de caracteres CP437 para el símbolo de grados
  display.write(167);               // Mostrar el símbolo de grados
  display.setTextSize(2);
  display.print("C");

  // Mostrar la humedad en el display OLED
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humedad: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h);
  display.print(" %");
  
  display.display();
}
