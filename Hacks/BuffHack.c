#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void buff_hack_on()
{
	int i;
	for(i = 0; i < 102; i++) *(int*)(sk_bs_addr + (i * 96) + 4) = 2;
}

void buff_hack_off()
{
	int i;
	for(i = 0; i < 102; i++) *(int*)(sk_bs_addr + (i * 96) + 4) = 0;
}