#include <input.cpp>

class Controller
{
public:
    int maxTimeout = 500;
    //ch 1              //pin   //range                 //max timeout
    Input CH1 = Input(9, Range(1000, 1500, 2000), maxTimeout);
    //ch 2
    Input CH2 = Input(11, Range(1000, 1500, 2000), maxTimeout);
    //ch 3
    Input CH3 = Input(10, Range(1000, 1500, 2000), maxTimeout);
    //ch 4
    Input CH4 = Input(13, Range(1000, 1500, 2000), maxTimeout);
    //ch 5
    Input CH5 = Input(12, Range(1000, 1500, 2000), maxTimeout);
    //ch 6
    Input CH6 = Input(14, Range(1000, 1500, 2000), maxTimeout);

    bool controllerDead(){
        return !(CH1.isAvalible() && CH2.isAvalible() && CH3.isAvalible() && CH4.isAvalible() && CH5.isAvalible() && CH6.isAvalible());
    }

    bool controllerConnected(){
        return CH1.RCStarted() && CH2.RCStarted() && CH3.RCStarted() && CH4.RCStarted() && CH5.RCStarted() && CH6.RCStarted();
    }

    bool allNewDataAvalible(){
        return CH1.hasNewData() && CH2.hasNewData() && CH3.hasNewData() && CH4.hasNewData() && CH5.hasNewData() && CH6.hasNewData();
    }
};