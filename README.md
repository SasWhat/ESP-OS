🧠 ESP-OS — A Serial Command-Line OS for ESP32
A mini operating system for ESP32 that runs entirely over Serial.
Control Wi-Fi, files, and hardware with simple shell-style commands like ping("google.com"), mkfile("log.txt", "ready"), and digwrite(13, high).

⚡ Features
🖥️ Serial-based command line interface (CLI)

📶 Wi-Fi setup and control using WiFiManager

📁 File system commands using SPIFFS

⚙️ GPIO control: digital I/O, PWM, analog read

🔄 Easily extendable command handler system

💾 Lightweight & user-friendly — fits in under 100 KB

🛠️ Commands
🧠 System
plaintext
Copy
Edit
help()           // List all commands
reboot()         // Restart the ESP32
clear()          // Clear Serial output
uptime()         // Show runtime
free()           // Show free RAM and SPIFFS space
📶 Wi-Fi
plaintext
Copy
Edit
wificonfig()     // Start WiFiManager portal
resetwifi()      // Clear saved Wi-Fi
status()         // Show connection info
disconnect()     // Disconnect from Wi-Fi
scan()           // List nearby networks
ping("host")     // Ping a domain or IP
ip()             // Show IP, gateway, DNS
📁 File System
plaintext
Copy
Edit
mkfile("name","data")   // Create file with text
read("file")            // Read a file
del("file")             // Delete a file
ls()                    // List files
⚙️ GPIO / Hardware
plaintext
Copy
Edit
digwrite(pin, state)    // Digital output: high/low
digread(pin)            // Read digital pin
pwm(pin, value)         // PWM 0–255
analogread(pin)         // Read analog value
📷 Example Session
plaintext
Copy
Edit
wificonfig()
ping("google.com")
mkfile("hello.txt", "Welcome to ESP-OS")
read("hello.txt")
digwrite(2, high)
analogread(34)
📦 Dependencies
Use PlatformIO and make sure this is in platformio.ini:

ini
Copy
Edit
lib_deps =
  tzapu/WiFiManager
  ESP32Ping
🔧 Getting Started
Clone this repo

Upload to your ESP32 board using PlatformIO or Arduino IDE

Open Serial Monitor at 115200

Type help() and start exploring

💡 Roadmap
servo(pin, angle)

tone(pin, freq)

Web-based command GUI (optional)

SPIFFS script runner: run("boot.txt")
