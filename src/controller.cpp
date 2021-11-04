#include <input.cpp>

/**
 * stores, configures, and checks all the inputs(inturups still have to be started with calcInput() from Input channels)
 */
class Controller
{
public:
    //the maximum amount of time before an Input is declared dead
    int maxTimeout = 1000;
    //ch 1(usually the ______)
    Input CH1 = Input(9, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 2(usually the ______)
    Input CH2 = Input(11, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 3(usually the throttle)
    Input CH3 = Input(10, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 4(usually the ______)
    Input CH4 = Input(13, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 5(usually function 1)
    Input CH5 = Input(12, Range(1000, 1500, 2000), maxTimeout, false);
    //ch 6(usually function 2)
    Input CH6 = Input(14, Range(1000, 1500, 2000), maxTimeout, false);

    /**
     * checks if all the Input are alive(updated within the time limit in maxTimeout)
     * @return if all Inputs are alive
     */
    bool isAllAlive(){
        return CH1.isAlive() && CH2.isAlive() && CH3.isAlive() && CH4.isAlive() && CH5.isAlive() && CH6.isAlive();
    }

    /**
     * checks if all the Inputs were ever connected since start(was the controller ever connected)
     * @return if all the Inputs were ever connected
     */
    bool isAllStarted(){
        return CH1.RCStarted() && CH2.RCStarted() && CH3.RCStarted() && CH4.RCStarted() && CH5.RCStarted() && CH6.RCStarted();
    }

    /**
     * checks if all the Inputs have new data to report(was there a new pulse - can be same value as before)
     * @return if all the Inputs have new data
     */
    bool allNewDataAvalible(){
        return CH1.hasNewData() && CH2.hasNewData() && CH3.hasNewData() && CH4.hasNewData() && CH5.hasNewData() && CH6.hasNewData();
    }
};