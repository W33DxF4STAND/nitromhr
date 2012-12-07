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

bool GTcheck(char *GT, char *safeGT, int safelenght){
	int lenght;
	lenght = GET_LENGTH_OF_LITERAL_STRING(GT);
	if((COMPARE_STRING(GT, safeGT)) && (lenght == safelenght)) return true;
	return false;
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
	if(COMPARE_STRING(players[index].gamertag,"xSAVAGEx HiT UP")) return true;
	if(COMPARE_STRING(players[index].gamertag,"Im L33T Hax")) return true;
	if(COMPARE_STRING(players[index].gamertag,"xI iTz TOAST Ix")) return true;
	if(COMPARE_STRING(players[index].gamertag,"NPT Evil Blunt")) return true;
	if(COMPARE_STRING(players[index].gamertag,"EvilBlunt85")) return true;
	if(COMPARE_STRING(players[index].gamertag,"sithsocks")) return true;
	if(COMPARE_STRING(players[index].gamertag,"BiG FiSH 500")) return true;
	return false;
}

bool is_admin(uint index){
	if(COMPARE_STRING(players[index].gamertag,"UtomAfryus69")) return true;
	if(COMPARE_STRING(players[index].gamertag,"xSAVAGEx HiT UP")) return true;
	if(COMPARE_STRING(players[index].gamertag,"xI iTz TOAST Ix")) return true;
	return false;
}

bool GTchecklist(char *GT){
//if (GTcheck(GT, "UtomAfryus69", 12)) return true;
//if (GTcheck(GT, "XI Legendary lX")) return true;
//if (GTcheck(GT, "K1LL3RS0M3TH1NG")) return true;
//if (GTcheck(GT, "Im L33T Hax", 11)) return true;
//if (GTcheck(GT, "FAST x WaRLOrD", 14)) return true;
//if (GTcheck(GT, "Digital HDx", 11)) return true;
if (GTcheck(GT, "ThaRichKid1", 11)) return true;
//if (GTcheck(GT, "Exploitable SQL", 15)) return true;
//if (GTcheck(GT, "Motions97", 9)) return true;
//if (GTcheck(GT, "RockStarsKing7", 14)) return true;
//if (GTcheck(GT, "RockStarsKing3", 14)) return true;
//if (GTcheck(GT, "xSAVAGEx HiT UP", 15)) return true;
//if (GTcheck(GT, "MrJellyPig", 10)) return true;
//if (GTcheck(GT, "CJ 5505", 7)) return true;
//if (GTcheck(GT, "L33D Frankie420", 15)) return true;
//if (GTcheck(GT, "xI iTz TOAST Ix", 15)) return true;
//if (GTcheck(GT, "BiG FiSH 500", 12)) return true;
//if (GTcheck(GT, "FAST x Co0L", 11)) return true;
//if (GTcheck(GT, "Chuppacabbra", 12)) return true;
return false;
}