
#include <iostream>
#include <Windows.h>

#include "offsets.h"
#include "godmode.h"
#include "armor.h"
#include "infinite_ammo.h"


#include "utility/featurestate.h"
#include "protections/skCrypter.h"

//ImGui Imports
//#include "imgui/imgui_impl_dx9.h"
//#include "imgui/imgui_impl_win32.h"
//#include "imgui/imgui.h"

DWORD WINAPI GodModeThread(LPVOID lpParam) {
    DWORD LocalPlayerAddr = *(DWORD*)lpParam;
    while (!GetAsyncKeyState(VK_DELETE)) {
        if (GetAsyncKeyState(VK_F1) & 1) {
            godmode(LocalPlayerAddr);
            std::cout << skCrypt("GodMode Exploit Enabled") << std::endl;
            godmode_state = true;
        }
        Sleep(10);  
    }
    return 0;
}

DWORD WINAPI ArmorThread(LPVOID lpParam) {
    DWORD LocalPlayerAddr = *(DWORD*)lpParam;
    while (!GetAsyncKeyState(VK_DELETE)) {
        if (GetAsyncKeyState(VK_F2) & 1) {
            armor(LocalPlayerAddr);
            armor_state = true;
        }
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI InfiniteAmmoThread(LPVOID lpParam) {
    DWORD LocalPlayerAddr = *(DWORD*)lpParam;
    while (!GetAsyncKeyState(VK_DELETE)) {
        if (GetAsyncKeyState(VK_F3)) {
            infiniteAmmo(LocalPlayerAddr);
            infiniteAmmo_state = true;
        }
        Sleep(10);
    }
    return 0;
}



DWORD WINAPI MainThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << skCrypt("Shadow Internal\nInjected Succesfully!") << std::endl;

    Sleep(4000);

    system("cls");

    DWORD BaseAddress = (DWORD)GetModuleHandle("ac_client.exe");

    if (!BaseAddress)
    {
        std::cerr << skCrypt("Error: Base Address Not Found") << std::endl;
        fclose(f);
        FreeConsole();
        FreeLibraryAndExitThread(hModule, 0);
        return 0;
    }

    std::cout << skCrypt("Base Address Found: ") << std::hex << BaseAddress << std::endl;

    DWORD LocalPlayerAddr = *(DWORD*)(BaseAddress + offsets::localPlayer);
    if (!LocalPlayerAddr)
    {
        std::cerr << skCrypt("Error: LocalPlayer not valid") << std::endl;
    }

    std::cout << skCrypt("LocalPlayer: ") << LocalPlayerAddr << std::endl;

    system("cls");

   
    CloseHandle(CreateThread(nullptr, 0, GodModeThread, &LocalPlayerAddr, 0, nullptr));
    CloseHandle(CreateThread(nullptr, 0, ArmorThread, &LocalPlayerAddr, 0, nullptr));
    CloseHandle(CreateThread(nullptr, 0, InfiniteAmmoThread, &LocalPlayerAddr, 0, nullptr));


    while (!GetAsyncKeyState(VK_DELETE))
    {
        
        Sleep(10);  
    }

    std::cout << skCrypt("Panic button pressed.\nExiting and deallocating memory in 5 seconds...") << std::endl;

    Sleep(5000);

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);

    return 0;  
}


// Entry Point
    BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
        switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
