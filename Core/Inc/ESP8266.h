/*
 * ESP8266.h
 *
 *  Created on: 16-Oct-2021
 *      Author: kani
 */

#ifndef INC_ESP8266_H_
#define INC_ESP8266_H_

#include <stdbool.h>

struct ESP8266{

	char *SSID;
	char *password;
	char *IP;
	int port;
	char *write_API_key;
	const char ok[4];

};

void uart_transmit(char*, uint16_t);
bool ESP8266_Test(void);
void ESP8266_WiFiSetup(char*, char*);
void TCP_Connect(char*, int);
void TS_Write(char*, double);

#endif /* INC_ESP8266_H_ */
