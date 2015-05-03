#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void inv_hack_on()
{
	cInv = TRUE;

	ZeroMemory(pak, 20);
	SetShort(0, 0);
	SetShort(0, 2);
	SetShort(0xAD9, 4);
	SetShort(GetClientID(), 6);
	SetInt(0, 8);
	SetInt(2, 12);
	SetInt(1, 16);

	SendPacket(pak, 20);
}

void inv_hack_off()
{
	int gx = GetPosX();
	int gy = GetPosY();

	cInv = FALSE;

	ZeroMemory(pak, 20);
	SetShort(0, 0);
	SetShort(0, 2);
	SetShort(0xAD9, 4);
	SetShort(GetClientID(), 6);
	SetInt(0, 8);
	SetInt(2, 12);
	SetInt(2, 16);
	SendPacket(pak, 20);

	sTeleport(gx,gy);
}