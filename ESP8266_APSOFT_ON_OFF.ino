#include <ESP8266WiFi.h>

WiFiServer server(80);

void setup(){

  WiFi.mode(WIFI_AP);
  WiFi.softAP("IoT-ESP8266", "12345678");

  server.begin();

  Serial.begin(115200);
  IPAddress HTTPS_ServerIP = WiFi.softAPIP();
  Serial.print("Servidor de IP: ");
  Serial.println(HTTPS_ServerIP);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {

   WiFiClient client = server.available();

   if(!client){
      return;
   }

   Serial.println("Cliente conectado!");
   
  
   String request = client.readStringUntil('\r');

   Serial.println(request);

   if(request.indexOf("/OFF") != -1){
      digitalWrite(2, HIGH);
   }else if(request.indexOf("/ON") != -1){
      digitalWrite(2,LOW);
   }
    
   String resp = "HTTP/1.1 200 OK\r\n";
   resp += "Content-Type: text/html\r\n\r\n";
   resp += "<!DOCTYPR HTML>\r\n<html>\r\n";
   resp += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED ON\" onclick=\"location.href='/ON'\">";
   resp += "<br><br><br>";
   resp += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";
   resp += "</html>\n";

   client.flush();
   client.print(resp);
   delay(1);
   Serial.println("Cliente desconectado");
}