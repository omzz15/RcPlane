#include <input.cpp>

class ControllerSettings{
public:
    //the maximum amount of time before an Input is declared dead
    int maxTimeout = 500;
    //ch 1(usually the roll)
    Input CH1 = Input(9, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 2(usually the pitch)
    Input CH2 = Input(11, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 3(usually the throttle)
    Input CH3 = Input(10, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 4(usually the heading)
    Input CH4 = Input(13, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 5(usually function 1)
    Input CH5 = Input(12, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 6(usually function 2)
    Input CH6 = Input(14, Range(1000, 1500, 2000), maxTimeout, false);
};

/**
 * stores, configures, and checks all the inputs(inturups still have to be started with calcInput() from Input channels)
 */
class Controller
{
private:
    ControllerSettings settings;

public:
    Controller(ControllerSettings settings){
        this -> settings = settings;
    }
    Controller(){
        settings = ControllerSettings();
    }

    /**
     * checks if all the Input are alive(updated within the time limit in maxTimeout)
     * @return if all Inputs are alive
     */
    bool isAllAlive(){
        return settings.CH1.isAlive() && settings.CH2.isAlive() && settings.CH3.isAlive() && settings.CH4.isAlive() && settings.CH5.isAlive() && settings.CH6.isAlive();
    }

    /**
     * checks if all the Inputs were ever connected since start(was the controller ever connected)
     * @return if all the Inputs were ever connected
     */
    bool isAllStarted(){
        return settings.CH1.RCStarted() && settings.CH2.RCStarted() && settings.CH3.RCStarted() && settings.CH4.RCStarted() && settings.CH5.RCStarted() && settings.CH6.RCStarted();
    }

    /**
     * checks if all the Inputs have new data to report(was there a new pulse - can be same value as before)
     * @return if all the Inputs have new data
     */
    bool allNewDataAvalible(){
        return settings.CH1.hasNewData() && settings.CH2.hasNewData() && settings.CH3.hasNewData() && settings.CH4.hasNewData() && settings.CH5.hasNewData() && settings.CH6.hasNewData();
    }

    double[] getAllValues(){
        return {1,1,1};
    }

    /**
     * returns an input from controller based on channel number
     * @param num the channel number you want
     * @return the input linked to the specified num
     */
    Input getChannel(int num){
        if(num == 1)
            return settings.CH1;
        if(num == 2)
            return settings.CH2;
        if(num == 3)
            return settings.CH3;
        if(num == 4)
            return settings.CH4;
        if(num == 5)
            return settings.CH5;
        if(num == 6)
            return settings.CH6;
        return NULL;
    }

    ControllerSettings getSettings(){
        return settings;
    }
};