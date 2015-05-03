#include "wAddr.h"
#include "wInline.h"
#include "wTypes.h"
#include "wFunc.h"

int Command(char *cmd, short clientid)
{
	if(*cmd != '#')
        return FALSE;

	if(strncmp(cmd, "#autoparty", 10) == 0)
	{
		sscanf(cmd, "#autoparty %d %s", &pt_id, &pt_name[0]);
		ShowMsg(0xFF99FF22, "#autoparty - %d %s", pt_id, pt_name);
		return TRUE;
	}

	if(_stricmp(cmd, "#macroupon") == 0)
	{
		cMacroUp = TRUE;
		ShowMsg(0xFF99FF22, "#macroup - Macro Up ON.");
		return TRUE;
	}

	else if(_stricmp(cmd, "#macroupoff") == 0)
	{
		cMacroUp = FALSE;
		ShowMsg(0xFF99FF22, "#macroup - Macro Up OFF.");
		return TRUE;
	}

	if(_stricmp(cmd, "#revon") == 0)
	{
		cRevive = TRUE;
		ShowMsg(0xFF99FF22, "#rev - Revive ON.");
		return TRUE;
	}

	else if(_stricmp(cmd, "#revoff") == 0)
	{
		cRevive = FALSE;
		ShowMsg(0xFF99FF22, "#rev - Revive OFF.");
		return TRUE;
	}

	if(_stricmp(cmd, "#indexon") == 0)
    {
        cIndex = TRUE;
		ShowMsg(0xFF99FF22, "#index - Index ON.");
		return TRUE;
    }
    else if(_stricmp(cmd, "#indexoff") == 0)
    {
        cIndex = FALSE;
		ShowMsg(0xFF99FF22, "#index - Index OFF.");
		return TRUE;
    }

	if(_stricmp(cmd, "#atkinvon") == 0)
	{
		cAtkInv = TRUE;
		ShowMsg(0xFF99FF22, "#atkinv - Atk Inv ON.");
		return TRUE;
	}

	else if(_stricmp(cmd, "#atkinvoff") == 0)
	{
		cAtkInv = FALSE;
		ShowMsg(0xFF99FF22, "#atkinv - Atk Inv OFF.");
		return TRUE;
	}

	if(strncmp(cmd, "#chat", 5) == 0)
	{
		sscanf(cmd, "#chat %d", &chat_index);

		if(chat_index <= 1000)
		{
			ShowMsg(0xFF99FF22, "#chat - Fake Chat: %d", chat_index);
			return TRUE;
		}

		chat_index = 0;
		ShowMsg(0xFF99FF22, "#chat - Invalid Fake Chat");
		return TRUE;
	}

	else if(_stricmp(cmd, "#dropon") == 0)
	{
		cDrop = TRUE;
		ShowMsg(0xFF99FF22, "#drop - Auto Drop ON.");
		return TRUE;
	}

	else if(_stricmp(cmd, "#dropoff") == 0)
	{
		cDrop = FALSE;
		ShowMsg(0xFF99FF22, "#drop - Auto Drop OFF.");
		return TRUE;
	}

	if(strncmp(cmd, "#list", 5) == 0)
	{
		short add_it;
		if(sscanf(cmd, "#list add %d", &add_it))
		{
			for(i = 0; i < 256; i++)
			{
				if(DropList[i] == add_it)
				{
					ShowMsg(0xFF99FF22, "#drop - %d ja esta na lista.", add_it);
					return TRUE;
				}

				else if(DropList[i] == 0)
				{
					DropList[i] = add_it;
					ShowMsg(0xFF99FF22, "#drop - %d adicionado a lista.", add_it);
					return TRUE;
				}

				else if(i == 256)
				{
					ShowMsg(0xFF99FF22, "#drop - Lista cheia.", add_it);
					return TRUE;
				}
			}
		}

		else if(sscanf(cmd, "#list remove %d", &add_it))
		{
			for(i = 0; i < 256; i++)
			{
				if(DropList[i] == add_it)
				{
					DropList[i] = 0;
					ShowMsg(0xFF99FF22, "#drop - %d removido da lista.", add_it);
					return TRUE;
				}

				if(i == 256)
				{
					ShowMsg(0xFF99FF22, "#drop - %d não está na lista.", add_it);
					return TRUE;
				}
			}			
		}

		else if(sscanf(cmd, "#list clear %d", &add_it))
		{
			ZeroMemory(DropList, 256);
			ShowMsg(0xFF99FF22, "#drop - Lista apagada.", add_it);
			return TRUE;
		}
		
		return TRUE;
	}

	if(strncmp(cmd, "#party", 6) == 0)
    {
        int ret, index;
		char party_name[16];

        ret = sscanf(cmd, "#party %d %s", &index, &party_name[0]);
		if(ret == 2)
		{
			party_hack(index, party_name);
			ShowMsg(0xFF99FF22, "#party - Party ON.");
			return TRUE;
		}

		ShowMsg(0xFF99FF22, "#party - Valores invalidos.");
		return TRUE;
    }

	if(_stricmp(cmd, "#onehiton") == 0)
    {
        cOneHit = TRUE;
		*(char*)onehit_addr = 0x5E;
		ShowMsg(0xFF99FF22, "#onehit - OneHit ON.");
		return TRUE;
    }
    else if(_stricmp(cmd, "#onehitoff") == 0)
    {
        cOneHit = FALSE;
		*(char*)onehit_addr = 0x48;
		ShowMsg(0xFF99FF22, "#onehit - OneHit OFF.");
		return TRUE;
    }
	
	if(_stricmp(cmd, "#wallon") == 0)
	{
		wall_hack_on();
		ShowMsg(0xFF99FF22, "#wall - Wall Hack ON.");
		return TRUE;
	}
	else if(_stricmp(cmd, "#walloff") == 0)
	{
		wall_hack_off();
		ShowMsg(0xFF99FF22, "#wall - Wall Hack OFF.");
		return TRUE;
	}

	if(_stricmp(cmd, "#rangeon") == 0)
    {
		range_hack_on();
		ShowMsg(0xFF99FF22, "#range - Range Hack ON.");
		return TRUE;
    }
    else if(_stricmp(cmd, "#rangeoff") == 0)
    {
		range_hack_off();
        ShowMsg(0xFF99FF22, "#range - Range Hack OFF.");
		return TRUE;
    }

	if(_stricmp(cmd, "#buffhackon") == 0)
	{
		buff_hack_on();
		ShowMsg(0xFF99FF22, "#buffhack - Buff Hack ON.");
		return TRUE;
	}

	if(_stricmp(cmd, "#buffhackoff") == 0)
	{
		buff_hack_off();
		ShowMsg(0xFF99FF22, "#buffhack - Buff Hack OFF.");
		return TRUE;
	}

	if(_stricmp(cmd, "#secon") == 0)
    {
		sec_x = GetPosX();
		sec_y = GetPosY();
		ShowMsg(0xFF99FF22, "#sec - Set Coord ON.");
		return TRUE;
    }
    else if(_stricmp(cmd, "#secoff") == 0)
    {
        sec_x = 0;
		sec_y = 0;
		ShowMsg(0xFF99FF22, "#sec - Set Coord OFF.");
		return TRUE;
    }

	if(strncmp(cmd, "#smo", 4) == 0)
    {
		int delay;
		sscanf(cmd, "#smo %d", &delay);
		*(BYTE*)0x0495F97 = 0xEB;
		*(short*)0x0456320 = delay;
		ShowMsg(0xFF99FF22, "#smo - %d", delay);
		return TRUE;
    }

	if(strncmp(cmd, "#speedatk", 9) == 0)
    {
		sscanf(cmd, "#speedatk %d", &speed_id);

		if(speed_id == 1000) speed_hack_off(), timer_speed = false;
		if(speed_id < 1000 && speed_id >= 0) speed_hack_on(speed_id), timer_speed = true;

		ShowMsg(0xFF99FF22, "#speedatk - Speed Delay: %d", speed_id);
		return TRUE;
    }

	if(strncmp(cmd, "#moved", 6) == 0)
    {
		short ret, x, y;
        ret = sscanf(cmd, "#moved %d %d", &x, &y);
        if(ret != 2 || x <= 0 || x >= 4096 || y <= 0 || y >= 4096)
        {
			ShowMsg(0xFF99FF22, "#moved - Coordenada INVALIDA.");
            return TRUE;
        }

		sTeleport( x, y);
		ShowMsg(0xFF99FF22, "#moved - Moved to X: %d Y: %d.", x, y);
		return TRUE;
    }

	if(strncmp(cmd, "#move", 5) == 0)
    {
        short ret, x, y;
        ret = sscanf(cmd, "#move %d %d", &x, &y);
        if(ret != 2 || x <= 0 || x >= 4096 || y <= 0 || y >= 4096)
        {
            ShowMsg(0xFF99FF22, "#move - Coordenada INVALIDA.");
            return TRUE;
        }

		sTeleport(x, y);
		ShowMsg(0xFF99FF22, "#moved - Moved to X: %d Y: %d.", x, y);
		return TRUE;
    }

	if(_stricmp(cmd, "#bau") == 0)
	{
		__asm
		{
			MOV EAX,ptrdat
			MOV EDX,DWORD PTR DS:[EAX]

			PUSH 1
			MOV ECX,EDX
			MOV EAX,cargo_addr1
			CALL EAX
		}

		ShowMsg(0xFF99FF22, "#bau - Bau aberto.");
		return true;
	}

	if(strncmp(cmd, "#freeon", 7) == 0)
	{
		cFree = TRUE;
		ShowMsg(0xFF99FF22, "#free - Seu WYD está mais leve.");
		return TRUE;
	}

	if(strncmp(cmd, "#freeoff", 8) == 0)
	{
		cFree = FALSE;
		ShowMsg(0xFF99FF22, "#free - Seu WYD foi normalizado.");
		return TRUE;
	}
	
	if(_stricmp(cmd, "#fastkillon") == 0)
	{
		ZeroMemory(fk_pak, 168);
		aSetShort(168, 0);
		aSetShort(0x39D, 4);
		aSetShort(GetClientID(), 6);
		aSetShort(GetPosX(), 34);
		aSetShort(GetPosY(), 36);
		aSetShort(GetPosX(), 38);
		aSetShort(GetPosY(), 40);
		aSetShort(GetClientID(), 42);
		aSetShort(4, 46);
		aSetShort(0xFF, 52);
		aSetShort(0xFF, 53);
		aSetShort(0xFF, 54);
		aSetShort(0xFF, 55);
		aSetShort(0xFF, 56);
		aSetShort(0xFF, 57);
		aSetShort(0xFE, 64);
		aSetShort(0xFF, 65);
		aSetShort(0xFF, 66);
		aSetShort(0xFF, 67);

		timer_fastkill = true;
		cFastKill = TRUE;
		ShowMsg(0xFF99FF22, "#fastkill - Fast Kill ON.");
		return TRUE;
	}

	if(_stricmp(cmd, "#fastkilloff") == 0)
	{
		cFastKill = FALSE;
		timer_fastkill = false;
		ShowMsg(0xFF99FF22, "#fastkill - Fast Kill OFF.");
		return TRUE;
	}

	if(_stricmp(cmd, "#invon") == 0)
	{
		inv_hack_on();
		ShowMsg(0xFF99FF22, "#inv - Invisibilidade ON.");
		return TRUE;
	}

	if(_stricmp(cmd, "#invoff") == 0)
	{
		inv_hack_off();
		ShowMsg(0xFF99FF22, "#inv - Invisibilidade OFF.");
		return TRUE;
	}

	if(_stricmp(cmd, "#speedmoveon") == 0)
	{
		cSpeedMove = TRUE;
		ShowMsg(0xFF99FF22, "#speedmove - Speed Move ON.");
		return TRUE;
	}

	if(_stricmp(cmd, "#speedmoveoff") == 0)
	{
		cSpeedMove = FALSE;
		ShowMsg(0xFF99FF22, "#speedmove - Speed Move OFF.");
		return TRUE;
	}

	if(strncmp(cmd, "#kill", 5) == 0)
	{
		short other_ID, sk_ID;
		if(sscanf(cmd, "#kill mag %hd %hd", &other_ID, &sk_ID))
		{
			AttackPlayer(2, sk_ID, true, other_ID);
			ShowMsg(0xFF99FF22, "#kill - Kill Mag Mob %d", other_ID);
			return TRUE;
		}

		else if(sscanf(cmd, "#kill dam %hd", &other_ID))
		{
			AttackPlayer(1, 0, true, other_ID);
			ShowMsg(0xFF99FF22, "#kill - Kill Dam Mob %d", other_ID);
			return TRUE;
		}

		return TRUE;
	}

	if(strncmp(cmd, "#atk", 4) == 0)
	{
		short other_ID, sk_ID;
		if(sscanf(cmd, "#atk mag %hd %hd", &other_ID, &sk_ID))
		{
			AttackPlayer(2, sk_ID, false, other_ID);
			ShowMsg(0xFF99FF22, "#atk - Atk Mag Mob %d", other_ID);
			return TRUE;
		}

		if(sscanf(cmd, "#atk dam %hd", &other_ID))
		{
			AttackPlayer(1, 0, false, other_ID);
			ShowMsg(0xFF99FF22, "#atk - Atk Dam Mob %d", other_ID);
			return TRUE;
		}
		return TRUE;
	}

	ShowMsg(0xFF99FF22, "Nenhum comando foi encontrado.");
    return TRUE;
}