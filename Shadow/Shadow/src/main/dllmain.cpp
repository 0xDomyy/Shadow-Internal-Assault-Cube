// dllmain.cpp : Definisce il punto di ingresso per l'applicazione DLL.
#include <iostream>
#include <Windows.h>

#include "offsets.h"
#include "godmode.h"
#include "armor.h"
#include "utility/featurestate.h"

//ImGui Imports
//#include "imgui/imgui_impl_dx9.h"
//#include "imgui/imgui_impl_win32.h"
//#include "imgui/imgui.h"



DWORD WINAPI MainThread(HMODULE hModule)
{
    
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Shadow Internal" << std::endl;

    
    DWORD BaseAddress = (DWORD)GetModuleHandle("ac_client.exe");
    if (!BaseAddress)
    {
        std::cerr << "Error: Base Address Not Found" << std::endl;
        fclose(f);
        FreeConsole();
        FreeLibraryAndExitThread(hModule, 0);
        return 0;
    }

    std::cout << "Base Address Found: " << std::hex << BaseAddress << std::endl;

    DWORD LocalPlayerAddr = *(DWORD*)(BaseAddress + offsets::localPlayer);
    if (!LocalPlayerAddr)
    {
        std::cerr << "Error: LocalPlayer not valid" << std::endl;
    }

    while (!GetAsyncKeyState(VK_END))
    {
        if (GetAsyncKeyState(VK_F1))
        {
            godmode(LocalPlayerAddr);

            std::cout << "GodMode Exploit Enabled" << std::endl;

            godmode_state = true;
                    
        }

        if (GetAsyncKeyState(VK_F2))
        {
            armor(LocalPlayerAddr);

            std::cout << "Armor Exploit Enabled" << std::endl;

            armor_state = true;

        }

        Sleep(10); 
    }

    
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}

// Entry Point
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved)
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
