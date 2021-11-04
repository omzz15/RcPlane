#include <Arduino.h>
#include <Range.cpp>
#include <utils.cpp>

/**
 * data and methods used to get an RC input from a certin pin(using interrupts)
 */
class Input
{
private:
	//the pin you want to read the data from
	int pin;
	//the min, mid, and max values for the input(so the input can be converted to -1 to 1)
	Range inputRange;
	//the max time before the input is declared dead if it does not have any new data
	unsigned int maxTimeout;
	//whether or not the input should be flipped
	bool flip;

	//the start time of a RC pulse
	uint32_t RC_start;
	//the value of the last RC pulse
	volatile uint16_t RC_value;
	//the last time a RC pulse was detected
	long lastUpdateTime;
	//if there is a new pulse that has not been read yet
	bool newData;

	
	void construct(int pin, Range inputRange, unsigned int maxTimeout, bool flip)
	{
		this->pin = pin;
		pinMode(pin, INPUT);
		this->inputRange = inputRange;
		this->maxTimeout = maxTimeout;
		this->flip = flip;
	}

public:
	Input(int pin)
	{
		construct(pin, Range(1000, 2000), 500, false);
	}

	Input(int pin, Range inputRange, unsigned int maxTimeout, bool flip)
	{
		construct(pin, inputRange, maxTimeout, flip);
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
		return Utils::flip(inputRange.scaleTo(getRawValue()), flip);
	}

	bool isAlive()
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