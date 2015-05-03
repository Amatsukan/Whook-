#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void AttackPlayer(int type, int sk_ID, bool isOneHit, int other_ID)
{
	if(type == 1)
	{
		ZeroMemory(pak, 168);
		SetShort(168, 0);
		SetShort(0x39D, 4);
		SetShort(GetClientID(), 6);
		SetShort(GetPosX(), 34);
		SetShort(GetPosY(), 36);
		SetShort(GetPosX(), 38);
		SetShort(GetPosY(), 40);
		SetShort(GetClientID() + 2, 42);
		SetShort(4, 46);
		SetShort(0xFF, 52);
		SetShort(0xFF, 53);
		SetShort(0xFF, 54);
		SetShort(0xFF, 55);
		SetShort(0xFF, 56);
		SetShort(0xFF, 57);
		SetShort(other_ID, 60);
		SetShort(0xFE, 64);
		SetShort(0xFF, 65);
		SetShort(0xFF, 66);
		SetShort(0xFF, 67);

		if(isOneHit)
		{
			SetShort(7, 48);
			SetShort(0xBBB, 73);
		}

		SendPacket(pak, 168);
	}

	if(type == 2)
	{
		ZeroMemory(pak, 94);
		SetShort(94, 0);
		SetShort(0x39D, 4);
		SetShort(GetClientID(), 6);
		SetShort(GetPosX(), 34);
		SetShort(GetPosY(), 36);
		SetShort(GetPosX(), 38);
		SetShort(GetPosY(), 40);
		SetShort(GetClientID() + 2, 42);
		SetShort(0xFF, 46);
		SetShort(0xFF, 52);
		SetShort(0xFF, 53);
		SetShort(0xFF, 54);
		SetShort(0xFF, 55);
		SetShort(sk_ID, 56);
		SetShort(other_ID, 60);
		SetShort(0xFF, 64);
		SetShort(0xFF, 65);
		SetShort(0xFF, 66);
		SetShort(0xFF, 67);

		if(isOneHit)
		{
			SetShort(7, 48);
			SetShort(0xBBB, 73);
		}

		SendPacket(pak, 94);
	}
}