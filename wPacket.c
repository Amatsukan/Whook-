#include "wAddr.h"
#include "wInline.h"
#include "wTypes.h"
#include "wFunc.h"

void PacketControl(char *Data, int *Lenght, int Type)
{
	short Size = *(short*)Data;
    short OPCode = *(short*)&Data[4];
	short pClientID = *(short*)&Data[6];
	int Time = *(int*)&Data[8];

	const int Send = 0;
	const int Recv = 1;

	if(OPCode == 0x3A0) inject++;

	if(OPCode == 0x20D && Type == Send) strcpy(clogin, (char*)&Data[24]);

	if(OPCode == 0xFDE && Type == Recv) inject++;

	if(OPCode == 0x213 && Type == Send) set_char = *(short*)&Data[12];

	if(CheckGameStat())
	{
		if(inject < 2) exit(1);

		PacketControl_fastkill(Data, Type);
		Check_AutoDrop(Data, Type);		

		if(OPCode == 0x36C && Type == Send && cSpeedMove) *(int*)&Data[16] = 1;

		if(OPCode == 0x37E && Type == Recv && cInv) ZeroMemory(Data, 2048);

		if(OPCode == 0x364 && Type == Send) *(char*)&Data[148] = 0;

		if(OPCode == 0x333 && Type == Send && chat_index != 0) *(short*)&Data[6] = chat_index;

		if((OPCode == 0x333 || OPCode == 0xD1D || OPCode == 0x334) && Type == Recv) if(cFree) ZeroMemory(Data, 2048);

		if((OPCode == 0x364 || OPCode == 0x336) && Type == Recv)
		{
			if(strncmp((char*)&Data[18], "[GM]", 4) == 0)
			{
				cInv = FALSE;
				cOneHit = FALSE;
				cAtkInv = FALSE;
				cRevive = FALSE;
				cOneHit = FALSE;
				cFastKill = FALSE;
				cSpeed = FALSE;
				cRange = FALSE;
				cWall = FALSE;
				sec_x = 0, sec_y = 0;

				sTeleport(2100, 2100);

				ShowMsg(0xFF99FF22, "GM IDENTIFICADO! HACKS DESLIGADOS!");
			}

			if(cIndex)
			{
				sprintf(pak, "index = %hd", *(short*)&Data[16]);
				strcpy(&Data[202], pak);
			}

			if(cInv && (OPCode == 0x364 && *(short*)&Data[16] == GetClientID()))
				*(char*)&Data[148] &= 254;

			if(*(char*)&Data[69] == 0x1C)
			{
				ZeroMemory(msg_pak, 2048);
				*(short*)&Data[68] = 0;
				if(cIndex) sprintf(msg_pak, "SK INV - %d", *(short*)&Data[16]);
				if(!cIndex) sprintf(msg_pak, "SK INV");
				strcpy(&Data[202], msg_pak);
			}

			if(*(char*)&Data[148] % 2 != 0 && *(short*)&Data[16] <= 1000)
			{
				*(short*)&Data[148] = 254;
				if(cIndex) sprintf(pak, "INV - %d", *(short*)&Data[16]);
				if(!cIndex) sprintf(pak, "INV");
				strcpy(&Data[202], pak);
			}
		}

		if(Type == Send && (OPCode == 0x367 || OPCode == 0x39D || OPCode == 0x39E))
		{
			if(cOneHit)
			{
				*(short*)&Data[48] = 7;
				*(char*)&Data[73] = 0xBBB;
			}

			if(cRange)
			{
				*(short*)&Data[34] = *(short*)&Data[38] = GetPosX();
				*(short*)&Data[36] = *(short*)&Data[40] = GetPosY();
			}

			if(cAtkInv) *(short*)&Data[42] = GetClientID() + (rand() % 5);			
			
			if(cInv)
			{
				CliMsg(2000, "Para atacar, desligue a invisibilidade. (#invoff)");
				ZeroMemory(Data, 2048);
			}
		}
	}
}

