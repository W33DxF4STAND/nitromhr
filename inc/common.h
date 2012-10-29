/*	---------------------------------------------------------------
	 This header contains GTAIV/EFLC PC script common functions.

	 This file is a part of scocl project (C) Alexander Blade 2011
	---------------------------------------------------------------  */

#pragma once

#include "natives.h"
#include "consts.h"

void print(char* text){
CLEAR_PRINTS();//Clears already printed text
PRINT_STRING_WITH_LITERAL_STRING("string",text,2000,true);
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
	return true;
}

#ifdef PRIVATE
bool GTcheck(char *GT, char *safeGT){
return COMPARE_STRING(GT, safeGT);
}

bool GTchecklist(char *GT){
//if (GTcheck(GT, "UtomAfryus69")) return true;
//if (GTcheck(GT, "X ADRENALINE IX")) return true;
//if (GTcheck(GT, "Lhna")) return true;
//if (GTcheck(GT, "XI Legendary lX")) return true;
//if (GTcheck(GT, "K1LL3RS0M3TH1NG")) return true;
//if (GTcheck(GT, "Im L33T Hax")) return true;
//if (GTcheck(GT, "akshay4497")) return true;
//if (GTcheck(GT, "boubouvirus")) return true;
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
if (GTcheck(GT, "MrJellyPig")) return true;
//if (GTcheck(GT, "CJ 5505")) return true;
//if (GTcheck(GT, "L A M B O sv 89")) return true;
//if (GTcheck(GT, "Captain Clucks")) return true;
//if (GTcheck(GT, "BiG FiSH 500")) return true;
//if (GTcheck(GT, "I wesley93 I")) return true;
return false;
}
#endif
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


