#include <plane.cpp>
#include <imu.cpp>
#include <controller.cpp>

class ManagerSettings{
public:
    //channel assign
    int throttleCH = 3;
    int rollCH = 1;
    int pitchCH = 2;
    int headingCH = 4;
    int flapsCH = 6;
    int functionCH = 5;
};

class Manager{
    Plane plane;
    Imu imu;
    Controller controller;
    ManagerSettings settings;

    void construct(ManagerSettings settings, Plane plane, Controller controller, Imu imu){
        this->settings = settings;
        this->imu = imu;
        this->controller = controller;
        this->plane = plane;
    }

public:
    Manager(){
        construct(ManagerSettings(), Plane(), Controller(), Imu());
    }
    Manager(ManagerSettings settings){
        construct(settings, Plane(), Controller(), Imu());
    }
    Manager(ManagerSettings settings, Plane plane, Controller controller, Imu imu){
        construct(settings, plane, controller, imu);
    }
};