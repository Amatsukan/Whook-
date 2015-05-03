#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <WinBase.h>
#include <wininet.h>
#include <time.h>
#pragma comment(lib, "Wininet.lib")
#pragma comment("Wininet")

short chat_index;
short sec_x, sec_y;
short sec2_x, sec2_y;
short mhit;
short inject;
short set_char;
short macro;
short autoparty;
short part_id;
short set_x, set_y;
short speed_id;
short num;
short pt_id;
short id11,id12,id13,id14;
char pt_name[16];

char pak[2048];
char msg_pak[2048];
char fk_pak[2048];
char fk2_pak[2048];

BOOL onIgnorePackets;
BOOL cInv;
BOOL cOneHit;
BOOL cAtkInv;
BOOL cFree;
BOOL cRevive;
BOOL cIndex;
BOOL cTimer;
BOOL cShutDown;
BOOL cFastKill;
BOOL cRange;
BOOL cSpeed;
BOOL cDrop;
BOOL cShowBuffer;
BOOL cAutoLog;
BOOL cWall;
BOOL cSpeedMove;
BOOL cMacroUp;
BOOL timer_speed;
BOOL timer_fastkill;

DWORD OldProtect;

char pass[16];
char id[16];
char pass2[16];
char id2[16];
char clogin[16];
char plog1[16];
char plog2[16];
char plog3[16];
char url[120];

short DropList[256];

HANDLE hConsoleHandle;
extern char pak[2048];
extern char msg_pak[2048];


#define SetByte(val,offset) *(char*)&pak[offset]=(char)(val)
#define SetShort(val,offset) *(short*)&pak[offset]=(short)(val)
#define SetInt(val,offset) *(int*)&pak[offset]=(int)(val)
#define SetStr(val,offset) strcpy(&pak[offset], val)
#define aSetShort(val,offset) *(short*)&fk_pak[offset]=(short)(val)
#define bSetShort(val,offset) *(short*)&fk2_pak[offset]=(short)(val)

#define YELLOW		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define LBLUE		FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define LRED		FOREGROUND_RED | FOREGROUND_INTENSITY
#define LGREEN		FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define LMAGENTA	FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define WHITE		FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define LCYAN		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define GREY		0 | FOREGROUND_INTENSITY	

#define cThread(name) CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)name, NULL, 0, 0);

void (__stdcall *MoveCharacter)(int,char*);
void (__stdcall *ShowGameMessage)(char*);
void (__cdecl *SendPacket)(char*, int);

void TimerFunc();
int Command(char*, short);
void PacketControl(char*, int*, int);
void Hook_TimerFunc();
void Hook_Chkpak_Send();
void Hook_Chkpak_Recv();
void Hook_Command();

/* Hack's */
void sAction(int x, int y);
void sTeleport(int x, int y);
void cTeleport(int x, int y);
void buff_hack_on();
void buff_hack_off();
void inv_hack_on();
void inv_hack_off();
void revive_hack();
void party_hack();
void PacketControl_fastkill(char *Data, int Type);
void do_fastkill();
void range_hack_on();
void range_hack_off();
void wall_hack_on();
void wall_hack_off();
void speed_hack_on(int speed_id);
void speed_hack_off();
void party_hack(int index, char *nick);
void AttackPlayer(int type, int sk_ID, BOOL isOneHit, int other_ID);
void Check_AutoDrop(char *Data, short Type);

/* End */

void ShowMsg(int color, char *s, ...);
void CliMsg(int delay, char *msg);
void hook_func();
void PrintTime();
void WINAPI TimedFunc();
void WINAPI UsedTimer();