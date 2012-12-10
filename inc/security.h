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

bool is_admin(uint i){
	if(COMPARE_STRING(GET_PLAYER_NAME(i),"UtomAfryus69")) return true;
	if(COMPARE_STRING(GET_PLAYER_NAME(i),"xSAVAGEx HiT UP")) return true;
	if(COMPARE_STRING(GET_PLAYER_NAME(i),"xI iTz TOAST Ix")) return true;
	if(COMPARE_STRING(GET_PLAYER_NAME(i),"ThaRichKid1")) return true;
	if(COMPARE_STRING(GET_PLAYER_NAME(i),"L33D Frankie420")) return true;
	return false;
}

bool GTchecklist(char *GT){
//if (GTcheck(GT, "UtomAfryus69", 12)) return true;
//if (GTcheck(GT, "Soft Dusty", 10)) return true;
//if (GTcheck(GT, "XI Legendary lX")) return true;
//if (GTcheck(GT, "K1LL3RS0M3TH1NG")) return true;
//if (GTcheck(GT, "Im L33T Hax", 11)) return true;
//if (GTcheck(GT, "FAST x WaRLOrD", 14)) return true;
//if (GTcheck(GT, "Digital HDx", 11)) return true;
//if (GTcheck(GT, "ThaRichKid1", 11)) return true;
//if (GTcheck(GT, "HackinBlack", 11)) return true;
//if (GTcheck(GT, "Exploitable SQL", 15)) return true;
//if (GTcheck(GT, "Motions97", 9)) return true;
//if (GTcheck(GT, "RockStarsKing7", 14)) return true;
//if (GTcheck(GT, "RockStarsKing3", 14)) return true;
////if (GTcheck(GT, "MrJellyPig", 10)) return true;
//if (GTcheck(GT, "CJ 5505", 7)) return true;
if (GTcheck(GT, "L33D Frankie420", 15)) return true;
//if (GTcheck(GT, "xI iTz TOAST Ix", 15)) return true;
//if (GTcheck(GT, "BiG FiSH 500", 12)) return true;
//if (GTcheck(GT, "FAST x Co0L", 11)) return true;
//if (GTcheck(GT, "Chuppacabbra", 12)) return true;
return false;
}

uint key1 = -999983304;
uint key2 = -999967879;
uint key3 = -999970539;
uint key4 = -999996407;
uint key5 = -999977679;
uint key6 = -999974528;
uint key7 = -999967828;
uint key8 = -999973733;
uint key9 = -999989294;
uint key10 = -999988048;
uint key11 = -999986622;
uint key12 = -999994641;
uint key13 = -999977393;
uint key14 = -999996696;
uint key15 = -999971162;
uint key16 = -999973811;
uint key17 = -999973583;
uint key18 = -999976455;
uint key19 = -999976388;
uint key20 = -999994830;
uint key21 = -999981353;
uint key22 = -999969749;
uint key23 = -999991685;
uint key24 = -999969075;
uint key25 = -999986192;
uint key26 = -999979849;
uint key27 = -999973523;
uint key28 = -999995004;
uint key29 = -999977982;
uint key30 = -999975860;
uint key31 = -999988685;
uint key32 = -999976083;
uint key33 = -999985690;
uint key34 = -999975541;
uint key35 = -999976577;
uint key36 = -999971883;
uint key37 = -999993271;
uint key38 = -999976566;
uint key39 = -999982568;
uint key40 = -999971652;
uint key41 = -999998932;
uint key42 = -999998379;
uint key43 = -999977639;
uint key44 = -999975081;
uint key45 = -999988379;
uint key46 = -999972504;
uint key47 = -999985230;
uint key48 = -999987059;
uint key49 = -999985892;
uint key50 = -999972810;
uint key51 = -999991003;
uint key52 = -999991941;
uint key53 = -999986608;
uint key54 = -999999323;
uint key55 = -999995958;
uint key56 = -999972880;
uint key57 = -999999409;
uint key58 = -999970929;
uint key59 = -999983540;
uint key60 = -999976207;
uint key61 = -999971007;
uint key62 = -999992509;
uint key63 = -999997334;
uint key64 = -999991498;
uint key65 = -999984482;
uint key66 = -999979006;
uint key67 = -999968905;
uint key68 = -999974997;
uint key69 = -999978573;
uint key70 = -999979902;
uint key71 = -999983910;
uint key72 = -999983632;
uint key73 = -999970783;
uint key74 = -999991697;
uint key75 = -999970673;
uint key76 = -999993639;
uint key77 = -999997858;
uint key78 = -999979291;
uint key79 = -999990876;
uint key80 = -999993618;
uint key81 = -999970253;
uint key82 = -999975177;
uint key83 = -999985475;
uint key84 = -999991571;
uint key85 = -999997636;
uint key86 = -999994325;
uint key87 = -999991664;
uint key88 = -999968700;
uint key89 = -999973014;
uint key90 = -999994116;
uint key91 = -999978902;
uint key92 = -999976553;
uint key93 = -999988348;
uint key94 = -999977641;
uint key95 = -999992152;
uint key96 = -999984320;
uint key97 = -999976030;
uint key98 = -999978210;
uint key99 = -999979713;
uint key100 = -999967799;

bool check_keys(void){
	 if((key1 + 20641) != -999962663) return false;
	 if((key2 + 7019) != -999960860) return false;
	 if((key3 + 15047) != -999955492) return false;
	 if((key4 + 4590) != -999991817) return false;
	 if((key5 + 30399) != -999947280) return false;
	 if((key6 + 11955) != -999962573) return false;
	 if((key7 + 4152) != -999963676) return false;
	 if((key8 + 21518) != -999952215) return false;
	 if((key9 + 15964) != -999973330) return false;
	 if((key10 + 17810) != -999970238) return false;
	 if((key11 + 19807) != -999966815) return false;
	 if((key12 + 32315) != -999962326) return false;
	 if((key13 + 18007) != -999959386) return false;
	 if((key14 + 14061) != -999982635) return false;
	 if((key15 + 18766) != -999952396) return false;
	 if((key16 + 12573) != -999961238) return false;
	 if((key17 + 19861) != -999953722) return false;
	 if((key18 + 6606) != -999969849) return false;
	 if((key19 + 15452) != -999960936) return false;
	 if((key20 + 6336) != -999988494) return false;
	 if((key21 + 6528) != -999974825) return false;
	 if((key22 + 24548) != -999945201) return false;
	 if((key23 + 11940) != -999979745) return false;
	 if((key24 + 20242) != -999948833) return false;
	 if((key25 + 27779) != -999958413) return false;
	 if((key26 + 32766) != -999947083) return false;
	 if((key27 + 30340) != -999943183) return false;
	 if((key28 + 20073) != -999974931) return false;
	 if((key29 + 3216) != -999974766) return false;
	 if((key30 + 12436) != -999963424) return false;
	 if((key31 + 18208) != -999970477) return false;
	 if((key32 + 29690) != -999946393) return false;
	 if((key33 + 22938) != -999962752) return false;
	 if((key34 + 12862) != -999962679) return false;
	 if((key35 + 20189) != -999956388) return false;
	 if((key36 + 4707) != -999967176) return false;
	 if((key37 + 29722) != -999963549) return false;
	 if((key38 + 10811) != -999965755) return false;
	 if((key39 + 26087) != -999956481) return false;
	 if((key40 + 5154) != -999966498) return false;
	 if((key41 + 29582) != -999969350) return false;
	 if((key42 + 3308) != -999995071) return false;
	 if((key43 + 19627) != -999958012) return false;
	 if((key44 + 11803) != -999963278) return false;
	 if((key45 + 11510) != -999976869) return false;
	 if((key46 + 6229) != -999966275) return false;
	 if((key47 + 31325) != -999953905) return false;
	 if((key48 + 8726) != -999978333) return false;
	 if((key49 + 2390) != -999983502) return false;
	 if((key50 + 24227) != -999948583) return false;
	 if((key51 + 31603) != -999959400) return false;
	 if((key52 + 4415) != -999987526) return false;
	 if((key53 + 27702) != -999958906) return false;
	 if((key54 + 24736) != -999974587) return false;
	 if((key55 + 24616) != -999971342) return false;
	 if((key56 + 24228) != -999948652) return false;
	 if((key57 + 10789) != -999988620) return false;
	 if((key58 + 14401) != -999956528) return false;
	 if((key59 + 15098) != -999968442) return false;
	 if((key60 + 8634) != -999967573) return false;
	 if((key61 + 3890) != -999967117) return false;
	 if((key62 + 21273) != -999971236) return false;
	 if((key63 + 12076) != -999985258) return false;
	 if((key64 + 10457) != -999981041) return false;
	 if((key65 + 30065) != -999954417) return false;
	 if((key66 + 15587) != -999963419) return false;
	 if((key67 + 3909) != -999964996) return false;
	 if((key68 + 3004) != -999971993) return false;
	 if((key69 + 27516) != -999951057) return false;
	 if((key70 + 31228) != -999948674) return false;
	 if((key71 + 2959) != -999980951) return false;
	 if((key72 + 19970) != -999963662) return false;
	 if((key73 + 27375) != -999943408) return false;
	 if((key74 + 29158) != -999962539) return false;
	 if((key75 + 28825) != -999941848) return false;
	 if((key76 + 4527) != -999989112) return false;
	 if((key77 + 7915) != -999989943) return false;
	 if((key78 + 27078) != -999952213) return false;
	 if((key79 + 30134) != -999960742) return false;
	 if((key80 + 22955) != -999970663) return false;
	 if((key81 + 14996) != -999955257) return false;
	 if((key82 + 3815) != -999971362) return false;
	 if((key83 + 7036) != -999978439) return false;
	 if((key84 + 23618) != -999967953) return false;
	 if((key85 + 24467) != -999973169) return false;
	 if((key86 + 4405) != -999989920) return false;
	 if((key87 + 6725) != -999984939) return false;
	 if((key88 + 26018) != -999942682) return false;
	 if((key89 + 5269) != -999967745) return false;
	 if((key90 + 19907) != -999974209) return false;
	 if((key91 + 24753) != -999954149) return false;
	 if((key92 + 19041) != -999957512) return false;
	 if((key93 + 19402) != -999968946) return false;
	 if((key94 + 2374) != -999975267) return false;
	 if((key95 + 8738) != -999983414) return false;
	 if((key96 + 27124) != -999957196) return false;
	 if((key97 + 31079) != -999944951) return false;
	 if((key98 + 14999) != -999963211) return false;
	 if((key99 + 30015) != -999949698) return false;
	 if((key100 + 16697) != -999951102) return false;
 }