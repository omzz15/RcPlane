#include <Servo.h>
#include <range.cpp>

/**
 * class to hold Servo and Range, plus apply flips if specified 
 */
class Output{
private:
	Range range;
	bool flip;
	Servo servo;
	
public:
	Output(int pin){
		update(pin, Range(1000, 2000), false);	
	}
	Output(int pin, Range range){
		update(pin, range, false);
	}
	Output(int pin, bool flip){
		update(pin, Range(1000, 2000), flip);
	}
	Output(int pin, Range range, bool flip){
		update(pin, range, flip);
	}

	/**
	 * updates all the values of Output(also used to construct instance)
	 * @param pin the pin the Output is attached to
	 * @param range the microsecond range of the Output
	 * @param flip if the servo direction sould be fliped
	 */
	void update(int pin, Range range, bool flip){
		servo = Servo();
		servo.attach(pin);
		this -> range = range;
		this -> flip = flip;
	}

	/**
	 * set the value of the Output
	 * @param pos the set value from -1 to 1
	 */
	void set(double pos){
		servo.writeMicroseconds((int)range.scaleFrom((flip) ? -pos : pos));
	}

	/**
	 * get the set value of the Output
	 * @return set value from -1 to 1
	 */
	double get(){
		return (flip) ? -range.scaleTo(servo.readMicroseconds()) : range.scaleTo(servo.readMicroseconds());
	}
};