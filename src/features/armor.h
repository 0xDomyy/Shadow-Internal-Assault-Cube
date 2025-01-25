#pragma once

#include "utility/offsets.h"

void armor(DWORD LocalPlayerAddr)
{
    while (true) {
        int armor = *(int*)(LocalPlayerAddr + offsets::armor);
        /*std::cout << "Armor Value: " << armor << std::endl;*/
        if (armor != 999)
        {
            *(int*)(LocalPlayerAddr + offsets::armor) = 999;
        }
    }
}
