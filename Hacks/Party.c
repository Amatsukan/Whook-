#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void party_hack(int index, char *nick)
{
	ZeroMemory(pak, 32);
	SetShort(0, 0);
	SetShort(0, 2);
	SetShort(0x3AB, 4);
	SetShort(GetClientID(), 6);
	SetInt(0, 8);
	SetShort(index, 12);
	strcpy(&pak[14], nick);
	SendPacket(pak, 32);
}