#include "../wFunc.h"
#include "../wAddr.h"
#include "../wInline.h"

/*
void PacketControl_macroup(char *Data, int Type)
{
    short Code = *(short*)&Data[4];
	short Index = *(short*)&Data[6];
	char *Question = (char*)&Data[222];

	const int Send = 0;
	const int Recv = 1;

	if(Code == 0x7B1)
	{
		if(strcmp(Question, "xxx") == 0)
		{
			sAction(GetPosX() + 2, 1);
		}
	}
}
*/