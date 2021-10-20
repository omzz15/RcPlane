#pragma once
/**
 * class that scales and caps values based on specified values
 */
class Range
{
private:
    double rangeLow;
    double rangeHigh;

public:
    double min;
    double mid;
    double max;

    Range(double min, double mid, double max){
        update(min, mid, max);
    }

    Range(double min, double max){
        update(min, max);
    }

    Range(){
        update(-1, 1);
    }

    /**
     * updates all values of Range and sets default mid based on passed in params(also used to construct instance)
     * @param min the low end of the range
     * @param max the high end of the range
     */
    void update(double min, double max){
        update(min, min + (max - min) / 2, max);
    }

    /**
     * updates all values of Range beaed on passed in params(also used to construct instance)
     * @param min the low end of the range
     * @param mid the center of the range
     * @param max the high end of the range
     */
    void update(double min, double mid, double max){
        this->min = min;
        this->mid = mid;
        this->max = max;
        rangeHigh = max - mid;
        rangeLow = mid - min;
    }

    /**
     * scales a -1 to 1 value to min and max
     * @param val the value to scale: range -1 to 1
     */
    double scaleFrom(double val){
        return (val < 0) ? mid + (val * rangeLow) : mid + (val * rangeHigh);
    }

    /**
     * scales a min to max value to -1 and 1
     * @param val the value to scale: range min to max
     */
    double scaleTo(double val){
        return (val < mid) ? (val - mid) / rangeLow : (val - mid) / rangeHigh;
    }

    /**
     * caps a value to between min(inclusive) and max(inclusive)
     * @param val value to be capped: range min to max
     */
    double cap(double val){
        return (val > max) ? max : (val < min) ? min : val;
    }
};