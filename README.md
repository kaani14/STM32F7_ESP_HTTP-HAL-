# STM32F7_ESP_HTTP-HAL-

# Description

Send dummy sensor data using HTTP request to Thingspeak using ESP8266 and STM32F767ZI. The ESP sends HTTP request to ThingSpeak channel. Before  initializing the ESP, the MCU sends an "AT" command and waits for "OK" as a reply. If OK is received, the green LED on the board is turned on. Else, the red LED is turned on after 5 seconds.

# Connections

**STM32F767ZI**  | **ESP-8266**
------------- | -------------
PC11  | Tx
PA0  | Rx
3.3V  | EN / CH_PD


# User files

* **ESP8266.h**: Structure and function declaration

* **ESP8266.c**: Definition of functions to communicate with ESP-8266. The file has functions that tests the ESP, connects to WiFi and sends HTTP request.
