#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void Check_AutoDrop(char *Data, short Type)
{
	short Code = *(short*)&Data[4];
	short Index = *(short*)&Data[6];

	const int Send = 0;
	const int Recv = 1;

	if(Code == 0x182 && Type == Recv && cDrop)
	{
		short equip = *(short*)&Data[12];
		short slot = *(short*)&Data[14];
		short item = *(short*)&Data[16];
		int dig;

		if(equip != 1) return;

		for(i = 0; i < 256; i++)
		{
			if(DropList[i] == item) 
			{
				dig = DropList[i];
				break;
			}
		}

		if(item == 0) return;
		if(item == dig)
		{
			sprintf(&msg_pak[1900], "Item [%d] foi adicionado com sucesso.", item);
			ShowMsg(0xFF99FF22, "#drop - [%d] adicionado.", item);
			CliMsg(3000, &msg_pak[1900]);
			printf("\a");
		}
	
		else
		{
			ZeroMemory(pak, 20);
			SetShort(20, 0);
			SetShort(0x2E4, 4);
			SetShort(GetClientID(), 6);
			SetShort(slot, 12);
			SetShort(item, 16);
			SendPacket(pak, 20);
			SendPacket(pak, 20);
			ShowMsg(0xFF99FF22, "#drop - [%d] descartado.", item);
	
			__asm
			{
				MOV EAX, ptrdat
				MOV EDX, DWORD PTR DS:[EAX]
				ADD EDX, 0x4C
				MOV ECX, DWORD PTR DS:[EDX]
			}
		}
	}
}