#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void wall_hack_on()
{
	memset((void*)wall_addr1, 0x90, 6);
	memset((void*)wall_addr2, 0x90, 6);
	memset((void*)wall_addr3, 0x90, 6);
	memset((void*)wall_addr4, 0x90, 6);

	cWall = TRUE;
}

void wall_hack_off()
{
	static uchar wallhack_jnz[4][6] = {
		{ 0x0F, 0x85, 0x9A, 0x0A, 0x00, 0x00 },
		{ 0x0F, 0x85, 0x86, 0x0A, 0x00, 0x00 },
		{ 0x0F, 0x85, 0x63, 0x09, 0x00, 0x00 },
		{ 0x0F, 0x85, 0x4F, 0x09, 0x00, 0x00 }
	};

	memcpy((void*)wall_addr1, wallhack_jnz[0], 6);
	memcpy((void*)wall_addr2, wallhack_jnz[1], 6);
	memcpy((void*)wall_addr3, wallhack_jnz[2], 6);
	memcpy((void*)wall_addr4, wallhack_jnz[3], 6);

	cWall = FALSE;
}