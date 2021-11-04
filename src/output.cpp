#include <Servo.h>
#include <range.cpp>
#include <utils.cpp>
#include <Arduino.h>

/**
 * class to hold Servo and Range, plus apply flips if specified 
 */
class Output
{
private:
	Range range;
	bool flip;
	Servo servo;

public:
	Output(int pin)
	{
		update(pin, Range(1000, 2000), false);
	}
	
	Output(int pin, Range range, bool flip)
	{
		update(pin, range, flip);
	}

	/**
	 * updates all the values of output(also used to construct instance)
	 * @param pin the pin the Output is attached to
	 * @param range the microsecond range of the Output
	 * @param flip if the servo direction sould be fliped
	 */
	void update(int pin, Range range, bool flip)
	{
		pinMode(pin, OUTPUT);
		servo = Servo();
		servo.attach(pin);
		this->range = range;
		this->flip = flip;
	}

	/**
	 * set the value of the output with optional clamping to min and max from range
	 * @param pos the set value from -1 to 1
	 */
	void set(double pos, bool clamp)
	{
		if(clamp)
			pos = Utils::clamp(pos);
		servo.writeMicroseconds((int)range.scaleFrom(Utils::flip(pos, flip)));
	}

	/**
	 * get the set value of the output
	 * @return set value from -1 to 1
	 */
	double get()
	{
		return Utils::flip(range.scaleTo(servo.readMicroseconds()), flip);
	}

	/**
	 * gets the set microseconds of the output
	 * @return the microseconds of the output
	 */
	int getRaw()
	{
		return servo.readMicroseconds();
	}
};