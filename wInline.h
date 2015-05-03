#include "wAddr.h"
#include "wTypes.h"
#include "wFunc.h"
#include "wStruct.h"

#include <signal.h>

#define PTR2PTR(ptrInit) *(DWORD*)(*(DWORD*)ptrInit)

#define JMP_NEAR_SIZE 5
#define JNZ_NEAR_SIZE 6
#define JGE_NEAR_SIZE 6
#define JG_NEAR_SIZE 6
#define CALL_NEAR_SIZE 5

DWORD i;
int inParam;
FILE *stdin_stream;

#define DEF_STR(str, addr) strcpy((CHAR*)addr, (CONST CHAR*)str)

__forceinline int GetClientID()
{
	__asm
	{
		MOV ECX,DWORD PTR DS:[acc_addr]
		ADD ECX,0xDFC
		XOR EAX,EAX
		MOV AX,WORD PTR DS:[ECX]
	}
}

__forceinline MOB_ST GetChar()
{
	__asm
	{
		MOV EAX,DWORD PTR DS:[acc_addr]
		ADD EAX,0x750
	}
}


__forceinline int GetGoldCargo()
{
	__asm
	{
		MOV ECX,DWORD PTR DS:[acc_addr]
		ADD ECX,0xC58
		MOV EAX,DWORD PTR DS:[ECX]
	}
}

__forceinline int GetMoveSpeed()
{
	return *(int*)movespeed_addr;
}

__forceinline int CheckGameStat()
{
	return *(int**)ptrdat != NULL && *(int*)((char*)(*(int**)ptrdat) + 76) != 0;
}

__forceinline HWND GetHWND()
{
	return *(HWND*)wnd_addr;
}

__forceinline short GetPosX()
{
	return (short)(*(float*)((*(int*)((char*)(*(int**)ptrdat) + 76)) + 40));
}

__forceinline short GetPosY()
{
	return (short)(*(float*)((*(int*)((char*)(*(int**)ptrdat) + 76)) + 44));
}

__forceinline void BuildIndirection(DWORD dwAddress, BYTE *opCode, DWORD opCodeSize, void *dwFuncAddr)
{
	DWORD
		dwOldProtect,
		dwInstructionSize = (opCodeSize + sizeof(DWORD)),
		dwDistance = (((DWORD)dwFuncAddr - dwAddress) - dwInstructionSize);

	BYTE
		*indirection = (BYTE*)malloc(opCodeSize + sizeof(DWORD));

	fflush(stdin);
	memcpy((BYTE*)&indirection[0], opCode, opCodeSize);

	memcpy((BYTE*)&indirection[opCodeSize], &dwDistance, sizeof(DWORD));

	VirtualProtect((LPVOID)dwAddress, dwInstructionSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	memcpy((DWORD*)dwAddress, indirection, dwInstructionSize);

	VirtualProtect((LPVOID)dwAddress, dwInstructionSize, dwOldProtect, &dwOldProtect);
}

__forceinline void FillWithNop(DWORD dwAddress, DWORD dwSize)
{	
	DWORD dwOldProtect;
	BYTE *nop = (BYTE*)malloc(dwSize);
	VirtualProtect((LPVOID)dwAddress, dwSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	for(i = 0; i < dwSize; i++)
        nop[i] = 0x90;

    memcpy((DWORD*)dwAddress, &nop[0], dwSize);
	VirtualProtect((LPVOID)dwAddress, dwSize, dwOldProtect, &dwOldProtect);
}

__forceinline void JMP_NEAR(DWORD dwAddress, void *dwFuncAddr)
{
	BYTE jmp = 0xE9;
	BuildIndirection(dwAddress, &jmp, 1, dwFuncAddr);
}

__forceinline void JGE_NEAR(DWORD dwAddress, void *dwFuncAddr)
{
	BYTE jge[2] = { 0x0F, 0x8D };
	BuildIndirection(dwAddress, jge, 2, dwFuncAddr);
}


__forceinline void JG_NEAR(DWORD dwAddress, void *dwFuncAddr)
{
	BYTE jg[2] = { 0x0F, 0x8F };
	BuildIndirection(dwAddress, jg, 2, dwFuncAddr);
}

__forceinline void JNZ_NEAR(DWORD dwAddress, void *dwFuncAddr)
{
	BYTE jnz[2] = { 0x0F, 0x85 };
	BuildIndirection(dwAddress, jnz, 2, dwFuncAddr);
}

__forceinline void CALL_NEAR(DWORD dwAddress, void *dwFuncAddr)
{
	BYTE call = 0xE8;
	BuildIndirection(dwAddress, &call, 1, dwFuncAddr);
}

__forceinline void WriteInConsole(const char *frmt_text, ...)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD nWritten;
    char text[1024];

    va_list pArgs;
    va_start(pArgs, frmt_text);
    vsprintf(text, frmt_text, pArgs);
    va_end(pArgs);

    WriteConsole(hConsole, text, strlen(text), &nWritten, NULL);
}

__forceinline void FixIOHandles()
{
    /* Output fix */
    int outParam = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    FILE *stdout_stream = _fdopen(outParam, "w");

    *stdout = *stdout_stream;

    /* Input fix */
    inParam = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
    stdin_stream = _fdopen(inParam, "r");

    *stdin = *stdin_stream;
}

__forceinline void CreateConsole()
{
    AllocConsole();
    FixIOHandles();

    /*while(TRUE)
    {
        WORD cmd;
        scanf("%x", &cmd);

        execute_command(cmd);
    }*/
}

