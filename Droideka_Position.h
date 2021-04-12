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
    void print_position(String str);

    int operator==(Droideka_Position d_p2)
    {
        bool res = true;
        for (int ii = 0; ii < LEG_NB; ii++)
        {
            for (int jj = 0; jj < 3; jj++)
            {
                if (fabs(d_p2.legs[ii][jj] - legs[ii][jj]) >= 0.01f)
                {
                    Serial.print(ii);
                    Serial.print("\t");
                    Serial.print(jj);
                    Serial.print("\t");
                    Serial.print(d_p2.legs[ii][jj]);
                    Serial.print("\t");
                    Serial.println(legs[ii][jj]);
                    res = false;
                }
            }
        }
        return res;
    }
};

#endif