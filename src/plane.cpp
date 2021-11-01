#include <range.cpp>
#include <output.cpp>

class PlaneHardware
{
public:
	//elevator					//pin		//range					//flip
	Output elevator = Output(1, Range(1000, 1500, 200), false);
	//rudder
	Output rudder = Output(2, Range(1000, 1500, 200), false);
	//aileron 1
	Output aileron1 = Output(3, Range(1000, 1500, 200), false);
	//aileron 2
	Output aileron2 = Output(4, Range(1000, 1500, 200), false);
	//throttle 1
	Output throttle1 = Output(5, Range(1000, 1500, 200), false);
	//throttle 2
	Output throttle2 = Output(6, Range(1000, 1500, 200), false);
};

class Plane
{
private:
	PlaneHardware hardware;

public:
	Plane(PlaneHardware hardware)
	{
		this->hardware = hardware;
	}

	Plane()
	{
		hardware = PlaneHardware();
	}

	/**
	 * sets all the plane's control surfaces and motors based on input parameters
	 * @param throttle the throttle(controls speed) of the plane: -1 to 1
	 * @param aileron the aileron(controls roll) of the plane: -1 to 1
	 * @param elevator the elevator(controls pitch) of the plane: -1 to 1
	 * @param rudder the rudder(controls heading) of the plane: -1 to 1
	 */
	void move(double throttle, double aileron, double elevator, double rudder)
	{
		hardware.throttle1.set(throttle);
		hardware.throttle2.set(throttle);
		hardware.aileron1.set(aileron);
		hardware.aileron2.set(-aileron);
		hardware.elevator.set(elevator);
		hardware.rudder.set(rudder);
	}
};