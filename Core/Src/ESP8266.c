/*
 * ESP8266.c
 *
 *  Created on: 16-Oct-2021
 *      Author: kani
 */

#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

extern UART_HandleTypeDef huart4;
extern TIM_HandleTypeDef htim14;

uint8_t rx_data[100];
uint8_t data[100];
char *OK_received;
char AT_Commmand[100];
const char ok[4] = "OK\r\n";
char APIrequest[100];
int APIrequest_size;


void uart_transmit(char* tx_data, uint16_t receive_size)
{
	sprintf((char*)data, "%s\r\n",tx_data);
	HAL_UART_Transmit(&huart4, data, strlen((char*)data), 1000);
	HAL_UART_Receive_IT(&huart4, rx_data, receive_size);
}

//If OK received, turn on the greed LED else turn on the red LED
bool ESP8266_Test()
{
	uart_transmit("AT", 11);

	HAL_TIM_Base_Start(&htim14);
	while (__HAL_TIM_GET_COUNTER(&htim14) < 20000)
	{
		OK_received = strstr((const char*)rx_data, ok);
		if (strcmp(OK_received, ok) == 0)
			{
				__HAL_TIM_DISABLE(&htim14);
				HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_SET);
				return true;
			}
	}
	__HAL_TIM_DISABLE(&htim14);
	HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
	return false;
}

//Set to station mode and connect to WiFi
void ESP8266_WiFiSetup(char* SSID, char* password)
{
	HAL_Delay(5000);
	uart_transmit("AT+CWMODE=1", 20);

	HAL_Delay(5000);
	sprintf((char*)AT_Commmand, "AT+CWJAP=%s,%s",SSID, password);
	uart_transmit(AT_Commmand, 90);
}

//Single connection
void TCP_Connect(char* IP, int port)
{
	HAL_Delay(10000);
	uart_transmit("AT+CIPMUX=0", 20);

	HAL_Delay(5000);
	sprintf((char*)AT_Commmand, "AT+CIPSTART=\"TCP\",%s,%d", IP, port);
	uart_transmit(AT_Commmand, 56);
}

//HTTP request
void TS_Write(char* channel_write_key, double sensor_output)
{
	sprintf(APIrequest, "GET /update?key=%s&field1=%lf",channel_write_key,sensor_output);
	HAL_Delay(10000);
	APIrequest_size = strlen (APIrequest) + 2; //+2 for /r/n
	sprintf(AT_Commmand, "AT+CIPSEND=%d", APIrequest_size);
	uart_transmit(AT_Commmand, 22);

	HAL_Delay(5000);
	uart_transmit(APIrequest, 86);
}
