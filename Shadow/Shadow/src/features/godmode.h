#pragma once

#include "utility/memory.h"
#include "utility/offsets.h"


void godmode(DWORD LocalPlayerAddr)
{
	while (true)
	{
		WriteMemory<int>(LocalPlayerAddr, offsets::health, 999);
	}
}