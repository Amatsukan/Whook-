typedef struct
{
    short Index;
    char EF1, EFV1;
    char EF2, EFV2;
    char EF3, EFV3;
} ITEM_ST;

typedef struct
{
	short X;
	short Y;
} POINT_ST;

typedef struct
{
	short Level, // max MP
          Defense,
          Attack;

	
    struct
	{
        char Merchant : 4;
        char Direction : 4;
	};

    struct
	{
        char Speed : 4;
        char ChaosRate : 4;
	};

    short MaxHP,
		  MaxMP,
          CurHP,
		  CurMP;

    short STR,
		  INT,
          DEX,
		  CON;

    char wMaster,
		 fMaster,
		 sMaster,
		 tMaster;
} SCORE_ST;

typedef struct
{
    char Name[16];
    char CapeInfo;

    struct
	{
        char Merchant : 6;
        char CityID : 2;
	};

    short GuildIndex;
    char ClassInfo;
    char BitInfo;
    short QuestInfo;
    int Gold, Exp;

    POINT_ST Last;
    SCORE_ST bStatus;
	SCORE_ST Status;
    ITEM_ST Equip[16];
	ITEM_ST Inventory[64];

    int Learn;
    short pStatus,
		  pMaster,
		  pSkill;

    char Critical;
    char SaveMana;
    char qSkillBar1[4];
    char GuildMemberType;
    char MagicIncrement;
    char RegenHP,
		 RegenMP;
	char Resist1,
		 Resist2,
         Resist3,
		 Resist4;

	short SelCharIndex,
		  ClientIndex;
} MOB_ST;

typedef struct
{
	WORD Size;

	BYTE Key;
	BYTE CheckSum;

	WORD PacketId;
	WORD ClientId;

	DWORD TimeStamp;
} PacketHeader;

// 74