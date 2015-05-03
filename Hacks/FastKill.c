#include "../wFunc.h"
#include "../wAddr.h"
#include "../wInline.h"

#define MAX_MOB_KILL 256

int cur_mob;
short fastkill[MAX_MOB_KILL];

void init_fastkill()
{
	int i;
	for(i = 0; i < MAX_MOB_KILL; i++)
		fastkill[i] = 0;

	cur_mob = 0;
}

void PacketControl_fastkill(char *Data, int Type)
{
    short Code = *(short*)&Data[4];
	short Index = *(short*)&Data[6];

	const int Send = 0;
	const int Recv = 1;

	if(Code == 0x114)
	{
		init_fastkill();
	}

	else if(Code == 0x364 && *(short*)&Data[16] >= 1000)
	{
		int i;
		for(i = 0; i < MAX_MOB_KILL; i++)
			if(fastkill[i] == *(short*)&Data[16])
				break;

		if(i == MAX_MOB_KILL)
		{
			for(i = 0; i < MAX_MOB_KILL; i++)
				if(fastkill[i] == 0)
					break;

			if(i < MAX_MOB_KILL)
				fastkill[i] = *(short*)&Data[16];
		}
	}

	else if(Code == 0x367 || Code == 0x39D || Code == 0x39E)
	{
		int i;
		for(i = 0; i < MAX_MOB_KILL; i++)
			if(fastkill[i] == *(short*)&Data[60])
				break;

		if(i < MAX_MOB_KILL)
		{
			if(Type == Send && cFastKill)
			{
				__asm
				{
					MOV ECX,DWORD PTR DS:[ptrdat]
					MOV DWORD PTR DS:[ECX+0x26E90],0
				}
			}
		}
	}

	else if(Code == 0x165)
	{
		int i, index;
		for(i = 0; i < MAX_MOB_KILL; i++)
			if(fastkill[i] == *(short*)&Data[6])
				break;

		if(i < MAX_MOB_KILL)
		{
			__asm
			{
				MOV ECX,DWORD PTR DS:[ptrdat]
				MOV EAX,DWORD PTR DS:[ECX+0x26E90]
				MOV index,EAX
			}

			if(index == fastkill[i] && cFastKill)
			{
				__asm
				{
					MOV ECX,DWORD PTR DS:[ptrdat]
					MOV DWORD PTR DS:[ECX+0x26E90],0
				}
			}

			fastkill[i] = 0;
		}
	}
}

void do_fastkill()
{
	int i, max, index;

	__asm
	{
		MOV ECX,DWORD PTR DS:[ptrdat]
		MOV EAX,DWORD PTR DS:[ECX+0x26E90]
		MOV index,EAX
	}

	if(index != 0)
		return ;

	max = 0;
	i = cur_mob;

	for( ; max < MAX_MOB_KILL; max++, i++)
	{
		if(i >= MAX_MOB_KILL)
			i = 0;

		if(fastkill[i] != 0)
			break;
	}

	if(i < MAX_MOB_KILL)
	{
		cur_mob = i + 1;
		i = fastkill[i];

		
		aSetShort(i, 60);
		SendPacket(fk_pak, 168);
		
	}
}

void WINAPI UsedTimer()
{
	while(1)
	{
		Sleep(2*60*1000);

		if(cFastKill && timer_fastkill)
		{
			cFastKill = FALSE;
			ShowMsg(0xFF99FF22, "Envio de pacotes importantes.(#fastkilloff).");
		}

		if(cSpeed && timer_speed)
		{
			speed_hack_off();
			ShowMsg(0xFF99FF22, "Envio de pacotes importantes.(#speedatkoff).");
		}

		__asm
		{
			MOV ECX,DWORD PTR DS:[ptrdat]
			MOV DWORD PTR DS:[ECX+0x26E90],0
		}

		Sleep(2*1000);

		if(!cFastKill && timer_fastkill)
		{
			cFastKill = TRUE;
			ShowMsg(0xFF99FF22, "Envio de pacotes importantes.(#fastkillon).");
		}

		if(!cSpeed && timer_speed)
		{
			speed_hack_on(speed_id);
			ShowMsg(0xFF99FF22, "Envio de pacotes importantes.(#speedatkon).");
		}
	}
}