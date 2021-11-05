#ifndef Droideka_Position_h
#define Droideka_Position_h

#include "../Droideka/utils/constants.h"
#include <Arduino.h>

class Droideka_Position
{
public:
    // Describes the position of the robot legs.
    float legs[LEG_NB][3]; // For each leg, id 0 stores the shoulder angle in degrees, id 1 and id 2 store resp. the x and y coordinates with respect to the leg frame.
                           // LEG_NB : id 0 is the front left leg, id 1 is the front right leg, id 2 is the rear left leg, id 3 is the rear right leg.
    bool valid_position;   // True if the position in legs is theoretically reachable by the robot. False if not. /!\ Does not take into account the motors limits, etc.

    Droideka_Position();                                                              // Class initializer. valid_position is false as no actual position is specified.
    Droideka_Position(float position[LEG_NB][3]);                                     // Class initializer.
    void copy_position(Droideka_Position pos);                                        // Copy position pos to this.
    void print_position();                                                            // Prints legs and valid_position in the Serial monitor.
    void print_position(String str);                                                  // Prints str, then prints legs and valid_position in the Serial monitor.
    Droideka_Position &move_leg(int id, float trans_x, float trans_y, float trans_z); // Modifies a Droideka_Position instance with a foot displacement of (trans_x, trans_y, trans_z) in cartesian coordinates.
    Droideka_Position &move_leg_polar(int id, float theta, float rho, float trans_z); // Modifies a Droideka_Position instance with a foot displacement of (theta, rho, trans_z) in polar coordinates.

    // Enable the comparison between two Droideka_position instances. Arbitrary precision of 0.01f at the moment.
    int operator==(Droideka_Position d_p2)
    {
        bool res = true;
        for (int ii = 0; ii < LEG_NB; ii++)
        {
            for (int jj = 0; jj < 3; jj++)
            {
                if (fabs(d_p2.legs[ii][jj] - legs[ii][jj]) >= 0.01f)
                {
                    // Serial.print(ii);
                    // Serial.print("\t");
                    // Serial.print(jj);
                    // Serial.print("\t");
                    // Serial.print(d_p2.legs[ii][jj]);
                    // Serial.print("\t");
                    // Serial.println(legs[ii][jj]);
                    res = false;
                }
            }
        }
        return res;
    }
};

#endif