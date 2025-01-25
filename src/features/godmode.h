#pragma once

#include "utility/offsets.h"

void godmode(DWORD LocalPlayerAddr)
{
    while (true) {
        int health = *(int*)(LocalPlayerAddr + offsets::health);
        /*std::cout << "Health Value: " << health << std::endl;*/
        if (health != 999)
        {
            *(int*)(LocalPlayerAddr + offsets::health) = 999;
        }
    }
}
