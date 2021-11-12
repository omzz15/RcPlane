#include <range.cpp>
#include <output.cpp>
#include <utils.cpp>

/**
 * class to hold all the settings for the plane
 */ 
class PlaneSettings{
public:
	bool flipThrottle = false;
	bool flipRoll = false;
	bool flipPitch = false;
	bool flipHeading = false;
	bool flipFlaps = false;
};

/**
 * class to hold all the hardware for the plane(holds all the Outputs)
 */
class PlaneHardware
{
public:
	//elevator					//pin		//range					//flip
	Output elevator = Output(1, Range(1000, 1500, 200), false);
	//rudder
	Output rudder = Output(2, Range(1000, 1500, 200), false);
	//aileron 1(usually the left one)
	Output aileron1 = Output(3, Range(1000, 1500, 200), false);
	//aileron 2
	Output aileron2 = Output(4, Range(1000, 1500, 200), false);
	//throttle 1(usually the right one)
	Output throttle1 = Output(5, Range(1000, 1500, 200), false);
	//throttle 2
	Output throttle2 = Output(6, Range(1000, 1500, 200), false);
};

/**
 * class that stores and controls eveything for the plane
 */
class Plane
{
private:
	//hardware for the plane
	PlaneHardware hardware;
	//settings for the plane
	PlaneSettings settings;

public:
	/**
	 * constructor that allows you to use custom settings and harware to make a plane
	 * @param hardware the hardware you want to use
	 * @param settings the settings you want to use
	 */
	Plane(PlaneHardware hardware, PlaneSettings settings)
	{
		this->hardware = hardware;
		this->settings = settings;
	}

	/**
	 * constructor that uses the default values for hardware and settings
	 */
	Plane()
	{
		hardware = PlaneHardware();
		settings = PlaneSettings();
	}

	/**
	 * sets all the plane's control surfaces and motors based on input parameters
	 * @param throttle the throttle(controls speed) of the plane: -1 to 1
	 * @param roll how much you want the plane to roll: -1 to 1
	 * @param pitch how much you want the plane to pitch: -1 to 1
	 * @param heading how fast you want the heading of the plane to change: -1 to 1
	 */
	void move(double throttle, double roll, double pitch, double heading, double flaps)
	{
		throttle = Utils::flip(throttle, settings.flipThrottle);
		roll = Utils::flip(roll, settings.flipRoll);
		pitch = Utils::flip(pitch, settings.flipPitch);
		heading = Utils::flip(heading, settings.flipHeading);
		flaps = Utils::flip(flaps, settings.flipFlaps);

		hardware.throttle1.set(throttle + heading, true);
		hardware.throttle2.set(throttle - heading, true);
		hardware.aileron1.set(pitch + roll + flaps, true);
		hardware.aileron2.set(pitch - roll + flaps, true);
		hardware.elevator.set(pitch, true);
		hardware.rudder.set(heading, true);
	}
};