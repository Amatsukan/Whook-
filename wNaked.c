#include "wFunc.h"
#include "wAddr.h"

void __declspec(naked) Hook_Command()
{
	__asm
	{
		MOV EAX,DWORD PTR SS:[EBP-098h]
		MOV EDX,DWORD PTR DS:[EAX]
		MOV ECX,DWORD PTR SS:[EBP-098h]
		CALL DWORD PTR DS:[EDX+088h]

		PUSH EAX
		CALL Command
		ADD ESP,08h

		TEST EAX,EAX
		JE chk_other_cmd

		MOV EAX,01h
		MOV ECX,hook_cmd_jmp1
		JMP ECX

chk_other_cmd:
		MOV EAX,hook_cmd_jmp2
		JMP EAX
	}
}

void __declspec(naked) Hook_TimerFunc()
{
	__asm
	{
		CALL TimerFunc

		CMP DWORD PTR SS:[EBP-020h],012h
		JE exit_loop

		MOV EAX,hook_timer_func_jmp1
		JMP EAX

exit_loop:
		MOV EAX,hook_timer_func_jmp2
		JMP EAX
	}
}

void __declspec(naked) Hook_Chkpak_Send()
{
	__asm
	{
		PUSH 0
		LEA ECX,DWORD PTR SS:[EBP+0Ch]
		PUSH ECX
		PUSH DWORD PTR SS:[EBP+08h]
		CALL PacketControl
		ADD ESP,0Ch

		MOV DWORD PTR SS:[EBP-0x0C],0x04

		MOV EAX,hook_chkpak_send_jmp1
		JMP EAX
	}
}

void __declspec(naked) Hook_Chkpak_Recv()
{
	__asm
	{
		MOV EAX,DWORD PTR SS:[EBP-0x08]
		AND EAX,0xFFFF
		MOV DWORD PTR SS:[EBP-0x08],EAX

		PUSH 0x01
		LEA ECX,DWORD PTR SS:[EBP-0x08]
		PUSH ECX
		PUSH DWORD PTR SS:[EBP-0x18]
		CALL PacketControl
		ADD ESP,0Ch

		MOV EAX,hook_chkpak_recv_jmp1
		JMP EAX
	}
}

