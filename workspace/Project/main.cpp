#define MENU_TITLE "XMC ModMenu v1 Private Edition"
#define PRIVATE 

#ifdef PRIVATE
#define GTCHECK "UtomAfryus69"
//Length of above gamertag
GTLENGTH = 12; 
#endif

#include <natives.h>
#include <common.h>
#include <consts.h>
#include <types.h>
#include <strings.h>
#include <vars.h>

#include "weapons.cpp"
#include "xmc_functions.cpp"
#include "setup.cpp"
#include "menu_functions.cpp"

#include "core.cpp"



void main(void){
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	show_menu = false;
	menu_setup();
	s_r = 0;
	s_g = 191;
	s_b = 255;
	
	bool length;
	
	Vehicle tmp,tmp2;
	
	#ifdef PRIVATE
	char *name = GET_PLAYER_NAME(GET_PLAYER_ID());
	if(!COMPARE_STRING(name, GTCHECK))return;
	length = GET_LENGTH_OF_LITERAL_STRING(name);
	if (length != GTLENGTH)return; //just stick your GT length in here
	while(1){
	#endif 
	
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
	
	WAIT(100);
	do{
		WAIT(0);
		pPlayer = GetPlayerPed();
		
		do_menu();
		looped_functions();
		better_grenade_loop();
		do_online_player_loop();
		
		//individual freeze protection
		if(modderprotect) {
			if (HAS_CHAR_GOT_WEAPON(pPlayer, WEAPON_ROCKET)) {
				REMOVE_WEAPON_FROM_CHAR(pPlayer, WEAPON_ROCKET);
			}
		}
		
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
	} while(true);
}
	#ifdef PRIVATE
	}
	#endif 