#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void speed_hack_on(int speed_id)
{
	cSpeed = TRUE;

	*(DWORD*)hits_addr1	= speed_id;
	*(DWORD*)hits_addr2	= speed_id;
	*(BYTE*)hits_addr3	= 0xEB;
//	*(DWORD*)hits_addr4	= speed_id;
	*(BYTE*)hits_addr5	= 0xEB;
	*(WORD*)hits_addr6	= 0x9090;
	*(DWORD*)hits_addr7	= speed_id;
	*(DWORD*)hits_addr8	= speed_id;
	*(DWORD*)hits_addr9	= speed_id;
	*(DWORD*)hits_addr10 = speed_id;
}

void speed_hack_off()
{
	cSpeed = FALSE;

	*(DWORD*)hits_addr1	= 1000;
	*(DWORD*)hits_addr2	= 1000;
	*(BYTE*)hits_addr3	= 0x72;
	*(DWORD*)hits_addr4	= 1000;
	*(BYTE*)hits_addr5	= 0x72;
	*(WORD*)hits_addr6	= 0x5775;
	*(DWORD*)hits_addr7	= 1000;
	*(DWORD*)hits_addr8	= 1000;
	*(DWORD*)hits_addr9	= 1000;
	*(DWORD*)hits_addr10 = 1000;
}