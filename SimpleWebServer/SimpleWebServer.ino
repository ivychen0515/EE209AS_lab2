#include <ESP8266WiFi.h>

WiFiServer server(80); //Initialize the server on Port 80
const short int LED_PIN = 16;
String html;
void setup() {

  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
  WiFi.softAP("BattleShip", "12345678"); // Provide the (SSID, password); .
  server.begin(); // Start the HTTP Server

  Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
  IPAddress HTTPS_ServerIP = WiFi.softAPIP(); // Obtain the IP of the Server
  Serial.print("Server IP is: "); // Print the IP to the monitor window
  Serial.println(HTTPS_ServerIP);


  pinMode(LED_PIN, OUTPUT); //GPIO16 is an OUTPUT pin;
  digitalWrite(LED_PIN, LOW); //Initial state is ON

  html = setupHtml();// Initial the HTML file
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  //Looking under the hood
  Serial.println("Somebody has connected :)");

  //Read what the browser has sent into a String class and print the request to the monitor
  String request = client.readStringUntil('\r');
  //Looking under the hood
  Serial.println(request);


  //coding according to each senarial
  if (request.indexOf("/OFF") != -1) {
    digitalWrite(LED_PIN, HIGH);
  }
  else if (request.indexOf("/ON") != -1) {
    digitalWrite(LED_PIN, LOW);
  }



  //Serve the HTML document to the browser.

  client.flush(); //clear previous info in the stream
  client.print(html); // Send the response to the client
  delay(1);
  Serial.println("Client disonnected"); //Looking under the hood

}



String setupHtml() {
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<head><style>.button{";
  s += "background-color: #4CAF50;";
  s += "border: none;color: white;padding: 16px 32px;text-align: center;text-decoration: none;";
  s += "display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;";
  s += "-webkit-transition-duration: 0.4s; /* Safari */ transition-duration: 0.4s;}";

  s += ".green {  background-color: white;  color: black; border: 2px solid #4CAF50;}/*green*/";
  s += ".green:hover {  background-color: #4CAF50;  color: white;}";
  s += ".blue {  background-color: white;  color: black; border: 2px solid #008CBA;} /* Blue */";
  s += ".blue:hover {  background-color: #008CBA;  color: white;}";
  s += ".red {  background-color: white;  color: black; border: 2px solid #f44336;} /* Red */";
  s += ".red:hover {  background-color: #f44336;  color: white;}";

  //s += ".button2 {background-color: #008CBA;} /* Blue */";
  //s += ".button3 {background-color: #f44336;} /* Red */";

  s += "</style></head>";


  //s += "<br><input type =\"button\" name=\"b1\" value=\"Turn LED ON\" onclick=\"location.href='/ON'\">";
  //s += "<br><br><br>";
  //s += "<input type =\"button\" name=\"b1\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";


  s += "<a href=\"/ON\" class=\"button green\">Turn LED ON</a><br><br><br>";
  s += "<a href=\"/OFF\" class=\"button red\">Turn LED OFF</a>";
  s += "</html>\n";

  return s;
}

