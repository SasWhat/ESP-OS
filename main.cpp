#include <WiFiManager.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ESP32Ping.h>

String input;
unsigned long bootTime;

void help();
void reboot();
void clear();
void uptime();
void freemem();
void wificonfig();
void resetwifi();
void status();
void disconnect();
void scan();
void pingHost(String cmd);
void ip();
void mkfile(String cmd);
void readfile(String cmd);
void deleteFile(String cmd);
void listFiles();
void digwrite(String cmd);
void digread(String cmd);
void pwm(String cmd);
void analogread(String cmd);

void setup() {
  Serial.begin(115200);
  SPIFFS.begin(true);
  bootTime = millis();
  Serial.println("ESP32 Serial OS Ready. Type help()\n");
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim();
    input.toLowerCase();

    if (input.startsWith("help")) help();
    else if (input.startsWith("reboot")) reboot();
    else if (input.startsWith("clear")) clear();
    else if (input.startsWith("uptime")) uptime();
    else if (input.startsWith("free")) freemem();
    else if (input.startsWith("wificonfig")) wificonfig();
    else if (input.startsWith("resetwifi")) resetwifi();
    else if (input.startsWith("status")) status();
    else if (input.startsWith("disconnect")) disconnect();
    else if (input.startsWith("scan")) scan();
    else if (input.startsWith("ping")) pingHost(input);
    else if (input.startsWith("ip")) ip();
    else if (input.startsWith("mkfile")) mkfile(input);
    else if (input.startsWith("read")) readfile(input);
    else if (input.startsWith("del")) deleteFile(input);
    else if (input.startsWith("ls")) listFiles();
    else if (input.startsWith("digwrite")) digwrite(input);
    else if (input.startsWith("digread")) digread(input);
    else if (input.startsWith("pwm")) pwm(input);
    else if (input.startsWith("analogread")) analogread(input);
    else Serial.println("Unknown command. Type help()");
  }
}

void help() {
  Serial.println("\nAvailable Commands:");
  Serial.println("help(), reboot(), clear(), uptime(), free()");
  Serial.println("wificonfig(), resetwifi(), status(), disconnect(), scan(), ping(\"host\"), ip()");
  Serial.println("mkfile(\"file\",\"text\"), read(\"file\"), del(\"file\"), ls()");
  Serial.println("digwrite(pin,state), digread(pin), pwm(pin,value), analogread(pin)");
}

void reboot() {
  Serial.println("Rebooting...");
  delay(1000);
  ESP.restart();
}

void clear() {
  for (int i = 0; i < 50; i++) Serial.println();
}

void uptime() {
  Serial.printf("Uptime: %lu seconds\n", millis() / 1000);
}

void freemem() {
  Serial.printf("Free RAM: %lu bytes\n", ESP.getFreeHeap());
  Serial.printf("SPIFFS: %.2f KB free\n", (float)(SPIFFS.totalBytes() - SPIFFS.usedBytes()) / 1024);
}

void wificonfig() {
  WiFiManager wm;
  if (!wm.autoConnect("ESP32-Setup")) {
    Serial.println("[FAIL] Failed to connect.");
    delay(3000);
    ESP.restart();
  }
  Serial.println("[OK] Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void resetwifi() {
  WiFiManager().resetSettings();
  Serial.println("Wi-Fi settings cleared.");
}

void status() {
  if (WiFi.isConnected()) {
    Serial.printf("Connected to: %s\n", WiFi.SSID().c_str());
    Serial.printf("IP: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());
  } else Serial.println("Not connected.");
}

void disconnect() {
  WiFi.disconnect();
  Serial.println("Disconnected from Wi-Fi.");
}

void scan() {
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; i++) {
    Serial.printf("%d: %s (%d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
}

void pingHost(String cmd) {
  int s = cmd.indexOf('"') + 1;
  int e = cmd.indexOf('"', s);
  String host = cmd.substring(s, e);
  if (Ping.ping(host.c_str())) Serial.printf("Ping success. Avg time: %d ms\n", Ping.averageTime());
  else Serial.println("Ping failed.");
}

void ip() {
  Serial.printf("IP: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("Gateway: %s\n", WiFi.gatewayIP().toString().c_str());
  Serial.printf("DNS: %s\n", WiFi.dnsIP().toString().c_str());
}

void mkfile(String cmd) {
  int s1 = cmd.indexOf('"') + 1;
  int e1 = cmd.indexOf('"', s1);
  int s2 = cmd.indexOf('"', e1 + 1) + 1;
  int e2 = cmd.indexOf('"', s2);
  String name = cmd.substring(s1, e1);
  String content = cmd.substring(s2, e2);
  File f = SPIFFS.open("/" + name, "w");
  if (!f) Serial.println("Failed to create file");
  else {
    f.print(content);
    f.close();
    Serial.println("File created");
  }
}

void readfile(String cmd) {
  int s = cmd.indexOf('"') + 1;
  int e = cmd.indexOf('"', s);
  String name = cmd.substring(s, e);
  File f = SPIFFS.open("/" + name, "r");
  if (!f) Serial.println("Failed to open file");
  else {
    while (f.available()) Serial.write(f.read());
    f.close();
  }
}

void deleteFile(String cmd) {
  int s = cmd.indexOf('"') + 1;
  int e = cmd.indexOf('"', s);
  String name = cmd.substring(s, e);
  if (SPIFFS.remove("/" + name)) Serial.println("File deleted");
  else Serial.println("Failed to delete file");
}

void listFiles() {
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.printf("%s (%d bytes)\n", file.name(), file.size());
    file = root.openNextFile();
  }
}

void digwrite(String cmd) {
  int open = cmd.indexOf('(');
  int comma = cmd.indexOf(',');
  int close = cmd.indexOf(')');
  int pin = cmd.substring(open + 1, comma).toInt();
  String state = cmd.substring(comma + 1, close);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, state.indexOf("high") != -1 ? HIGH : LOW);
  Serial.printf("Pin %d set to %s\n", pin, state.c_str());
}

void digread(String cmd) {
  int open = cmd.indexOf('(');
  int close = cmd.indexOf(')');
  int pin = cmd.substring(open + 1, close).toInt();
  pinMode(pin, INPUT);
  int val = digitalRead(pin);
  Serial.printf("Pin %d reads %d\n", pin, val);
}

void pwm(String cmd) {
  int open = cmd.indexOf('(');
  int comma = cmd.indexOf(',');
  int close = cmd.indexOf(')');
  int pin = cmd.substring(open + 1, comma).toInt();
  int duty = cmd.substring(comma + 1, close).toInt();
  ledcAttachPin(pin, 0);
  ledcSetup(0, 5000, 8);
  ledcWrite(0, duty);
  Serial.printf("PWM set on pin %d with duty %d\n", pin, duty);
}

void analogread(String cmd) {
  int open = cmd.indexOf('(');
  int close = cmd.indexOf(')');
  int pin = cmd.substring(open + 1, close).toInt();
  int val = analogRead(pin);
  Serial.printf("Analog read from pin %d: %d\n", pin, val);
}
