/*
 * UART.h
 *
 *  Created on: 14. 9. 2013
 *      Author: Tomas Bures <bures@d3s.mff.cuni.cz>
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

#include <functional>

class UART {
public:
	typedef std::function<void()> ReadyListener;

	uint8_t recv();
	void send(uint8_t ch);
	bool canSend();
	bool canRecv();
	bool isSendComplete();
	bool isBreakOrError();
	void clearBreakOrError();

	void enableSendReadyEvents();
	void disableSendReadyEvents();
	void setSendReadyListener(ReadyListener sendReadyListener);

	void enableRecvReadyEvents();
	void disableRecvReadyEvents();
	void setRecvReadyListener(ReadyListener recvReadyListener);

	static UART uart2;
	friend void USART2_IRQHandler();

private:
	UART(uint32_t clkGPIO, uint32_t clkUSART, GPIO_TypeDef* gpio, USART_TypeDef* usart, uint16_t pinSourceTX, uint16_t pinSourceRX, uint32_t pinTX, uint32_t pinRX, uint8_t afConfig, uint8_t nvicIRQChannel);
	virtual ~UART();

	void interruptHandler();

	uint32_t clkGPIO, clkUSART;
	GPIO_TypeDef* gpio;
	USART_TypeDef* usart;
	uint16_t pinSourceTX, pinSourceRX;
	uint32_t pinTX, pinRX;
	uint8_t afConfig;
	uint8_t nvicIRQChannel;

	ReadyListener sendReadyListener;
	ReadyListener recvReadyListener;
};

#endif /* UART_H_ */
