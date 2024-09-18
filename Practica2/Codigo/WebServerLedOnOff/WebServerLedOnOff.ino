
#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid = "IoT";
const char* password = "1t3s0IoT23";

WiFiServer server(80);

#define LED 2

String estado = "";

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  //Conectando a WiFi
  WiFi.begin(ssid, password);
  // Checa si está conectado
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("La dirección IP es: ");
  Serial.println(WiFi.localIP());
  // Inicio del servidor web
  server.begin();
  Serial.println("Servidor web iniciado.");
}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    Serial.print("Nuevo cliente: ");
    Serial.println(client.remoteIP());
    while(!client.available()){  delay(1); }
    ///////////////////////////////////////
    // Lee la información enviada por el cliente
    String req = client.readStringUntil('\r');
    Serial.println(req);
    // Realiza la petición del cliente
    if (req.indexOf("on2") != -1) { 
      digitalWrite(LED, HIGH);
      estado = "Encendido";
    }
    if (req.indexOf("off2") != -1) { 
      digitalWrite(LED, LOW);
      estado = "Apagado";
    }
    ///////////////////////////////////////
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><meta charset = utf-8></head>");
    client.println("<body><center><font face = 'Arial'>");
      client.println("<h1>Servidor Web con ESP32.</h1>");
      client.println("<h1>Tirzah Peniche Barba</h1>");
      client.println("<h2><font color = '#009900'>Webserver 1.0</font></h2>");
      client.println("<h3>Práctica botón</h3>");
      client.println("<br><br>");
      client.println("<a href = 'on2'><button>Enciende LED</button></a>");
      client.println("<a href = 'off2'><button>Apaga LED</button></a>");
      client.println("<br><br>");
      client.println(estado);
    client.println("</font>");
    client.println("</center>");
    client.println("</body>");
    client.println("</html>");
    Serial.print("Cliente desconectado: ");
    Serial.println(client.remoteIP());
    client.flush();
    client.stop();

}
