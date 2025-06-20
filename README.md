**ESP-OS** Version-1.0

ESP-OS is a lightweight serial-based command-line operating system for the ESP32 microcontroller. It allows users to interact with the ESP32 over the Serial Monitor using simple shell-like commands. With ESP-OS, you can manage Wi-Fi connections, read and write files to SPIFFS, control GPIOs, and perform system diagnostics.

**Features**

ESP-OS supports serial commands to perform tasks typically done through code. This includes setting up Wi-Fi using WiFiManager, creating and reading files, listing or deleting them, and controlling digital and analog pins. The system is extendable, so new commands can be added as needed.

**Supported Commands

System Commands:**

help() – Lists all available commands

reboot() – Restarts the ESP32

clear() – Clears the Serial screen

uptime() – Shows how long the ESP32 has been running

free() – Displays free RAM and available SPIFFS space

**Wi-Fi Commands:**

wificonfig() – Starts WiFiManager captive portal to connect to a network

resetwifi() – Clears saved Wi-Fi credentials

status() – Displays current SSID, IP, and signal strength

disconnect() – Disconnects from the current Wi-Fi network

scan() – Lists available Wi-Fi networks

ping("host") – Pings a domain or IP address

ip() – Shows the ESP32’s IP address, gateway, and DNS

**File System Commands:**

mkfile("name","text") – Creates a new file and writes text

read("file") – Reads the contents of a file

del("file") – Deletes a specified file

ls() – Lists all files stored in SPIFFS

**GPIO and Hardware Commands:**

digwrite(pin, state) – Sets a digital pin to HIGH or LOW

digread(pin) – Reads the value of a digital pin

pwm(pin, value) – Outputs PWM signal on a pin (value 0 to 255)

analogread(pin) – Reads analog input from a specified pin

Example Session
scss
Copy
Edit
wificonfig()
ping("google.com")
mkfile("log.txt","System ready")
read("log.txt")
digwrite(13, high)
analogread(34)
Dependencies
This project requires the following libraries:

_WiFiManager_

_ESP32Ping_

You can install them via PlatformIO using:
pasting the following code into the platform.ini file

lib_deps =
  tzapu/WiFiManager
  ESP32Ping
  
**How to Use**

Upload the project to an ESP32 board using PlatformIO or Arduino IDE.

Open the Serial Monitor at **115200** baud rate.

Type help() and press Enter to see the list of commands.

Use the commands interactively through the Serial Monitor.

**Future Improvements**

Add servo control using servo(pin, angle)

Add buzzer control using tone(pin, frequency)

Support command scripting with run("script.txt")

Optional web interface for commands

