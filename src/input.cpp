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

	/**
	 * sets all the variables and enables the pin as an input
	 * @param pin the pin that the input should read
	 * @param inputRange the range of the input(so it can be scaled to -1 to 1)
	 * @param maxTimeout the max time before the input is declared dead if no pulse is detected
	 * @param flip whether or not you want the input to be flipped
	 */
	void construct(int pin, Range inputRange, unsigned int maxTimeout, bool flip)
	{
		this->pin = pin;
		pinMode(pin, INPUT);
		this->inputRange = inputRange;
		this->maxTimeout = maxTimeout;
		this->flip = flip;
	}

public:
	/**
	 * a basic Input constructor that just requires pin - all other values are set to default
	 * @param pin the pin you want to get input from
	 */
	Input(int pin)
	{
		construct(pin, Range(1000, 2000), 500, false);
	}

	/**
	 * a more advanced Input constructor that allows you to set all parameters
	 * @param pin the pin that the input should read
	 * @param inputRange the range of the input(so it can be scaled to -1 to 1)
	 * @param maxTimeout the max time before the input is declared dead if no pulse is detected
	 * @param flip whether or not you want the input to be flipped
	 */
	Input(int pin, Range inputRange, unsigned int maxTimeout, bool flip)
	{
		construct(pin, inputRange, maxTimeout, flip);
	}

	/**
	 * returns the pin in the pin variable(used to enableInterrupt)
	 * @return the pin 
	 */
	int getPin()
	{
		return pin;
	}

	/**
	 * method to calculate and store(in RC_value) how long a input pulse is(should be attached to an interrupt on pin change)
	 */
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

	/**
	 * gives you the raw microsecond value of the last pulse
	 * @return the raw microsecond value
	 */
	int getRawValue()
	{
		newData = false;
		return RC_value;
	}

	/**
	 * gives you the scaled and flipped(if flip is true) value of the last pulse(from -1 to 1)
	 * @return formated value of last pulse
	 */
	double getValue()
	{
		return Utils::flip(inputRange.scaleTo(getRawValue()), flip);
	}

	/**
	 * if the input has had a pulse before maxTimeout
	 * @return if the input is alive
	 */
	bool isAlive()
	{
		return (millis() - lastUpdateTime) <= maxTimeout;
	}

	/**
	 * if the Input has ever recived a pulse since start(was the input ever connected)
	 * @return if the input has ever recived a pulse
	 */
	bool RCStarted()
	{
		return RC_value != 0;
	}

	/**
	 * if there is new data(another pulse) since the last time you called getValue or getRawValue
	 * @return if there is new data
	 */
	bool hasNewData()
	{
		return newData;
	}
};