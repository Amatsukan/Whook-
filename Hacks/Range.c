#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void range_hack_on()
{
	int i;
	const int max_range = 255;

	cRange = TRUE;

	for(i = 0; i < 102; i++)
		*(int*)(sk_bs_addr + (i * 96) + 16) = max_range;

	*(int*)range_addr1 = max_range;
    *(int*)range_addr2 = max_range;

	*(int*)range_addr3 = max_range;
	*(int*)range_addr4 = max_range;

    *(int*)range_addr5 = max_range;
    *(int*)range_addr6 = max_range;

    *(int*)range_addr7 = max_range;
    *(int*)range_addr8 = max_range;

	*(int*)range_addr9 = max_range;
	*(int*)range_addr10 = max_range;

	*(int*)range_addr11 = max_range;
	*(int*)range_addr12 = max_range;

	*(int*)range_addr13 = max_range;
	*(int*)range_addr14 = max_range;
}

void range_hack_off()
{
	cRange = FALSE;

	*(int*)range_addr1 = 0;
    *(int*)range_addr2 = 1;

	*(int*)range_addr3 = 0;
	*(int*)range_addr4 = 1;

    *(int*)range_addr5 = 0;
    *(int*)range_addr6 = 1;

    *(int*)range_addr7 = 0;
    *(int*)range_addr8 = 1;

	*(int*)range_addr9 = 0;
	*(int*)range_addr10 = 1;

	*(int*)range_addr11 = 0;
	*(int*)range_addr12 = 1;

	*(int*)range_addr13 = 0;
	*(int*)range_addr14 = 1;
}