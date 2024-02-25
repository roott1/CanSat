/*
* Servidor web con ESP32
* Librerias necesarias para conectarnos a un entorno Wifi y poder configurar  
* un servidor WEB
*/
#include <WiFi.h>
#include <WebServer.h>

/* Añade tu SSID & Clave para acceder a tu Wifi */
const char* ssid = "Paulita";  // Tu SSID
const char* password = "27101968";  //Tu Clave

/*
    Declaramos un objeto de la libreria WebServer para poder acceder a sus funciones
    Y como parametro 80, que es el puerto estandar de todos los servicios WEB HTTP
*/
WebServer server(80);

/*
   Declaramos el estado inicial de los LEDs del ESP32
*/
uint8_t LED1pin = 12;
bool LED1Estado = LOW;
uint8_t LED2pin = 5;
bool LED2Estado = LOW;

/*
   Todos las siguientes funciones ejecutan tres tareas:
   1 Cambian de estado las variables  de los LED
   2 Muestran por el monitor Serial de Arduino IDE, informacion relevante al estado de los LED
   3 Actualizan la vista de la pagina del servidor WEB con ESP32, envia al navegador un codigo 200 indican el exito
   de la conexion y llama a otra funcion SendHTML con dos parametros que modificaran la pagina 
   del servidor WEB con Arduino.
*/
void handle_OnConnect() {
  LED1Estado = LOW; // 1
  LED2Estado = LOW; // 1
  Serial.println("GPIO4 Estado: OFF | GPIO5 Estado: OFF"); // 2
  server.send(200, "text/html", SendHTML(LED1Estado, LED2Estado)); // 3
}

void handle_led1on() {
  LED1Estado = HIGH; //1
  Serial.println("GPIO4 Estado: ON"); // 2
  server.send(200, "text/html", SendHTML(true, LED2Estado)); //3
}

void handle_led1off() {
  LED1Estado = LOW;
  Serial.println("GPIO4 Estado: OFF");
  server.send(200, "text/html", SendHTML(false, LED2Estado));
}

void handle_led2on() {
  LED2Estado = HIGH;
  Serial.println("GPIO5 Estado: ON");
  server.send(200, "text/html", SendHTML(LED1Estado, true));
}

void handle_led2off() {
  LED2Estado = LOW;
  Serial.println("GPIO5 Estado: OFF");
  server.send(200, "text/html", SendHTML(LED1Estado, false));
}

void handle_NotFound() {
  server.send(404, "text/plain", "La pagina no existe");
}

/*
   Aqui esta definido todo el HTML y el CSS del servidor WEB con ESP32
*/
String SendHTML(uint8_t led1stat, uint8_t led2stat) {
  // Cabecera de todas las paginas WEB
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head>\n";
  ptr += "<meta charset='utf-8'>\n";
  ptr += "<link rel='icon' href='data:image/svg+xml,<svg xmlns=%22http://www.w3.org/2000/svg%22 viewBox=%220 0 100 100%22><text y=%22.9em%22 font-size=%2290%22>📡</text></svg>'>\n";
  ptr += "<title>Satellite GSn</title>\n";
  ptr += "<link rel='stylesheet' type='text/css' href='estilos.css'>\n";
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
   * Declaracion de la velocidad de comunicacion entre Arduino IDE y ESP32
   * Configura el comportamiento de los pines
   */
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
/*
 * Configuracion de la conexion a la Wifi de tu casa
 */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
/*
 * Para procesar las solicitudes HTTP necesitamos definir el codigo que debe de ejecutar en
 * cada estado. Para ello utilizamos el metodo "on" de la libreria WebServer que hemos 
 * habilitador en la linea 13 de este codigo
 * 1 El primero se ejecuta cuando te conectas al Servidor WEB con ESP32 http://la_ip_del_esp32/
 * 2 Los 4 siguientes procesan los 2 estados que puede tener cada LED ON/OFF
 * 3 El ultimo gestiona los errores por ejemplo si pones http://la_ip_del_esp32/holaquetal
 * esta pagina no existe, por lo tanto actualizara la pagina WEB con un mensaje de error
 */
  server.on("/", handle_OnConnect); // 1
  server.on("/led1on", handle_led1on); // 2
  server.on("/led1off", handle_led1off); // 2
  server.on("/led2on", handle_led2on); // 2
  server.on("/led2off", handle_led2off); // 2
  server.onNotFound(handle_NotFound); // 3
/*
 * Arrancamos el Servicio WEB
 */
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}
/*
 * Para gestionar las la peticiones HTTP es necesario llamar al metodo "handleClient"
 * de la libreria WebServer que se encarga de recibir las peticiones y lanzar las fuciones
 * de callback asociadas tipo "handle_led1on()" "handle_led2on()" etc
 * Tambien ejecutan el cambio de estado de los pines y por lo tanto hacen que los 
 * LEDs se enciendan o apaguen
 */
void loop() {
  server.handleClient();
  if (LED1Estado)
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
  }

  if (LED2Estado)
  {
    digitalWrite(LED2pin, HIGH);
  }
  else
  {
    digitalWrite(LED2pin, LOW);
  }
}