#include <range.cpp>
#include <output.cpp>


class PlaneHardware
{
public:
	//elevator					//pin		//range					//flip
	Output elevator		= Output(1,			Range(1000,1500,200),	false);
	//rudder
	Output rudder 		= Output(2, 		Range(1000,1500,200), 	false);
	//aileron 1
	Output aileron1 	= Output(3, 		Range(1000,1500,200), 	false);
	//aileron 2
	Output aileron2		= Output(4, 		Range(1000,1500,200),	false);
	//throttle 1
	Output throttle1	= Output(5,			Range(1000,1500,200),	false);
	//throttle 2
	Output throttle2	= Output(6, 		Range(1000,1500,200), 	false);
};

class Plane
{
	PlaneHardware planeHardware;

public:
	Plane(PlaneHardware planeHardware){
		this -> planeHardware = planeHardware;
	}

	Plane(){
		planeHardware = PlaneHardware();
	}

	void move(double throttle, double aileron, double elevator, double rudder){
		planeHardware.throttle1.set(throttle);
		planeHardware.throttle2.set(throttle);
		planeHardware.aileron1.set(aileron);
		planeHardware.aileron2.set(-aileron);
		planeHardware.elevator.set(elevator);
		planeHardware.rudder.set(rudder);
	}
};