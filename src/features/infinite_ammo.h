#pragma once

#include "Windows.h"
#include <iostream>

#include "utility/offsets.h"

void infiniteAmmo(DWORD LocalPlayerAddr) {
    while (true) {
        int rifleAmmo = *(int*)(LocalPlayerAddr + offsets::rifleAmmo);
        int pistolAmmo = *(int*)(LocalPlayerAddr + offsets::pistolAmmo);
        int sniperAmmo = *(int*)(LocalPlayerAddr + offsets::rifleAmmo);
        int shotgunAmmo = *(int*)(LocalPlayerAddr + offsets::shotgunAmmo);
        int tmpCarabineAmmo = *(int*)(LocalPlayerAddr + offsets::tmpCarabineAmmo);
        /*std::cout << "ammo Value: " << ammo << std::endl;*/
        if (rifleAmmo != 999 || pistolAmmo != 999 || shotgunAmmo != 999 || sniperAmmo != 999 || tmpCarabineAmmo != 999)
        {
            *(int*)(LocalPlayerAddr + offsets::rifleAmmo) = 999;
            *(int*)(LocalPlayerAddr + offsets::pistolAmmo) = 999;
            *(int*)(LocalPlayerAddr + offsets::sniperAmmo) = 999;
            *(int*)(LocalPlayerAddr + offsets::shotgunAmmo) = 999;
            *(int*)(LocalPlayerAddr + offsets::tmpCarabineAmmo) = 999;
        }
    }
}