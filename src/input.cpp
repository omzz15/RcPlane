#include <Arduino.h>
#include <Range.cpp>

class Input
{
private:
	int pin;
	Range inputRange;
	unsigned int maxTimeout;

	uint32_t RC_start;
	volatile uint16_t RC_value = 0;
	long lastUpdateTime;
	bool newData;

	void construct(int pin, Range inputRange, unsigned int maxTimeout)
	{
		this->pin = pin;
		pinMode(pin, INPUT);
		this->inputRange = inputRange;
		this->maxTimeout = maxTimeout;
	}

public:
	Input(int pin)
	{
		construct(pin, Range(1000, 2000), 500);
	}

	Input(int pin, Range inputRange, unsigned int maxTimeout)
	{
		construct(pin, inputRange, maxTimeout);
	}

	int getPin()
	{
		return pin;
	}

	void calcInput()
	{
		if (digitalRead(pin) == HIGH)
		{
			RC_start = micros();
			lastUpdateTime = millis();
		}
		else
		{
			RC_value = (uint16_t)(micros() - RC_start);
			newData = true;
		}
	}

	int getRawValue()
	{
		newData = false;
		return RC_value;
	}

	double getValue()
	{
		return inputRange.scaleTo(getRawValue());
	}

	bool isAvalible()
	{
		return (millis() - lastUpdateTime) <= maxTimeout;
	}

	bool RCStarted()
	{
		return RC_value != 0;
	}

	bool hasNewData()
	{
		return newData;
	}
};