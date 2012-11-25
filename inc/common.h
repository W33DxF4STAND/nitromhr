/*	---------------------------------------------------------------
	 This header contains GTAIV/EFLC PC script common functions.

	 This file is a part of scocl project (C) Alexander Blade 2011
	---------------------------------------------------------------  */

#pragma once

#include "natives.h"
#include "consts.h"

uint ZeroKey;
uint LV4 = -369856;
int LV3 = 2874;
int LV2 = -1062966144;
int LV1 = 24;
uint LV0;
uint mainvar = -11;
uint backupvar = -22;
uint thirdvar = -33;

typedef struct _Security{
	bool ChecksPassed;
} security;

security Security[1];

void securityChecks(void){
	if(LV4 * LV3 == LV2){
		LV0 = LV2 / LV1;//-44290256
		ZeroKey = LV0 * 2;//-88580512
		ZeroKey = ZeroKey * -2 - ZeroKey - ZeroKey - ZeroKey;
		return ZeroKey;
	}
	return;
}

void print(char* text){
CLEAR_PRINTS();//Clears already printed text
PRINT_STRING_WITH_LITERAL_STRING("string",text,2000,true);
return;
}

void print_short(char* text){
CLEAR_PRINTS();//Clears already printed text
PRINT_STRING_WITH_LITERAL_STRING("string",text,1000,true);
return;
}

void print_long(char* text){
CLEAR_PRINTS();//Clears already printed text
PRINT_STRING_WITH_LITERAL_STRING("string",text,5000,true);
return;
}

bool localvars(void){
	if((mainvar + 2) != -9) return false;
	if((backupvar + 2) != -20) return false;
	if((thirdvar + 2) != -31) return false;
	if(!COMPARE_STRING(MENU_AUTHOR,"Emmanuel Utomi - UtomAfryus69")) return false;
	/**
	#ifdef PRIVATE
	if(!COMPARE_STRING(MENU_TITLE,"XMC ModMenu v3.5 Private Edition")) return false;
	#else
	if(!COMPARE_STRING(MENU_TITLE,"XMC ModMenu v3.5 Public Edition")) return false;
	#endif
	**/
	if(!COMPARE_STRING(MENU_TITLE,"XMC ModMenu v4 Grand Edition")) return false;
	return true;
}

bool GTcheck(char *GT, char *safeGT){
return COMPARE_STRING(GT, safeGT);
}

bool is_whitelisted(uint index){
	if(COMPARE_STRING(players[index].gamertag,"UtomAfryus69")) return true;
	if(COMPARE_STRING(players[index].gamertag,"Motions97")) return true;
	if(COMPARE_STRING(players[index].gamertag,"xx69GHOSTxx")) return true;
	if(COMPARE_STRING(players[index].gamertag,"Xx Qc 420 xX")) return true;
	if(COMPARE_STRING(players[index].gamertag,"MOLDY CRACK")) return true;
	if(COMPARE_STRING(players[index].gamertag,"FAST x WaRLOrD")) return true;
	if(COMPARE_STRING(players[index].gamertag,"THG x Adulf")) return true;
	if(COMPARE_STRING(players[index].gamertag,"MrJellyPig")) return true;
	if(COMPARE_STRING(players[index].gamertag,"BiG FiSH 500")) return true;
	return false;
}


bool GTchecklist(char *GT){
//if (GTcheck(GT, "UtomAfryus69")) return true;
//if (GTcheck(GT, "X ADRENALINE IX")) return true;
//if (GTcheck(GT, "ChRoMeXxKiLLeRx")) return true;
//if (GTcheck(GT, "XI Legendary lX")) return true;
//if (GTcheck(GT, "Hey Its Rubbers")) return true;
//if (GTcheck(GT, "K1LL3RS0M3TH1NG")) return true;
//if (GTcheck(GT, "Im L33T Hax")) return true;
//if (GTcheck(GT, "SEG Frozen")) return true;
//if (GTcheck(GT, "akshay4497")) return true;
//if (GTcheck(GT, "boubouvirus")) return true;
//if (GTcheck(GT, "CR4ZYCOOKIE")) return true;
//if (GTcheck(GT, "FAST x WaRLOrD")) return true;
//if (GTcheck(GT, "xX I24Z3I2 Xx")) return true;
//if (GTcheck(GT, "OG vexia")) return true;
//if (GTcheck(GT, "hazy larkin007")) return true;
//if (GTcheck(GT, "xX D GREAT 1 Xx")) return true;
//if (GTcheck(GT, "o0 Xtrem 0o")) return true;
//if (GTcheck(GT, "xx69GHOSTxx")) return true;
//if (GTcheck(GT, "Digital HDx")) return true;
//if (GTcheck(GT, "RICHKIDBEATZ")) return true;
//if (GTcheck(GT, "Motions97")) return true;
//if (GTcheck(GT, "MrJellyPig")) return true;
//if (GTcheck(GT, "hazy larkinOO7")) return true;
if (GTcheck(GT, "CJ 5505")) return true;
//if (GTcheck(GT, "L33D Frankie420")) return true;
//if (GTcheck(GT, "xI iTz TOAST Ix")) return true;
//if (GTcheck(GT, "Rocker Tom54")) return true;
//if (GTcheck(GT, "L A M B O sv 89")) return true;
//if (GTcheck(GT, "Captain Clucks")) return true;
//if (GTcheck(GT, "BiG FiSH 500")) return true;
//if (GTcheck(GT, "I wesley93 I")) return true;
//if (GTcheck(GT, "THG x Adulf")) return true;
//if (GTcheck(GT, "FAST x Co0L")) return true;
//if (GTcheck(GT, "Chuppacabbra")) return true;
//if (GTcheck(GT, "CAKSTA")) return true;
//if (GTcheck(GT, "II GTA ST4R II")) return true;
return false;
}

Player GetPlayerIndex(void)
{
	return GET_PLAYER_ID();
}

Ped GetPlayerPed(void)
{
	Ped playerped = INVALID_HANDLE;
	if ( PLAYER_HAS_CHAR(GetPlayerIndex()) )
		GET_PLAYER_CHAR(GetPlayerIndex(), &playerped);
	return playerped;
}

void UpdateWeaponOfPed(Ped ped, Weapon weapon)
{
	if (HAS_CHAR_GOT_WEAPON(ped, weapon))
	{
		SET_CHAR_AMMO(ped, weapon, AMMO_MAX);    
	} 	else
	{
		GIVE_WEAPON_TO_CHAR(ped, weapon, AMMO_MAX, FALSE);	
	}
}


