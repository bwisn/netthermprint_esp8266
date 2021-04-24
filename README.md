# netthermprint_esp8266
## What it is?
Example usage of libnetthermprint on ESP8266

## What to do?
Create include/config.h file:
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
Connect your printer RX pin to D4 pin on your board.