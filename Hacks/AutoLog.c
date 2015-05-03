#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void WINAPI TimedFunc()
{
	while(1)
	{
		if(CheckGameStat())
		{
			Sleep(32*1000);

			if(CheckGameStat())
			{
				macro = *(short*)0x0635334;
				sec2_x = GetPosX();
				sec2_y = GetPosY();

				ZeroMemory(fk2_pak, 0xC);
				bSetShort(0xC, 0);
				bSetShort(0x215, 4);
				bSetShort(GetClientID(), 6);
				ZeroMemory(&fk2_pak[20], 0x24);
				bSetShort(0x24, 20);
				bSetShort(0x213, 24);
				bSetShort(GetClientID(), 26);
				bSetShort(set_char, 32);
	
				SendPacket(fk2_pak, 0xC);
				Sleep(1000);
				SendPacket(&fk2_pak[20], 0x24);

				Sleep(2*1000);

				*(short*)0x0635334 = macro;
				if(pt_id != 0 && pt_name[0] != 0) party_hack(pt_id, pt_name);

				Sleep(2*1000);
				sec2_x = 0;
				sec2_y = 0;
			}	
		}
	}
}