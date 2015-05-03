#include "wAddr.h"
#include "wInline.h"
#include "wTypes.h"
#include "wFunc.h"

void ShowMsg(int color, char *s, ...)
{
	int *dat;
    va_list pArgList;

	va_start(pArgList, s);
	vsprintf(pak, s, pArgList);
	va_end(pArgList);

    *(int*)color_addr = color;

	dat = *(int**)ptrdat;

	__asm
	{
		MOV ECX, dat
	}

    ShowGameMessage(pak);

    *(int*)color_addr = 0xFFFFAAAA;
}

void CliMsg(int delay, char *msg)
{
	DWORD addr = climsg_addr;

	va_list pArgList;

	va_start(pArgList, msg);
	vsprintf(pak, msg, pArgList);
	va_end(pArgList);

	__asm
	{	
		PUSH delay
		PUSH pak
		MOV ECX, DWORD PTR SS:[ptrdat]
		MOV ECX, DWORD PTR DS:[ECX+0xC4]
		CALL addr
		PUSH 0
		PUSH 1
		MOV EDX, DWORD PTR SS:[ptrdat]
		MOV ECX, DWORD PTR DS:[EDX+0xC4]
		MOV EAX, DWORD PTR SS:[ptrdat]
		MOV EDX, DWORD PTR DS:[EAX+0xC4]
		MOV EAX, DWORD PTR DS:[EDX]
		CALL DWORD PTR DS:[EAX+0x88]
		MOV EAX, 1
	}
}

void hook_func()
{	
	VirtualProtect((int*)vprotect_addr1,vprotect_addr2 - vprotect_addr1,0x40, &OldProtect);

	strcpy((char*)wintitle_addr, "wMod v2.1");

	JMP_NEAR(hook_chkpak_send_call, Hook_Chkpak_Send);
	JGE_NEAR(hook_chkpak_recv_call, Hook_Chkpak_Recv);
	JNZ_NEAR(hook_cmd_call, Hook_Command);
	JMP_NEAR(hook_timer_func_call, Hook_TimerFunc);
	
	*(char*)0x04B9065 = 0xEB; // Create Scene Fail
	*(char*)0x04F7203 = 0xEB; // Crashed Character Unit Time
	*(char*)0x0477EF3 = 0xEB; // Critical Data Error In Client
	*(char*)0x0477F3C = 0xEB; // Critical Data Error In Client
	*(char*)0x04A8A39 = 0xEB; // Critical Data Error In Client	

    MoveCharacter		= (void*)movechar_addr;
    ShowGameMessage		= (void*)showmsg_addr;
    SendPacket			= (void*)sendpak_addr;
	
    return;
}