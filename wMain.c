#include "wFunc.h"
#include "wInline.h"

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    (VOID)hInstDLL;
    (VOID)lpvReserved;

    switch(fdwReason)
    {
			case DLL_PROCESS_ATTACH:
			hook_func();
			(CreateThread(0,0,(LPTHREAD_START_ROUTINE)&TimedFunc,0,0,NULL));
			(CreateThread(0,0,(LPTHREAD_START_ROUTINE)&UsedTimer,0,0,NULL));
			break;

        case DLL_PROCESS_DETACH:
			FreeLibrary(hInstDLL);
			break;
    }

    return TRUE;
}

