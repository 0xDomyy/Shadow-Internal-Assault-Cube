#pragma once

#include <Windows.h>
#include <iostream>


template <typename T>
bool WriteMemory(DWORD baseAddress, DWORD offset, T value)
{
    DWORD address = baseAddress + offset;

    DWORD oldProtect;
    if (VirtualProtect((LPVOID)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        *(T*)address = value;
        VirtualProtect((LPVOID)address, sizeof(T), oldProtect, &oldProtect);
        return true;
    }
    else
    {
        std::cerr << "Errore: Impossibile modificare i permessi della memoria." << std::endl;
        return false;
    }
}
