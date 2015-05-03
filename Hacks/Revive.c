#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void revive_hack()
{
	*(short*)&pak[4] = 0x289;
	*(short*)&pak[6] = GetClientID();
	SendPacket(pak, 14);
}