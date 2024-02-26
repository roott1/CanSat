#include <WiFi.h>
#include <WebServer.h>

const int LED = 12;
const char* ssid = "Paulita";
const char* password = "27101968";
WebServer server(80);

/**
  HTML       
**/

String SendHTML() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head>\n";
  ptr += "<meta charset='utf-8'>\n";
  ptr += "<link rel='icon' href='data:image/svg+xml,<svg xmlns=%22http://www.w3.org/2000/svg%22 viewBox=%220 0 100 100%22><text y=%22.9em%22 font-size=%2290%22>📡</text></svg>'>\n";
  ptr += "<title>Satellite GSn</title>\n";
  ptr += "<link rel='stylesheet' type='text/css' href='estilos.css'>\n";
  /**
    CSS      
  **/
  ptr += "<style>\n";
  ptr +=  "body { background-color: #333; }\n";
  ptr +=  "h1 { color: white; text-align: center; background-color: #222; }\n";
  ptr +=  "h2.blue { color: white; background-color: #336; }\n";
  ptr +=  "h2.red { color: white; background-color: #633; }\n";
  ptr +=  "#grid_main { display: grid; grid-template-columns: 50% 1fr; }\n";
  ptr +=  "#grid_2x2 { display: grid; grid-template-columns: 1fr 1fr; }\n";
  ptr +=  "#grid_mini { display: grid; }\n";
  ptr +=  "div.std { border: 3px solid #222; margin: 10px; height: 600px; padding: 0px 10px 0px 10px; border-radius: 10px; }\n";
  ptr +=  "div.small { border: 3px solid #222; margin: 10px; padding: 0px 10px 0px 10px; border-radius: 10px; }\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  /**
    AQUI EMPIEZA EL CUERPO     
  **/
  ptr += "<body>\n";
  ptr +="<h1>Satellite Ground-Station:🔴Transmitiendo</h1>\n";
  ptr +="<div id='grid_main'>\n";
  ptr +="<div class='std'>\n";
  ptr +="<h2 class='red'>📌Posición</h2>\n";
  ptr +="</div>\n";
  ptr +="<div id='grid_2x2'>\n";
  ptr +="<div id='grid_mini'>\n";
  ptr +="<div class='small'>\n";
  ptr +="<h2 class='blue'>♨️Condiciones ambientales</h2>\n";
  ptr +="</div>\n";
  ptr +="<div class='small'>\n";
  ptr +="<h2 class='blue'>📏Métricas</h2>\n";
  ptr +="</div>\n";
  ptr +="</div>\n";
  ptr +="<div class='std'>\n";
  ptr +="<h2 class='red'>🛠️Sistemas<h2>\n";
  ptr +="</div>\n";
  ptr +="</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void setup() {
  /*
  CONFIGURACION DEL WIFI
  */
  pinMode(LED, OUTPUT); 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }
  digitalWrite(LED, HIGH);
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
  /*
  CONFIGURACION DEL SERVER
  */
  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", SendHTML());
  });
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}
