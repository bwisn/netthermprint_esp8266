# netthermprint_esp8266
## What it is?
Example usage of libnetthermprint

## What to do?
Create config.h file in root directory:
```c++
#ifndef CONFIG_H
#define CONFIG_H
#include <cstdint>
#define WIFI_SSID "changeme"
#define WIFI_PASSWD "hackme"
#define WIFI_SSID2 "changeme"
#define WIFI_PASSWD2 "hackme"

const uint8_t SERVER_IP[4] = {8, 8, 4, 4}; // change to your server ip
#endif
```
Connect your printer RX to D4 pin on your board.