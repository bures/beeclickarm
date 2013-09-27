/*
 * LED.h
 *
 *  Created on: 15. 9. 2013
 *      Author: Tomas Bures <bures@d3s.mff.cuni.cz>
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f4xx.h"
#include <list>

class LED {
public:
	struct Properties {
		GPIO_TypeDef* gpio;
		uint32_t pin;
		uint32_t clk;
	};

	LED(Properties& initProps);
	~LED();

	void on();
	void off();
	void init();

private:
	Properties props;
};

class PulseLED {
public:
	PulseLED(LED& led, int minimalOnTimeTicks);
	~PulseLED();

	void pulse();
	void init();

	static void tickInterruptHandler();

private:
	LED& led;
	int minimalOnTimeTicks;
	int onTicks;

	void tick();

	static std::list<PulseLED*> tickListeners;
};

#endif /* LED_H_ */
