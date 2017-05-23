#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = "name"; // แก้ชื่อ WiFi Access Point 
const char* password = "pass"; // รหัสผ่าน Access Point
const int port = 12345;

ESP8266WebServer server(port);

const int led = D0;
int state = 0;
String status_led = "OFF";

void Web_index() {
  Serial.println("Index Page");
  server.send(200, "text/html", "<h1>Hello World ESP8266</h1><a href=control>Control Page</a>");
}

void ControlLED(bool a){
  if(a==1){
    digitalWrite(led, !a);
    Serial.println("LED ON");
    status_led = "ON";
  }
 if(a==0){
    digitalWrite(led, !a);
    Serial.println("LED OFF");
    status_led = "OFF";
  }
}

void Web_led() {
  state = server.arg("led").toInt();
  status_led = "ON";
  if (state == 1) 
   ControlLED(1);
  else 
     ControlLED(0);
  
  Web_control();
}
 
void Web_control() {
  Serial.println("Control Page");
  String html = "LED Status = " + status_led;
  server.send(200, "text/html", "LED is " + status_led + "<p><a href=led?led=1><button> ON </button></a><a href=led?led=0><button> OFF </button></a>");
}

void Connect_WIFI()
{
  delay(10);
  Serial.println("");
  Serial.print("Connecting to :"); 
  Serial.println(ssid); 
 
  WiFi.begin(ssid, password); // สั่งให้เชื่อมต่อกับ AP
  
  while (WiFi.status() != WL_CONNECTED) //รอ
  {
    delay(500);
    Serial.print("*");
  }

  //IPAddress local_ip = {192, 168, 31, 129}; //ฟิกค่า IP
  //IPAddress gateway = {192, 168, 31, 1}; //ตั้งค่า IP Gateway
  //IPAddress subnet = {255, 255, 255, 0}; //ตั้งค่า Subnet
  //WiFi.config(local_ip, gateway, subnet); //setค่าไปยังโมดูล
 
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Port: ");
  Serial.println(port);
  pinMode(D0, OUTPUT);
  digitalWrite(led, 1);
  Serial.println("LED Ready");
}

void setup()
{
  Serial.begin(9600); 
  
  Connect_WIFI();
 
  server.on("/led", Web_led);
  server.on("/control", Web_control);
  server.on("/", Web_index);
  server.begin();
  
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}
