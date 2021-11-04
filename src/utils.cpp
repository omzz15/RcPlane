#pragma once

class Utils
{
public:
    /**
     * caps a value to between min(inclusive) and max(inclusive)
     * @param val value to be capped: range min to max
     */
    static double clamp(double val, double min, double max)
    {
        return (val > max) ? max : (val < min) ? min
                                               : val;
    }

    /**
     * caps a value to between -1 and 1
     * @param val value to be capped: range -1 to 1
     */
    static double clamp(double val)
    {
        return clamp(val, -1, 1);
    }

    /**
     * flips a value is boolean is true
     * @param val the value you want to flip
     * @param flip if you want the value to be flipped
     */
    static double flip(double val, bool flip){
        return (flip) ? -val : val;
    }
};