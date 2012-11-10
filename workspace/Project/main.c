//Leave undefined unless you know what your doing
//#define PRIVATE 
#define ENGLISH
//#define SPANISH
//#define FRENCH
//#define PC

#ifdef PRIVATE
#define MENU_TITLE "XMC ModMenu v3 Private Edition"
#else
#define MENU_TITLE "XMC ModMenu v3 Public Edition"
#endif

#define MENU_AUTHOR "Emmanuel Utomi - UtomAfryus69"

#include <natives.h>
#include <vars.h>
#include <common.h>
#include <consts.h>
#include <types.h>
#include <strings.h>

#ifdef FRENCH
#include "menu_items_french.c"
#endif

#ifdef ENGLISH
#include "menu_items.c"
#endif

#ifdef SPANISH
#include "menu_items_spanish.c"
#endif

#include "menu_functions.c"
#include "engine.c"

void main(void){
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	show_menu = false;
	menu_setup();
	
#ifdef PRIVATE
	//gold
	s_r = 218;
	s_g = 165;
	s_b = 32;
#else
	//blue
	s_r = 0;
	s_g = 191;
	s_b = 255;
#endif

	Vehicle tmp,tmp2;
	
	if(drive_free){
		SWITCH_ROADS_OFF(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
		SWITCH_AMBIENT_PLANES(false);
	}
	else{
		SWITCH_ROADS_ON(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
		SWITCH_AMBIENT_PLANES(true);
	}	
	
	if(neverwanted)
		SET_MAX_WANTED_LEVEL(0);

	#ifdef PRIVATE
	if(!GTchecklist(GET_PLAYER_NAME(GET_PLAYER_ID()))){
	print_long("~b~LOL Unregistered ~r~GT!");
	WAIT(500);
	WARP_CHAR_INTO_CAR_AS_PASSENGER(GetPlayerPed(), ClosestCar, 1);
	WAIT(0);
	}
	#endif

	print_long("~b~Xmc ~b~Modmenu ~b~- ~g~Emmanuel ~g~Utomi ~b~AKA ~g~UtomAfryus69");
	
	securityChecks();
	int hiddenGlobalInt = ZeroKey;

	if(ZeroKey == hiddenGlobalInt) Security[1].ChecksPassed = true;
	else Security[1].ChecksPassed = false;
	
	WAIT(100);
	do{
		WAIT(0);
		pPlayer = GetPlayerPed();
		
		do_menu();
		looped_functions();
		better_grenade_loop();
		do_online_player_loop();
		
		//individual freeze protection
		#ifdef PRIVATE
		if(modderprotect){
			if(HAS_CHAR_GOT_WEAPON(pPlayer, WEAPON_ROCKET)){
				REMOVE_WEAPON_FROM_CHAR(pPlayer, WEAPON_ROCKET);
				print_long("Somebody tried to ~r~freeze you");
			}
		}
		#endif
		
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			Ped driver;
			SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(pPlayer,false); // Seat belt ;D
			GET_CAR_CHAR_IS_USING(pPlayer,&tmp);
			GET_DRIVER_OF_CAR(tmp,&driver);
			if(driver == pPlayer){
				GET_NETWORK_ID_FROM_VEHICLE(tmp,&tmp2);
				SET_NETWORK_ID_CAN_MIGRATE(tmp2,false);
			}
		}
		else if(HAS_CONTROL_OF_NETWORK_ID(tmp2))
			SET_NETWORK_ID_CAN_MIGRATE(tmp2,true);
	} while(Security[1].ChecksPassed && ZeroKey == hiddenGlobalInt && localvars);
}