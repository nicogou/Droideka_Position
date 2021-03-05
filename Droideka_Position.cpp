#include "Droideka_Position.h"

Droideka_Position::Droideka_Position()
{
    valid_position = false;
}

Droideka_Position::Droideka_Position(float position[LEG_NB][3])
{
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
    Serial.println(str);
    print_position();
}
