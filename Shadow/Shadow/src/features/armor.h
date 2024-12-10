#pragma once

#include "utility/memory.h"
#include "utility/offsets.h"


void armor(DWORD LocalPlayerAddr)
{
	while (true)
	{
		WriteMemory<int>(LocalPlayerAddr, offsets::armor, 999);
	}
}