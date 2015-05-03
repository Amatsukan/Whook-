#include "../wAddr.h"
#include "../wInline.h"
#include "../wTypes.h"
#include "../wFunc.h"

void sAction(int x, int y)
{
    ZeroMemory(pak, 0x34);
    SetShort(0x36C, 4);
    SetShort(GetClientID(), 6);
    SetShort(GetPosX(), 12);
    SetShort(GetPosY(), 14);
	SetInt(0, 16);
    SetInt(GetMoveSpeed(), 20);
    SetShort(x, 48);
    SetShort(y, 50);
    SendPacket(pak, 0x34);
	MoveCharacter(0x36C, pak);
}

void sTeleport(int x, int y)
{
    ZeroMemory(pak, 0x34);
    SetShort(0x36C, 4);
    SetShort(GetClientID(), 6);
    SetShort(GetPosX(), 12);
    SetShort(GetPosY(), 14);
    SetInt(1, 16);
    SetInt(GetMoveSpeed(), 20);
    SetShort(x, 48);
    SetShort(y, 50);
    SendPacket(pak, 0x34);

     __asm
     {
		MOV EAX, ptrdat
		MOV EDX, DWORD PTR DS:[EAX]
		ADD EDX, 0x4C
		MOV ECX, DWORD PTR DS:[EDX]
     }
 
    MoveCharacter(0x36C, pak);
	MoveCharacter(0x36C, pak);
}

void cTeleport(int x, int y)
{
    ZeroMemory(pak, 0x34);
	SetShort(0x36C, 4);
    SetShort(GetClientID(), 6);
    SetShort(GetPosX(), 12);
    SetShort(GetPosY(), 14);
    SetInt(1, 16);
    SetInt(GetMoveSpeed(), 20);
    SetShort(x, 48);
    SetShort(y, 50);

    __asm
    {
		MOV EAX, ptrdat
        MOV EDX, DWORD PTR DS:[EAX]
        ADD EDX, 0x4C
        MOV ECX, DWORD PTR DS:[EDX]
    }
 
    MoveCharacter(0x36C, pak);
}