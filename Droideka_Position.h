#ifndef Droideka_Position_h
#define Droideka_Position_h

#include "../Droideka/utils/constants.h"
#include <Arduino.h>

class Droideka_Position
{
public:
    float legs[LEG_NB][3]; // For each leg, id 0 stores the shoulder angle in degrees, id 1 and id 2 store resp. the x and y coordinates with respect to the leg frame.
                           // LEG_NB : id 0 is the front left leg, id 1 is the front right leg, id 2 is the rear left leg, id 3 is the rear right leg.
    bool valid_position;

    Droideka_Position();
    Droideka_Position(float position[LEG_NB][3]);
    void copy_position(Droideka_Position pos);
    void print_position();
};

#endif