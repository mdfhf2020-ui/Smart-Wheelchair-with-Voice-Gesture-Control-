 // Include required libraries
 #include <WiFi.h>
 #include <WebServer.h>
 // SSID and Password for your ESP Access Point
 const char* ssid = "Robot Wifi";
 const char* password = "87654321";
 // Define motor control pins
 #define ENA 32
 #define IN_1 33
 #define IN_2 25
 #define IN_3 26
 #define IN_4 27
 // Enable/speed motors Right
 // L298N IN1 motor Right
 // L298N IN2 motor Right
 // L298N IN3 motor Left
 // L298N IN4 motor Left
 #define ENB 14 // Enable/speed motors Left
 #define Light 16 // Light control
 String command;
 // String to store app command state
 int speedCar = 150; // Default speed (0 to 255)
 int speed_low = 60; // Reduced speed for turning
 WebServer server(80); // Create a web server on port 80

void rotateForSeconds(int seconds, int direction);
 void setup() {
 Serial.begin(115200);
 // Set pin modes
 pinMode(ENA, OUTPUT);
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
 pinMode(ENB, OUTPUT);
 pinMode(Light, OUTPUT);
 // Set up Wi-Fi Access Point
 WiFi.softAP(ssid, password);
 // Display the IP address
 IPAddress myIP = WiFi.softAPIP();
 Serial.print("AP IP address: ");
 Serial.println(myIP);
 // Start the web server and set up routes
 server.on("/", HTTP_handleRoot);
 server.onNotFound(HTTP_handleRoot);
 server.begin();
 }
 void loop() {
 server.handleClient(); // Handle client requests
 // Process the command
 command = server.arg("State");
 if (command == "F") goForward();
 
else if (command == "B") goBack();
 else if (command == "L") goLeft();
 else if (command == "R") goRight();
 else if (command == "X") goLeftCus();
 else if (command == "Y") goRightCus();
 else if (command == "0") speedCar = 100;
 else if (command == "1") speedCar = 120;
 else if (command == "2") speedCar = 140;
 else if (command == "3") speedCar = 160;
 else if (command == "4") speedCar = 180;
 else if (command == "5") speedCar = 200;
 else if (command == "6") speedCar = 215;
 else if (command == "7") speedCar = 230;
 else if (command == "8") speedCar = 240;
 else if (command == "9") speedCar = 255;
 else if (command == "S") stopRobot();
 }
 void HTTP_handleRoot() {
 if (server.hasArg("State")) {
 Serial.println(server.arg("State"));
 }
 server.send(200, "text/html", "");
 delay(1);
 }
 // Motor control functions
 void goForward() {
 digitalWrite(IN_1, HIGH);
 digitalWrite(IN_2, LOW);
 analogWrite(ENA, speedCar);
 digitalWrite(IN_3, LOW);
 digitalWrite(IN_4, HIGH);
 
analogWrite(ENB, speedCar);
 }
 void goBack() {
 digitalWrite(IN_1, LOW);
 digitalWrite(IN_2, HIGH);
 analogWrite(ENA, speedCar);
 digitalWrite(IN_3, HIGH);
 digitalWrite(IN_4, LOW);
 analogWrite(ENB, speedCar);
 }
 void goRight() {
 digitalWrite(IN_1, LOW);
 digitalWrite(IN_2, HIGH);
 analogWrite(ENA, speedCar);
 digitalWrite(IN_3, LOW);
 digitalWrite(IN_4, HIGH);
 analogWrite(ENB, speedCar);
 }
 void goLeft() {
 digitalWrite(IN_1, HIGH);
 digitalWrite(IN_2, LOW);
 analogWrite(ENA, speedCar);
 digitalWrite(IN_3, HIGH);
 digitalWrite(IN_4, LOW);
 analogWrite(ENB, speedCar);
 }
 void goLeftCus() {
 
digitalWrite(IN_1, HIGH);
 digitalWrite(IN_2, LOW);
 analogWrite(ENA, 120);
 digitalWrite(IN_3, HIGH);
 digitalWrite(IN_4, LOW);
 analogWrite(ENB, 120);
 }
 void goRightCus() {
 digitalWrite(IN_1, LOW);
 digitalWrite(IN_2, HIGH);
 analogWrite(ENA, 120);
 digitalWrite(IN_3, LOW);
 digitalWrite(IN_4, HIGH);
 analogWrite(ENB, 120);
 }
 void stopRobot() {
 digitalWrite(IN_1, LOW);
 digitalWrite(IN_2, LOW);
 analogWrite(ENA, speedCar);
 digitalWrite(IN_3, LOW);
 digitalWrite(IN_4, LOW);
 analogWrite(ENB, speedCar);
 }
