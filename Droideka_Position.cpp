#include "Droideka_Position.h"

Droideka_Position::Droideka_Position()
{
    /* Class initializer. valid_position is false as no actual position was specified.
     */
    valid_position = false;
}

Droideka_Position::Droideka_Position(float position[LEG_NB][3])
{
    /* Class initializer.
     *
     * position : the legs position.
     * LEG_NB : id 0 is the front left leg, id 1 is the front right leg, id 2 is the rear left leg, id 3 is the rear right leg.
     * For each leg, id 0 stores the shoulder angle in degrees, id 1 and id 2 store resp. the x and y coordinates with respect to the leg frame.
     */
    for (int ii = 0; ii < LEG_NB; ii++)
    {
        if (position[ii][1] * position[ii][1] + position[ii][2] * position[ii][2] > (HIP_LENGTH + TIBIA_LENGTH) * (HIP_LENGTH + TIBIA_LENGTH))
        {
            valid_position = false;
            break;
        }
        else
        {
            valid_position = true;
        }
    }

    for (int ii = 0; ii < LEG_NB; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            legs[ii][jj] = position[ii][jj];
        }
    }
}

void Droideka_Position::copy_position(Droideka_Position position)
{
    /* copies Droideka_position position into current instance.
     *
     * position : the position to be copied.
     */
    for (int ii = 0; ii < LEG_NB; ii++)
    {
        if (position.legs[ii][1] * position.legs[ii][1] + position.legs[ii][2] * position.legs[ii][2] > (HIP_LENGTH + TIBIA_LENGTH) * (HIP_LENGTH + TIBIA_LENGTH))
        {
            valid_position = false;
            break;
        }
        else
        {
            valid_position = true;
            for (int jj = 0; jj < 3; jj++)
            {
                legs[ii][jj] = position.legs[ii][jj];
            }
        }
    }
}

void Droideka_Position::print_position()
{
    /* Prints position
     *
     * Displays info so that it is somewhat readable.
     */
    for (int ii = 0; ii < LEG_NB; ii++)
    {
        Serial.print("Leg n°" + String(ii) + " : ");
        for (int jj = 0; jj < 3; jj++)
        {
            Serial.print(legs[ii][jj]);
            Serial.print(" ");
        }
        Serial.println();
    }
    Serial.println("Valid position: " + String(valid_position));
}

void Droideka_Position::print_position(String str)
{
    /* Prints str then prints position.
     *
     * Displays info so that it is somewhat readable.
     */
    Serial.println(str);
    print_position();
}

Droideka_Position &Droideka_Position::move_leg(int id, float trans_x, float trans_y, float trans_z)
{
    /* Modifies a Droideka_Position instance with a foot displacement of (trans_x, trans_y, trans_z) in cartesian coordinates.
     *
     * id : leg id to move.
     * trans_x : longitudinal foot displacement
     * trans_y : lateral foot disp
     * trans_z : vertical foot displacement
     */
    if (id == 0)
    {
        trans_x = -trans_x;
    }
    else if (id == 1)
    {
    }
    else if (id == 2)
    {
        trans_x = -trans_x;
        trans_y = -trans_y;
    }
    else if (id == 3)
    {
        trans_y = -trans_y;
    }
    float temp_theta, temp_rho, temp_z;
    temp_theta = 180 * atan((legs[id][1] * sin(PI * legs[id][0] / 180) + trans_y) / (legs[id][1] * cos(PI * legs[id][0] / 180) + trans_x)) / PI;
    temp_rho = (legs[id][1] * cos(PI * legs[id][0] / 180) + trans_x) / cos(PI * temp_theta / 180);
    temp_z = legs[id][2] + trans_z;
    legs[id][0] = temp_theta;
    legs[id][1] = temp_rho;
    legs[id][2] = temp_z;

    for (int ii = 0; ii < LEG_NB; ii++)
    {
        if (legs[ii][1] * legs[ii][1] + legs[ii][2] * legs[ii][2] > (HIP_LENGTH + TIBIA_LENGTH) * (HIP_LENGTH + TIBIA_LENGTH))
        {
            valid_position = false;
            break;
        }
        else
        {
            valid_position = true;
        }
    }
    return *this;
}

Droideka_Position &Droideka_Position::move_leg_polar(int id, float theta, float rho, float trans_z)
{
    /* Modifies a Droideka_Position instance with a foot displacement of (theta, rho, trans_z) in polar coordinates.
     *r
     * id : leg id to move.
     * theta : leg angle (added to starting position)
     * rho : replaces the previous value /!\ This is a replacement, not an addition.
     * trans_z : vertical foot displacement
     */
    if (id == 0 || id == 3)
    {
        theta = -theta;
    }
    float temp_theta, temp_rho, temp_z;
    temp_theta = legs[id][0] + theta;
    temp_rho = rho;
    temp_z = legs[id][2] + trans_z;
    legs[id][0] = temp_theta;
    legs[id][1] = temp_rho;
    legs[id][2] = temp_z;

    for (int ii = 0; ii < LEG_NB; ii++)
    {
        if (legs[ii][1] * legs[ii][1] + legs[ii][2] * legs[ii][2] > (HIP_LENGTH + TIBIA_LENGTH) * (HIP_LENGTH + TIBIA_LENGTH))
        {
            valid_position = false;
            break;
        }
        else
        {
            valid_position = true;
        }
    }
    return *this;
}