#include <ESP8266WiFi.h>

#define MANUAL 5      //D1
#define DO 4          //D2
#define RE 0          //D3
#define MI 2          //D4
#define FA 14         //D5
#define SO 12         //D6
#define LA 13         //D7

//BUILTIN_LED is 16

WiFiServer server(80); //Initialize the server on Port 80
const short int LED_PIN = 2;
const int high_low_pause = 50;
String html;

void setup() {
  pinMode(DO, OUTPUT);
  pinMode(RE, OUTPUT);
  pinMode(MI, OUTPUT);
  pinMode(FA, OUTPUT);
  pinMode(SO, OUTPUT);
  pinMode(LA, OUTPUT);
  pinMode(MANUAL, OUTPUT);
  //WIFI configuration
  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
  WiFi.softAP("BattleShip", "12345678"); // Provide the (SSID, password); .
  server.begin(); // Start the HTTP Server

  Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
  IPAddress HTTPS_ServerIP = WiFi.softAPIP(); // Obtain the IP of the Server
  Serial.print("Server IP is: "); // Print the IP to the monitor window
  Serial.println(HTTPS_ServerIP);


  pinMode(LED_PIN, OUTPUT); //GPIO16 is an OUTPUT pin;
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(LED_PIN, LOW); //Initial state is ON
  digitalWrite(DO, LOW); //Initial state 
  digitalWrite(RE, LOW); //Initial state 
  digitalWrite(MI, LOW); //Initial state
  digitalWrite(FA, LOW); //Initial state
  digitalWrite(SO, LOW); //Initial state
  digitalWrite(LA, LOW); //Initial state
  digitalWrite(BUILTIN_LED, HIGH); //Initial sound state is OFF

  html = setupHtml();// Initial the HTML file

}

void loop() {

  //wifi setup
  wifiSetup();

  //Sent out the signal to slaves
  Do();
  delay(500);
  Re();
  delay(500);
}



void Do() {
  digitalWrite(DO, HIGH);
  digitalWrite(BUILTIN_LED, LOW);
  delay(high_low_pause);
  digitalWrite(DO, LOW);
  digitalWrite(BUILTIN_LED, HIGH);
}

void Re() {
  digitalWrite(RE, HIGH);
  digitalWrite(BUILTIN_LED, LOW);
  delay(high_low_pause);
  digitalWrite(RE, LOW);
  digitalWrite(BUILTIN_LED, HIGH);
}

void Mi() {
  digitalWrite(MI, HIGH);
  digitalWrite(BUILTIN_LED, LOW);
  delay(high_low_pause);
  digitalWrite(MI, LOW);
  digitalWrite(BUILTIN_LED, HIGH);
}

void Fa() {
  digitalWrite(FA, HIGH);
  digitalWrite(BUILTIN_LED, LOW);
  delay(high_low_pause);
  digitalWrite(FA, LOW);
  digitalWrite(BUILTIN_LED, HIGH);
}

void So() {
  digitalWrite(SO, HIGH);
  digitalWrite(BUILTIN_LED, LOW);
  delay(high_low_pause);
  digitalWrite(SO, LOW);
  digitalWrite(BUILTIN_LED, HIGH);
}

void La() {
  digitalWrite(LA, HIGH);
  digitalWrite(BUILTIN_LED, LOW);
  delay(high_low_pause);
  digitalWrite(LA, LOW);
  digitalWrite(BUILTIN_LED, HIGH);
}

void playSound1(){
  Do();
  Do();
  So();
  So();
  La();
  La();
  So();
  delay(high_low_pause);
  Fa();
  Fa();
  Mi();
  Mi();
  Re();
  Re();
  Do();
  delay(high_low_pause);
  return;
}

void wifiSetup() {
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
  if (request.indexOf("/MANUALLY") != -1) {
    Serial.println("1");
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(MANUAL, HIGH);
  }
  else if (request.indexOf("/AUTO") != -1) {
    Serial.println("2");
    digitalWrite(LED_PIN, LOW);
    digitalWrite(MANUAL, LOW);
    playSound1();
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


  //s += "<br><input type =\"button\" name=\"b1\" value=\"MANUALLY ON\" onclick=\"location.href='/MANUALLY'\">";
  //s += "<br><br><br>";
  //s += "<input type =\"button\" name=\"b1\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";


  s += "<a href=\"/MANUALLY\" class=\"button green\">Manual On</a><br><br><br>";
  s += "<a href=\"/AUTO\" class=\"button red\">AUTO</a>";
  s += "</html>\n";

  return s;
}

