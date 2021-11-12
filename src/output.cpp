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
	//the range of the output
	Range range;
	//whether or not the output should be flipped
	bool flip;
	//sends the pwm output 
	Servo servo;

public:
	/**
	 * basic constructor for Output that just requires pin(other values are set to default)
	 * @param pin the pin you want to control
	 */
	Output(int pin)
	{
		update(pin, Range(1000, 2000), false);
	}
	
	/**
	 * an advanced constructor that allows you to set all parameters of Output
	 */
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