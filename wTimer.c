#include "wAddr.h"
#include "wInline.h"
#include "wTypes.h"
#include "wFunc.h"

static DWORD exec_time = 0;

void TimerFunc()
{
	if(CheckGameStat())
	{
		__asm
		{
			MOV ECX,DWORD PTR DS:[ptrdat]
			MOV DWORD PTR DS:[ECX+0x26E90],0
		}

		if(*(int*)(*(int*)ptrdat + 0x54)) *(int*)(*(int*)ptrdat + 0x54) = 0;

		if(inject < 2) exit(1);

		if(cFastKill)
			do_fastkill();

		if(sec_x != 0 && sec_y != 0)
			if(sec_x != GetPosX() || sec_y != GetPosY())
				sTeleport(sec_x,sec_y);

		if(sec2_x != 0 && sec2_y != 0)
			if(sec2_x != GetPosX() || sec2_y != GetPosY())
				sTeleport(sec2_x,sec2_y);

		if(cRevive && *(int*)(*(int*)(0x0612AA0) + 0x74) == 0)
		{
			sec_x = GetPosX();
			sec_y = GetPosY();
			revive_hack();
		}

		if(GetAsyncKeyState(VK_F5))
		{
			__asm
			{
				MOV EAX,ptrdat
				MOV EDX,DWORD PTR DS:[EAX]
					
				PUSH 1
				MOV ECX,EDX
				MOV EAX,cargo_addr1
				CALL EAX
			}
		}

		if(GetAsyncKeyState(VK_F6))
		{
			cRevive = TRUE;
			sec_x = GetPosX();
			sec_y = GetPosY();
		}
	}
}