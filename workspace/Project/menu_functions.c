/**
	Menu functions
	Orig. by: Herr Muskelprotze
	by: Emmanuel Utomi
	
**/

#define do_toggle(x) \
	if(x) x=false;\
	else x=true;\
	reset_menu();
	
//#define print(x) PRINT_STRING_WITH_LITERAL_STRING("string",x,2000,true)

void draw_title(float x, float y, float width, float height, uint r, uint g, uint b, uint a, char *val){
#ifdef PC
	if (!IS_FONT_LOADED(7))
	{
		LOAD_TEXT_FONT(7);
	}
	SET_TEXT_FONT(7);
#else
	if (!IS_FONT_LOADED(6))
	{
		LOAD_TEXT_FONT(6);
	}
	SET_TEXT_FONT(6);
#endif
	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(1, 0, 0, 0, 255);
	SET_TEXT_PROPORTIONAL(1);
	SET_TEXT_WRAP(0.0000, 1.0000);	

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(1);
	SET_TEXT_RIGHT_JUSTIFY(0);
	DISPLAY_TEXT_WITH_LITERAL_STRING(x, y, "STRING", val);
}

void set_up_draw(int type, float width, float height, uint r, uint g, uint b, uint a){

	SET_TEXT_FONT(0);

	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(0, 0, 0, 0, 255);

	if (type == 1)
	{
		SET_TEXT_BACKGROUND(1);
	}
	else if (type == 2)
	{
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 255);
	}
	else if (type == 3)
	{
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
	}

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_PROPORTIONAL(1);

	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(0);
	SET_TEXT_RIGHT_JUSTIFY(0);

}

void draw_text(char *gxtName, float x, float y, char *val){
	DISPLAY_TEXT_WITH_LITERAL_STRING(x, y, gxtName, val);
	return;
}	
	
void draw_number(char *gxtName, float x, float y, int val){
	DISPLAY_TEXT_WITH_NUMBER(x, y, gxtName, val);
	return;
}

void menu_startup(void){
	menu_level = 0;
	item_select = 1;
	
	CLEAR_PRINTS();
	CLEAR_HELP();
	
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mpcellphone");
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("spcellphone");
	
	WAIT(200);
	
	menu_setup();
	show_menu = true;
}

void menu_shutdown(void){
	menu_level = 0;
	item_select = 1;
	show_menu = false;
	
	reset_menu();
	
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("addon_loader");
	
	WAIT(200);
	if(IS_NETWORK_SESSION()){
		REQUEST_SCRIPT("mpcellphone");
		while(!HAS_SCRIPT_LOADED("mpcellphone")) WAIT(0);
		START_NEW_SCRIPT("mpcellphone",1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("mpcellphone");
	}
	else{
		REQUEST_SCRIPT("spcellphone");
		while(!HAS_SCRIPT_LOADED("spcellphone")) WAIT(0);
		START_NEW_SCRIPT("spcellphone",1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("spcellphone");				
	}	
}
	
void create_big_explosion(float fX,float fY,float fZ){
	ADD_EXPLOSION(fX,fY,fZ + 12.5,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 20.0,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 40.0,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX,fY + 20.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY + 30.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 20.0,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 40.0,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX,fY + 20.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY - 40.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 12.5,fY + 12.5,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX + 25.0,fY + 25.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 12.5,fY - 12.5,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 25.0,fY - 25.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);

}

void teleport_char(Ped pPed, float x,float y,float z){
	if(IS_CHAR_IN_ANY_CAR(pPed)){
		int pveh,nvid,tick;
		GET_CAR_CHAR_IS_USING(pPed,&pveh);
		float s;
		GET_CAR_SPEED(pveh,&s);
		GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
		REQUEST_CONTROL_OF_NETWORK_ID(nvid);
		while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
			tick++;
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			if(tick >= 200){
				print("Error");
				return;
			}
			WAIT(0);
		}
		SET_CAR_COORDINATES(pveh,x,y,z);
		SET_CAR_FORWARD_SPEED(pveh,s);
	}
	else{
		SET_CHAR_COORDINATES(pPed,x,y,z);
		SET_GAME_CAM_HEADING(0.0);
		LOAD_ALL_OBJECTS_NOW();
	}
	REQUEST_COLLISION_AT_POSN(x,y,z);
}

void kill_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	uint test,guards;
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 7; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				int nvid;
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 250){
						continue;
					}
					WAIT(0);
				}
				SET_CHAR_INVINCIBLE(gameped[i], false);
				SET_CHAR_PROOFS(gameped[i], false, false, false, false, false);
			}
			if((i >= 7) || (i > 6)) return;
		}
		print("Gave all available guards specified weapon");			
		return;
	}
	return;
}

void delete_all_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	uint test,guards;
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 7; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				int nvid;
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 250){
						continue;
					}
					WAIT(0);
				}
				FORCE_CHAR_TO_DROP_WEAPON(gameped[i]);
				WAIT(10);
				DELETE_CHAR(&gameped[i]);
				MARK_CHAR_AS_NO_LONGER_NEEDED(&gameped[i]);
			}
		}
		print("Deleted All available guards");			
		return;
	}
	return;
}

void delete_one_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	uint test,guards;
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 7; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				int nvid;
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 250){
						return;
					}
					WAIT(0);
				}
				FORCE_CHAR_TO_DROP_WEAPON(gameped[i]);
				WAIT(10);
				DELETE_CHAR(&gameped[i]);
				MARK_CHAR_AS_NO_LONGER_NEEDED(&gameped[i]);
				print("1 was Guard Deleted");					
				return;
			}
			if((i >= 7) || (i > 6)) return;
		}
	print("No guards Exist or Available");			
	return;
	}
	return;
}

void arm_spawnguards(int weapon){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	uint test,guards;
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 7; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				int nvid;
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 250){
						continue;
					}
					WAIT(0);
				}
				REMOVE_ALL_CHAR_WEAPONS(gameped[i]);
				WAIT(10);
				UpdateWeaponOfPed(gameped[i], weapon);
				SET_CURRENT_CHAR_WEAPON(gameped[i], weapon, true);
			}
			if((i >= 7) || (i > 6)) return;
		}
		print("Gave all available guards specified weapon");			
		return;
	}
	return;
}

void tele_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	uint test,guards;
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		float x,y,z;
		GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
		for(i = 0;i <= 7; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				int nvid;
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 250){
						continue;
					}
					WAIT(0);
				}
				teleport_char(gameped[i], x, y, z);
			}
			if((i >= 7) || (i > 6)) return;
		}
	print("Teleported all available guards to you");			
	return;
	}
	return;
}

void spawnguards(uint model, uint weapon){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	if(!DOES_GROUP_EXIST(Bgroup)){
		CREATE_GROUP(0, Bgroup, true);
		SET_GROUP_LEADER(Bgroup, pPlayer);
		SET_GROUP_FORMATION(Bgroup, 2);
		SET_GROUP_FORMATION_SPACING(Bgroup, 5);
	}	
	uint test,guards;
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards >= 7) || (guards == 7) || (guards > 6)){
		print("Max guards (7) exceeded");
		return;
	}
	for(i = 0;i <= 7; i++){
		if(!DOES_CHAR_EXIST(gameped[i])){
			
			REQUEST_MODEL(model);
			while (!HAS_MODEL_LOADED(model)) WAIT(0);
			WAIT(100);
			
			GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPlayer, 0, 2, 0, &x, &y, &z);
			
			CREATE_CHAR(26, model, x,y,z, &gameped[i], true);
			WAIT(100);
			SET_CHAR_RANDOM_COMPONENT_VARIATION(gameped[i]);
			SET_GROUP_MEMBER(Bgroup, gameped[i]);
			SET_CHAR_NEVER_LEAVES_GROUP(gameped[i], true);
			SET_CHAR_RELATIONSHIP_GROUP(gameped[i], 24);
			SET_CHAR_RELATIONSHIP(gameped[i], 5, 0);
			SET_CHAR_ACCURACY(gameped[i], 100);
			SET_CHAR_KEEP_TASK(gameped[i], true);
			SET_SENSE_RANGE(gameped[i], 200.0);
			SET_PED_GENERATES_DEAD_BODY_EVENTS(gameped[i], true);
			SET_CHAR_SHOOT_RATE(gameped[i], 100);
			SET_CHAR_WILL_USE_COVER(gameped[i], true);
			SET_CHAR_WILL_DO_DRIVEBYS(gameped[i], true);
			SET_CHAR_SIGNAL_AFTER_KILL(gameped[i], true);
			SET_CHAR_WILL_USE_CARS_IN_COMBAT(gameped[i], true);
			SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(gameped[i], false);
			SET_CHAR_INVINCIBLE(gameped[i], true);
			SET_CHAR_PROOFS(gameped[i], true, true, true, true, true);
			SET_CHAR_PROVIDE_COVERING_FIRE(gameped[i], true);
			SET_CHAR_CANT_BE_DRAGGED_OUT(gameped[i], true);
			SET_CHAR_STAY_IN_CAR_WHEN_JACKED(gameped[i], true);
			SET_PED_DONT_DO_EVASIVE_DIVES(gameped[i], true);
			SET_DONT_ACTIVATE_RAGDOLL_FROM_PLAYER_IMPACT(gameped[i], true);
			SET_PED_PATH_MAY_DROP_FROM_HEIGHT(gameped[i], true);
			SET_PED_PATH_MAY_USE_CLIMBOVERS(gameped[i], true);
			SET_PED_PATH_MAY_USE_LADDERS(gameped[i], true);
			UpdateWeaponOfPed(gameped[i], weapon);
			SET_CURRENT_CHAR_WEAPON(gameped[i], weapon, true);
			WAIT(100);
			print("Spawned Guard");
			return;
		}
	}
	return;
}

void rapidrpg(void){
	Vector3 rapid;
	while(IS_BUTTON_PRESSED(0,BUTTON_R) && IS_BUTTON_PRESSED(0,BUTTON_L) && !IS_CHAR_IN_ANY_CAR(pPlayer)){
		GET_PED_BONE_POSITION(pPlayer,BONE_RIGHT_HAND,5,0.0,0.0,&rapid);
	//	GET_PED_BONE_POSITION(pPlayer,BONE_RIGHT_HAND,0.0,0.0,0.0,&rapid);
		FIRE_PED_WEAPON(pPlayer, rapid.x,rapid.y,rapid.z);
		FIRE_PED_WEAPON(pPlayer, rapid.x,rapid.y,rapid.z);
		FIRE_PED_WEAPON(pPlayer, rapid.x,rapid.y,rapid.z);
		WAIT(0);
	}
}

void object_aim(void){
	GET_GAME_CAM(&game_cam);
	if (IS_CAM_ACTIVE(game_cam)){
		GET_CAM_ROT(game_cam, &gcrotX, &gcrotY, &gcrotZ);// used for setting the object rotation and for some weird trig stuff below
		GET_CAM_POS(game_cam, &gcX, &gcY, &gcZ);// used for the spawn point of the object, because the player is offset while aiming
		if (gcrotX < 0.0)// the range for cam rot is -180 to 180, to set object rot we need 0 to 360
		{
			objrotX = gcrotX + 360.0;
		}
		else
		{
			objrotX = gcrotX;
		}
		if (gcrotZ < 0.0)
		{
			objrotZ = gcrotZ + 360.0;
		}
		else
		{
			objrotZ = gcrotZ;
		}
		/*  the trig stuff below could possibly be replaced with vectors, I have no idea how to do that though.  *
		*   I apologize if this is confusing, but if you want to change the distance from the game_cam that the  *
		*   object is spawned, adjust "3.0" to your preference on the first and fourth lines.  Also prjT is the  *
		*   adjacent side from the pitch calculation, its purpose is to be the tangent in the following 2 lines */
		prjT = (3.0 * COS(gcrotX));       // adj side calculation to be used as a tangent below
		prjX = gcX - (prjT * SIN(gcrotZ));// calculates how far to spawn the object from the game_cam on the X plane
		prjY = gcY + (prjT * COS(gcrotZ));// calculates how far to spawn the object from the game_cam on the Y plane
		prjZ = gcZ + (3.0 * SIN(gcrotX)); // calculates how far to spawn the object from the game_cam on the Z plane
	}
}

void object_shoot(void){
	if(del_objgun){
		if(DOES_OBJECT_EXIST(ObjectProjectile)){
			GET_NETWORK_ID_FROM_OBJECT(ObjectProjectile, &nvid);
			SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
				tick++;
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				if(tick >= 250){
					break;
				}
				WAIT(0);
			}
			GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
			SET_OBJECT_COORDINATES(ObjectProjectile, x,y,z);
			DELETE_OBJECT(&ObjectProjectile);
		}
	}
		
	REQUEST_MODEL(object_launch);
	while(!HAS_MODEL_LOADED(object_launch)) WAIT(0);
		
	CREATE_OBJECT(object_launch, prjX, prjY, prjZ, &ObjectProjectile, 1);
	GET_NETWORK_ID_FROM_OBJECT(ObjectProjectile, &nvid);
	SET_NETWORK_ID_CAN_MIGRATE(nvid, 0);
	SET_OBJECT_VISIBLE(ObjectProjectile, 0);
	MARK_MODEL_AS_NO_LONGER_NEEDED(object_launch);
	if(DOES_OBJECT_EXIST(ObjectProjectile)){
		SET_OBJECT_QUATERNION(ObjectProjectile,0,0,0,0);
		SET_OBJECT_INVINCIBLE(ObjectProjectile,false);
		FREEZE_OBJECT_POSITION(ObjectProjectile,false);
		SET_OBJECT_DYNAMIC(ObjectProjectile,true);
		SET_OBJECT_AS_STEALABLE(ObjectProjectile,true);
		SET_OBJECT_ROTATION(ObjectProjectile, objrotX, 0.0, objrotZ);
		SET_OBJECT_COLLISION(ObjectProjectile, true);
		WAIT(100);
		SET_OBJECT_VISIBLE(ObjectProjectile, 1);
		APPLY_FORCE_TO_OBJECT(ObjectProjectile, 1, 0.0, 250.0, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1);
	}
}

void car_shoot(void){
	if(del_cargun){
		if(DOES_VEHICLE_EXIST(CarProjectile)){
			GET_NETWORK_ID_FROM_VEHICLE(CarProjectile, &nvid);
			SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
				tick++;
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				if(tick >= 250){
					break;
				}
				WAIT(0);
			}
			GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
			SET_CAR_COORDINATES(CarProjectile, x,y,z);
			DELETE_CAR(&CarProjectile);
			MARK_CAR_AS_NO_LONGER_NEEDED(&CarProjectile);
		}
	}
	
	Vector3 aim,spawn,force;
	GET_PED_BONE_POSITION(pPlayer, BONE_RIGHT_HAND, 100, 0, 0, &aim);
	GET_PED_BONE_POSITION(pPlayer, BONE_RIGHT_HAND, 5, 0, 0, &spawn);
	force.x = (aim.x - spawn.x) / 95 * 2000;
	force.y = (aim.y - spawn.y) / 95 * 2000;
	force.z = (aim.z - spawn.z) / 95 * 2000;
		
	REQUEST_MODEL(car_launch);
	while(!HAS_MODEL_LOADED(car_launch)) WAIT(0);
		
	CREATE_CAR(car_launch, spawn.x, spawn.y, spawn.z, &CarProjectile, 1);
	GET_NETWORK_ID_FROM_VEHICLE(CarProjectile, &nvid);
	SET_NETWORK_ID_CAN_MIGRATE(nvid, 0);
	SET_CAR_VISIBLE(CarProjectile, 0);
	MARK_MODEL_AS_NO_LONGER_NEEDED(car_launch);
	if(DOES_VEHICLE_EXIST(CarProjectile)){
		SET_CAR_PROOFS(CarProjectile, true, true, true, true, true);
		FREEZE_CAR_POSITION(CarProjectile,false);
		SET_CAR_COLLISION(CarProjectile, true);
		if(exp_cargun) SET_PETROL_TANK_HEALTH(CarProjectile, -1);
		WAIT(100);
		SET_CAR_VISIBLE(CarProjectile, 1);
		APPLY_FORCE_TO_CAR(CarProjectile, 1, force.x, force.y, force.z + 1.5, 0.0, 0.0, 0.0, 1, 0, 1, 1);
	//	APPLY_FORCE_TO_CAR(CarProjectile, 1, 0.0, 500.0, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1);
	}
}


void create_throwable_object(uint model){
	int obj = 0;
	float fX,fY,fZ;
	GET_CHAR_COORDINATES(pPlayer,&fX,&fY,&fZ);
	CREATE_OBJECT(model,fX,fY,fZ,&obj,true);
	SET_OBJECT_QUATERNION(obj,0,0,0,0);
	SET_OBJECT_INVINCIBLE(obj,false);
	FREEZE_OBJECT_POSITION(obj,false);
	SET_OBJECT_DYNAMIC(obj,true);
	SET_OBJECT_AS_STEALABLE(obj,true);
	SET_OBJECT_COLLISION(obj,true);
}

void spawn_car(uint model){
	int pveh,driver;
	float h, s;
	bool speed = false;
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)) WAIT(0);
	GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
	GET_CHAR_HEADING(pPlayer,&h);
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
		GET_CAR_SPEED(pveh,&s);
		speed = true;
		GET_DRIVER_OF_CAR(pveh,&driver);
		WARP_CHAR_FROM_CAR_TO_COORD(pPlayer,x,y,z);
		if(!DOES_CHAR_EXIST(driver) || pPlayer == driver || !IS_NETWORK_SESSION()){
			DELETE_CAR(&pveh);
			MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
		}
	}
	CREATE_CAR(model,x,y,z,&pveh,true);
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
    CHANGE_CAR_COLOUR(pveh, 133, 133);
	SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
    SET_VEHICLE_DIRT_LEVEL(pveh, 0);
    WASH_VEHICLE_TEXTURES(pveh, 255);
	SET_CAR_ENGINE_ON(pveh,true,true);
	WARP_CHAR_INTO_CAR(pPlayer,pveh);
	SET_CAR_PROOFS(pveh, true, true, true, true, true);
	SET_CAR_HEADING(pveh,h);
	if(speed)
		SET_CAR_FORWARD_SPEED(pveh,s);
	return;
}

void helibomb(void){
	uint heliBomb = 0x7E339194;
	Object BOMB;
	float zground, repeat, counter;
	REQUEST_MODEL(heliBomb);
	while (!HAS_MODEL_LOADED(heliBomb)) WAIT(0); 	
	GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(GetPlayerPed(), 0.5, -2.1, -2.1, &x, &y, &z);
	GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
	CREATE_OBJECT(heliBomb, x, y, z, &BOMB, 1);
	PLAY_SOUND_FROM_VEHICLE(-1, "F5_TRUCK_ARSON_BOMB_BLEEP", pveh);
	PLAY_SOUND_FROM_VEHICLE(-1, "F5_TRUCK_ARSON_BOMB_BLEEP", pveh);
	SET_OBJECT_HEALTH(BOMB, 100.0);
	SET_OBJECT_ROTATION(BOMB, 90.0, 0.0, 0.0);
	GET_GROUND_Z_FOR_3D_COORD(x, y, z, &zground);
	repeat = z - zground;
		//repeat
	for (counter = 1; counter <= repeat; counter++) {
		WAIT(27);
		SLIDE_OBJECT(BOMB, x, y, zground, 0.0, 0.0, 1.3, 0);
	}
	PLAY_SOUND_FROM_VEHICLE(-1, "F5_TRUCK_ARSON_BOMB_BLEEP", pveh);
	
		// repeat end!
	WAIT(100);

		//---------------- In Heli
	//BombType(X, Y, Z, width, highness, spacing)
	//BombType(x, y, zground, 7, 2, 2);
	create_big_explosion(x,y,zground);
	create_big_explosion(x,y,zground + 2);
	create_big_explosion(x + 5,y,zground);
	create_big_explosion(x + 5,y,zground);
	create_big_explosion(x - 5,y,zground);
	create_big_explosion(x,y + 5,zground);
	create_big_explosion(x,y - 5,zground);
	
	DELETE_OBJECT(&BOMB);
	MARK_MODEL_AS_NO_LONGER_NEEDED(heliBomb);
}

void spawn_car_for_char(Ped pPed, uint model){
	int pveh;
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)) WAIT(0);
	//spawn car offset 3ft infront of player
	GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, 0, 3, 0, &x, &y, &z);
	CREATE_CAR(model,x,y,z,&pveh,true);
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
    CHANGE_CAR_COLOUR(pveh, 133, 133);
	SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
    SET_VEHICLE_DIRT_LEVEL(pveh, 0);
    WASH_VEHICLE_TEXTURES(pveh, 255);
	SET_CAR_ENGINE_ON(pveh,true,true);
	SET_CAR_PROOFS(pveh, true, true, true, true, true);
	return;
}

//example usage
//spawn_car_for_char(players[index].ped, MODEL_SULTAN);

void xmc_teleportinfront(void){
        float ch;
        GET_CHAR_HEADING(GetPlayerPed(), &ch);
        GET_CHAR_COORDINATES(GetPlayerPed(), &x, &y, &z);
        teleport_char(pPlayer, x+(10*SIN((-1*ch))), y+(10*COS((-1*ch))), z);
}

void xmc_airstrike(void){
	if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
		Vector3 pos;
		GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&pos);
		GET_GROUND_Z_FOR_3D_COORD(pos.x,pos.y,pos.z,&z);
		create_big_explosion(pos.x,pos.y,z+5.0f);
		print("Launching Airstrike!");
	}
	else print("You need to set a waypoint!");
}

void attachobjecttocar(Vehicle veh,uint model,float offsetX,float offsetY,float offsetZ,float yaw,float pitch,float roll){
	int obj;
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)){ WAIT(0); }
	CREATE_OBJECT(model,0,0,0,&obj,true);
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
	ATTACH_OBJECT_TO_CAR(obj,veh,0,offsetX,offsetY,offsetZ,yaw,pitch,roll);
	FREEZE_OBJECT_POSITION(obj,true);
	SET_OBJECT_VISIBLE(obj,true);
	SET_OBJECT_INVINCIBLE(obj,true);
	SET_OBJECT_LIGHTS(obj,true);
}

void menu_functions(void){
	if(menu_level == 1){
		if(last_selected[0] == 1){
			if(item_select == 3){
				SET_CHAR_HEALTH(pPlayer,500);
				ADD_ARMOUR_TO_CHAR(pPlayer,100);
				return;
			}
			if(item_select == 4){
				do_toggle(godmode);
				return;
			}
			if(item_select == 5){
				do_toggle(neverwanted);
				if(neverwanted){
					SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), true);
					ALLOW_EMERGENCY_SERVICES(false);
					SET_MAX_WANTED_LEVEL(0);
					SET_CHAR_WANTED_BY_POLICE(pPlayer, false);
				}
				else
					SET_MAX_WANTED_LEVEL(6);
				return;
			}
			if(item_select == 6){
				do_toggle(pprotection);
				FREEZE_CHAR_POSITION(pPlayer,false);
				return;
			}
			if(item_select == 7){
				if(!superrun){
				print("Press LB + A to use");
				}
				do_toggle(superrun);
				return;
			}
			if(item_select == 8){
				if(!superjump){
				print("Press LB + X to use");
				}
				do_toggle(superjump);
				return;
			}
			if(item_select == 9){
				do_toggle(chronicle);
				return;
			}
			if(item_select == 10){
				do_toggle(chaos);
				return;
			}
			if(item_select == 11){
				do_toggle(invisible);
				if(invisible){
					SET_CHAR_VISIBLE(pPlayer, false);
				}
				else{
					SET_CHAR_VISIBLE(pPlayer, true);
				}
				return;
			}
			if(item_select == 12){
				do_toggle(onfire);
				if(onfire){
					START_CHAR_FIRE(pPlayer);
				}
				else{
					EXTINGUISH_CHAR_FIRE(pPlayer);
				}
				return;
			}
		}
		if(last_selected[0] == 2){
			if(item_select == 2){
				do_toggle(vhelper);
				return;
			}
			if(item_select == 3){
				if(DOES_CHAR_EXIST(pPlayer)){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
						tick++;
						REQUEST_CONTROL_OF_NETWORK_ID(nvid);
						if(tick >= 200){
						print("Error");
						return;
					}
					WAIT(0);
					}
				APPLY_FORCE_TO_CAR(pveh,true,0.0,0.0,1000.0,0.0,0.0,0.0,true,true,true,true);
				}
				else print("Not in vehicle");
				}
				return;
			}
			if(item_select == 4){
				do_toggle(carsonground);
				return;
			}
			if(item_select == 5){
				do_toggle(nfs);
				carsonground = true;
				return;
			}
			if(item_select == 6){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					// float x,y,z;
					GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
					teleport_char(pPlayer,0.0,4000.0,0.0);
					WAIT(0);
					teleport_char(pPlayer,x,y,z);
				}
				return;
			}
			if(item_select == 7){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					uint lock;
					// Vehicle pveh;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					GET_CAR_DOOR_LOCK_STATUS(pveh,&lock);
					if(lock == VEHICLE_DOOR_UNLOCKED){
						LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_LOCKED_BOTH_SIDES);
						print("Doors locked!");
					}
					else{
						LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_UNLOCKED);
						print("Doors unlocked!");
					}
				}
				return;
			}
			if(item_select == 8){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					// // Vehicle pveh;
					Ped driver;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					GET_DRIVER_OF_CAR(pveh,&driver);
					if(driver == pPlayer){
						DELETE_CAR(&pveh);
						MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
					}
					else print("You must be the driver of this vehicle");
				}
				return;
			}
			if(item_select == 9){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					// Vehicle pveh;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					SET_CAR_ON_GROUND_PROPERLY(pveh);
				}
				return;
			}
			if(item_select == 10){
				//// float x, y, z;
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
					z += 1;
					WARP_CHAR_FROM_CAR_TO_COORD(pPlayer, x, y, z);
					APPLY_FORCE_TO_PED(pPlayer, 1 ,0.0f ,0.0f ,1000.0f ,0.0f ,0.0f ,0.0f ,1 ,1 ,1 ,1);
					print("Ejected");
					return;
				}
			}
			if(item_select == 11){
				if(!bikefly){
				print("Get in a bike and it will fly");
				}
				do_toggle(bikefly);
				return;
			}
			if(item_select == 12){
				float h, s;
				uint model;
				int color1, color2, color3, color4;
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					GET_CAR_MODEL(pveh, &model);
					GET_CAR_COLOURS(pveh, &color1, &color2);
					GET_EXTRA_CAR_COLOURS(pveh, &color3, &color4);
					bool speed = false;
					REQUEST_MODEL(model);
					while(!HAS_MODEL_LOADED(model)) WAIT(0);
					GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
					GET_CHAR_HEADING(pPlayer,&h);
					GET_CAR_SPEED(pveh,&s);
					speed = true;
					GET_DRIVER_OF_CAR(pveh,&driver);
					WARP_CHAR_FROM_CAR_TO_COORD(pPlayer,x,y,z);
					if(!DOES_CHAR_EXIST(driver) || pPlayer == driver || !IS_NETWORK_SESSION()){
						DELETE_CAR(&pveh);
						MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
					}
					CREATE_CAR(model,x,y,z,&pveh,true);
					MARK_MODEL_AS_NO_LONGER_NEEDED(model);
					CHANGE_CAR_COLOUR(pveh, color1, color2);
					SET_EXTRA_CAR_COLOURS(pveh, color3, color4);
					SET_VEHICLE_DIRT_LEVEL(pveh, 0);
					WASH_VEHICLE_TEXTURES(pveh, 255);
					SET_CAR_ENGINE_ON(pveh,true,true);
					WARP_CHAR_INTO_CAR(pPlayer,pveh);
					SET_CAR_PROOFS(pveh, true, true, true, true, true);
					SET_CAR_HEADING(pveh,h);
					if(speed)
						SET_CAR_FORWARD_SPEED(pveh,s);
					return;
				}
				return;
			}
			if(item_select == 13){
				if(!helistrike){
				print("All Helis will drop bomb when left stick is pressed");
				}
				do_toggle(helistrike);
				return;
			}
			return;
		}
		if(last_selected[0] == 3){
			if(item_select == 2){
				do_toggle(ammo);
				return;
			}
			else if(item_select == 3){
				do_toggle(fastreload);
				if(fastreload){
					SET_PLAYER_FAST_RELOAD(GetPlayerIndex(), true);
				}
				else{
					SET_PLAYER_FAST_RELOAD(GetPlayerIndex(), false);
				}
				return;
			}
			else if(item_select == 4){
				if(!autoaim){
					print("Forced Auto Aim");
				}
				do_toggle(autoaim);
				if(autoaim){
					DISABLE_PLAYER_LOCKON(GetPlayerIndex(), false);
				}
				else{
					DISABLE_PLAYER_LOCKON(GetPlayerIndex(), true);
				}
				return;
			}
			else if(item_select == 6){
				#ifndef PRIVATE
				print("Private version only");
				return;
				#endif
				do_toggle(burstfire);
				return;
			}
		}
		if(last_selected[0] == 4){
			if(item_select == 1){
				if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
					Vector3 pos;
					GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&pos);
					teleport_char(pPlayer,pos.x,pos.y,0.0);
					
					GET_GROUND_Z_FOR_3D_COORD(pos.x,pos.y,1000,&z);
					WAIT(0);
					teleport_char(pPlayer,pos.x,pos.y,z);
				}
				else print("You need to set a waypoint!");
				
				return;
			}
			if(item_select == 2){
				teleport_char(pPlayer,2175.3516,761.2235,30.0);
				return;
			}
			if(item_select == 3){
				teleport_char(pPlayer,1100.5,-747.0,7.39);
				return;
			}
			if(item_select == 4){
				teleport_char(pPlayer,-178.2,582.6,126.85);
				return;
			}
			if(item_select == 5){
				teleport_char(pPlayer,-2476.0,942.7,1100.0);
				return;
			}
			if(item_select == 6){
				teleport_char(pPlayer,-236.0,795.9,6.20);
				return;
			}
			if(item_select == 7){
				teleport_char(pPlayer,-415.17,1463.54,39.0);
				return;
			}
			if(item_select == 8){
				teleport_char(pPlayer,-279.77,-99.66,386.791);
				return;
			}
			if(item_select == 9){
				teleport_char(pPlayer,-1079.8,-469.7,2.62);
				return;
			}
			if(item_select == 10){
				teleport_char(pPlayer,1375.8765,197.4544,48.0);
				return;
			}
			if(item_select == 11){
				teleport_char(pPlayer,-532.681,1273.3307,105.65);
				return;
			}
			if(item_select == 12){
				teleport_char(pPlayer,55.3537,1125.3387,2.4527);
				return;
			}
			if(item_select == 13){
				teleport_char(pPlayer,104.13,856.53,45.58);
				return;
			}
			if(item_select == 14){
				teleport_char(pPlayer,-473.0176,1746.8829,6.26);
				return;
			}
			if(item_select == 15){
				teleport_char(pPlayer,237.5457,-805.6555,13.7);
				return;
			}
			if(item_select == 16){
				teleport_char(pPlayer,-3.4734,270.6067,-2.9470);
				return;
			}
			if(item_select == 17){
				teleport_char(pPlayer,-1539.8414,163.2967,9.9000);
				return;
			}
			if(item_select == 18){
				xmc_teleportinfront();
				return;
			}
			if(item_select == 19){
				GET_CHAR_COORDINATES(pPlayer,&x, &y, &z);
				ClosestCar = GET_CLOSEST_CAR(x,y,z, 50, false, 70);
				if(!DOES_VEHICLE_EXIST(ClosestCar))
				ClosestCar = GET_CLOSEST_CAR(x,y,z, 50, false, 71);
				if(!DOES_VEHICLE_EXIST(ClosestCar))
				ClosestCar = GET_CLOSEST_CAR(x,y,z, 50, false, 69);
				if(!DOES_VEHICLE_EXIST(ClosestCar)) return;
				GET_DRIVER_OF_CAR(ClosestCar,&driver);
				if(!DOES_CHAR_EXIST(driver)){
					WARP_CHAR_INTO_CAR(pPlayer,ClosestCar);
					print("Teleported into Nearest Car as Driver");
				}
				else{
					for(i = 0;i <= 2;i++){
						if(IS_CAR_PASSENGER_SEAT_FREE(ClosestCar,i)){
							WARP_CHAR_INTO_CAR_AS_PASSENGER(pPlayer,ClosestCar,i);
							print("Teleported into Nearest Car as Passenger");
						}
					}
				}
				return;
			}
		}
		if(last_selected[0] == 5){
			if(item_select == 4){
				do_toggle(chat_thingy);
				return;
			}
			if(item_select == 5){
				do_toggle(drive_free);
				if(drive_free){
					SWITCH_ROADS_OFF(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
					SWITCH_AMBIENT_PLANES(false);
				}
				else{
					SWITCH_ROADS_ON(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
					SWITCH_AMBIENT_PLANES(true);
				}
				return;
			}
			if(item_select == 6){
				SHUTDOWN_AND_LAUNCH_NETWORK_GAME(2);
				return;
			}
			if(item_select == 7){
				SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
				return;
			}
			if(item_select == 8){
				print_long(GET_PLAYER_NAME(GET_HOST_ID()));
			}
			if(item_select == 9){	
				do_toggle(modderprotect);
				return;
			}
			if(item_select == 10){
				for(i = 0; i < 66; i++){
					if(!HAS_ACHIEVEMENT_BEEN_PASSED(i)) AWARD_ACHIEVEMENT(i);
				}
				print("Unlocked All available Achievements");
				return;
			}
			if(item_select == 11){
				print_long("~b~May take some time");
				Object nObj;
				GET_CHAR_COORDINATES(GetPlayerPed(), &x, &y, &z);
				CLEAR_AREA_OF_OBJECTS(x,y,z,500);
				for(i;i<2000;i++){
					GET_OBJECT_FROM_NETWORK_ID(i, &nObj);
					if(DOES_OBJECT_EXIST(nObj)){
						GET_NETWORK_ID_FROM_OBJECT(nObj, &nvid);
						REQUEST_CONTROL_OF_NETWORK_ID(nvid);
						while(!HAS_CONTROL_OF_NETWORK_ID(i)){
							tick++;
							REQUEST_CONTROL_OF_NETWORK_ID(nvid);
							if(tick >= 200){
								print("Deleted all available Objects");
								return;
							}
							WAIT(0);
						}
						DELETE_OBJECT(&nObj);
					}
				}
				return;
			}
			if(item_select == 12){
				GET_CHAR_COORDINATES(pPlayer,&x, &y, &z);
				CLEAR_AREA_OF_CARS(x,y,z,500);
				for(i = 0; i <= 20; i++){
					ClosestCar = GET_CLOSEST_CAR(x,y,z, 60, false, 70);
					if(!DOES_VEHICLE_EXIST(ClosestCar)) ClosestCar = GET_CLOSEST_CAR(x,y,z, 60, false, 71);
					if(!DOES_VEHICLE_EXIST(ClosestCar)) ClosestCar = GET_CLOSEST_CAR(x,y,z, 60, false, 69);
					if(!DOES_VEHICLE_EXIST(ClosestCar)) return;
						
					GET_NETWORK_ID_FROM_VEHICLE(ClosestCar, &nvid);
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					while(!HAS_CONTROL_OF_NETWORK_ID(i)){
						tick++;
						REQUEST_CONTROL_OF_NETWORK_ID(nvid);
						if(tick >= 200){
							print("Deleted all available cars");
							return;
						}
						WAIT(0);
					}
					DELETE_CAR(&ClosestCar);
					MARK_CAR_AS_NO_LONGER_NEEDED(&ClosestCar);
				}
				return;
			}
			if(item_select == 13){
				GET_CHAR_COORDINATES(pPlayer,&x, &y, &z);
				CLEAR_AREA_OF_CHARS(x,y,z,500);
				for(i = 0; i <= 20; i++){
					GET_CLOSEST_CHAR(x,y,z, 60, false, 70, &ClosestChar);
					if(!DOES_CHAR_EXIST(ClosestChar)) GET_CLOSEST_CHAR(x,y,z, 60, false, 71, &ClosestChar);
					if(!DOES_CHAR_EXIST(ClosestChar)) GET_CLOSEST_CHAR(x,y,z, 60, false, 69, &ClosestChar);
					if(!DOES_CHAR_EXIST(ClosestChar)) return;
					
					GET_NETWORK_ID_FROM_PED(ClosestChar, &nvid);
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					while(!HAS_CONTROL_OF_NETWORK_ID(i)){
						tick++;
						REQUEST_CONTROL_OF_NETWORK_ID(nvid);
						if(tick >= 200){
							print("Deleted all available peds");
							return;
						}
						WAIT(0);
					}
					DELETE_CHAR(&ClosestChar);
				}
				return;
			}
		}
		if(last_selected[0] == 6){
			if(item_select == 1){
				if(DOES_SCRIPT_EXIST("xmc1")){
					do_toggle(xmc1);
					if(xmc1){
						REQUEST_SCRIPT("xmc1");
						while(!HAS_SCRIPT_LOADED("xmc1")){
							REQUEST_SCRIPT("xmc1");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc1", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc1");
						print_long("~g~Launched xmc1.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc1");
						print_long("~r~Killed xmc1.sco");
					}
				}
				else print_long("~r~xmc1.sco Doesn't exist");
				return;
			}
			if(item_select == 2){
				if(DOES_SCRIPT_EXIST("xmc2")){
					do_toggle(xmc2);
					if(xmc2){
						REQUEST_SCRIPT("xmc2");
						while(!HAS_SCRIPT_LOADED("xmc2")){
							REQUEST_SCRIPT("xmc2");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc2", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc2");
						print_long("~g~Launched xmc2.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc2");
						print_long("~r~Killed xmc2.sco");
					}
				}
				else print_long("~r~xmc2.sco Doesn't exist");
				return;
			}
			if(item_select == 3){
				if(DOES_SCRIPT_EXIST("xmc3")){
					do_toggle(xmc3);
					if(xmc3){
						REQUEST_SCRIPT("xmc3");
						while(!HAS_SCRIPT_LOADED("xmc3")){
							REQUEST_SCRIPT("xmc3");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc3", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc3");
						print_long("~g~Launched xmc3.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc3");
						print_long("~r~Killed xmc3.sco");
					}
				}
				else print_long("~r~xmc3.sco Doesn't exist");
				return;
			}
			if(item_select == 4){
				if(DOES_SCRIPT_EXIST("xmc4")){
					do_toggle(xmc4);
					if(xmc4){
						REQUEST_SCRIPT("xmc4");
						while(!HAS_SCRIPT_LOADED("xmc4")){
							REQUEST_SCRIPT("xmc4");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc4", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc4");
						print_long("~g~Launched xmc4.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc4");
						print_long("~r~Killed xmc4.sco");
					}
				}
				else print_long("~r~xmc4.sco Doesn't exist");
				return;
			}
			if(item_select == 5){
				if(DOES_SCRIPT_EXIST("xmc5")){
					do_toggle(xmc5);
					if(xmc5){
						REQUEST_SCRIPT("xmc5");
						while(!HAS_SCRIPT_LOADED("xmc5")){
							REQUEST_SCRIPT("xmc5");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc5", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc5");
						print_long("~g~Launched xmc5.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc5");
						print_long("~r~Killed xmc5.sco");
					}
				}
				else print_long("~r~xmc5.sco Doesn't exist");
				return;
			}
			if(item_select == 6){
				if(DOES_SCRIPT_EXIST("xmc6")){
					do_toggle(xmc6);
					if(xmc6){
						REQUEST_SCRIPT("xmc6");
						while(!HAS_SCRIPT_LOADED("xmc6")){
							REQUEST_SCRIPT("xmc6");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc6", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc6");
						print_long("~g~Launched xmc6.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc6");
						print_long("~r~Killed xmc6.sco");
					}
				}
				else print_long("~r~xmc6.sco Doesn't exist");
				return;
			}
			if(item_select == 7){
				if(DOES_SCRIPT_EXIST("xmc7")){
					do_toggle(xmc7);
					if(xmc7){
						REQUEST_SCRIPT("xmc7");
						while(!HAS_SCRIPT_LOADED("xmc7")){
							REQUEST_SCRIPT("xmc7");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc7", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc7");
						print_long("~g~Launched xmc7.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc7");
						print_long("~r~Killed xmc7.sco");
					}
				}
				else print_long("~r~xmc7.sco Doesn't exist");
				return;
			}
			if(item_select == 8){
				if(DOES_SCRIPT_EXIST("xmc8")){
					do_toggle(xmc8);
					if(xmc8){
						REQUEST_SCRIPT("xmc8");
						while(!HAS_SCRIPT_LOADED("xmc8")){
							REQUEST_SCRIPT("xmc8");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc8", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc8");
						print_long("~g~Launched xmc8.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc8");
						print_long("~r~Killed xmc8.sco");
					}
				}
				else print_long("~r~xmc8.sco Doesn't exist");
				return;
			}
			if(item_select == 9){
				if(DOES_SCRIPT_EXIST("xmc9")){
					do_toggle(xmc9);
					if(xmc9){
						REQUEST_SCRIPT("xmc9");
						while(!HAS_SCRIPT_LOADED("xmc9")){
							REQUEST_SCRIPT("xmc9");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc9", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc9");
						print_long("~g~Launched xmc9.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc9");
						print_long("~r~Killed xmc9.sco");
					}
				}
				else print_long("~r~xmc9.sco Doesn't exist");
				return;
			}
			if(item_select == 10){
				if(DOES_SCRIPT_EXIST("xmc10")){
					do_toggle(xmc10);
					if(xmc10){
						REQUEST_SCRIPT("xmc10");
						while(!HAS_SCRIPT_LOADED("xmc10")){
							REQUEST_SCRIPT("xmc10");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc10", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc10");
						print_long("~g~Launched xmc10.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc10");
						print_long("~r~Killed xmc10.sco");
					}
				}
				else print_long("~r~xmc10.sco Doesn't exist");
				return;
			}
			if(item_select == 11){
				if(DOES_SCRIPT_EXIST("xmc11")){
					do_toggle(xmc11);
					if(xmc11){
						REQUEST_SCRIPT("xmc11");
						while(!HAS_SCRIPT_LOADED("xmc11")){
							REQUEST_SCRIPT("xmc11");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc11", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc11");
						print_long("~g~Launched xmc11.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc11");
						print_long("~r~Killed xmc11.sco");
					}
				}
				else print_long("~r~xmc11.sco Doesn't exist");
				return;
			}
			if(item_select == 12){
				if(DOES_SCRIPT_EXIST("xmc12")){
					do_toggle(xmc12);
					if(xmc12){
						REQUEST_SCRIPT("xmc12");
						while(!HAS_SCRIPT_LOADED("xmc12")){
							REQUEST_SCRIPT("xmc12");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc12", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc12");
						print_long("~g~Launched xmc12.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc12");
						print_long("~r~Killed xmc12.sco");
					}
				}
				else print_long("~r~xmc12.sco Doesn't exist");
				return;
			}
			if(item_select == 13){
				if(DOES_SCRIPT_EXIST("xmc13")){
					do_toggle(xmc13);
					if(xmc13){
						REQUEST_SCRIPT("xmc13");
						while(!HAS_SCRIPT_LOADED("xmc13")){
							REQUEST_SCRIPT("xmc13");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc13", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc13");
						print_long("~g~Launched xmc13.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc13");
						print_long("~r~Killed xmc13.sco");
					}
				}
				else print_long("~r~xmc13.sco Doesn't exist");
				return;
			}
			if(item_select == 14){
				if(DOES_SCRIPT_EXIST("xmc14")){
					do_toggle(xmc14);
					if(xmc14){
						REQUEST_SCRIPT("xmc14");
						while(!HAS_SCRIPT_LOADED("xmc14")){
							REQUEST_SCRIPT("xmc14");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc14", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc14");
						print_long("~g~Launched xmc14.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc14");
						print_long("~r~Killed xmc14.sco");
					}
				}
				else print_long("~r~xmc14.sco Doesn't exist");
				return;
			}
			if(item_select == 15){
				if(DOES_SCRIPT_EXIST("xmc15")){
					do_toggle(xmc15);
					if(xmc15){
						REQUEST_SCRIPT("xmc15");
						while(!HAS_SCRIPT_LOADED("xmc15")){
							REQUEST_SCRIPT("xmc15");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc15", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc15");
						print_long("~g~Launched xmc15.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc15");
						print_long("~r~Killed xmc15.sco");
					}
				}
				else print_long("~r~xmc15.sco Doesn't exist");
				return;
			}
		}
	}
	if(menu_level == 2){
		if(last_selected[0] == 1){
			if(last_selected[1] == 13){
				if(item_select == 2){
					spawnguards(MODEL_M_O_HASID_01, WEAPON_MP5);
					return;
				}
				else if(item_select == 3){
					spawnguards(MODEL_IG_LILJACOB, WEAPON_MP5);
					return;
				}
				else if(item_select == 4){
					spawnguards(MODEL_IG_BRUCIE, WEAPON_POOLCUE);
					return;
				}
				else if(item_select == 5){
					spawnguards(MODEL_M_Y_GAFR_LO_01, WEAPON_MICRO_UZI);
					return;
				}
				else if(item_select == 6){
					spawnguards(MODEL_M_M_FBI, WEAPON_DEAGLE);
					return;
				}
				else if(item_select == 7){
					spawnguards(MODEL_M_Y_COP, WEAPON_SHOTGUN);
					return;
				}
				else if(item_select == 8){
					spawnguards(MODEL_M_M_FATCOP_01, WEAPON_RLAUNCHER);
					return;
				}
				else if(item_select == 9){
					spawnguards(MODEL_M_Y_MULTIPLAYER, WEAPON_AK47);
					return;
				}
				else if(item_select == 10){
					spawnguards(MODEL_F_Y_MULTIPLAYER, WEAPON_BARETTA);
					return;
				}
				else if(item_select == 11){
					spawnguards(MODEL_M_M_GUNNUT_01, WEAPON_M4);
					return;
				}
				else if(item_select == 12){
					spawnguards(MODEL_M_Y_CLUBFIT, WEAPON_BASEBALLBAT);
					return;
				}
				else if(item_select == 13){
					spawnguards(MODEL_F_Y_STRIPPERC01, WEAPON_POOLCUE);
					return;
				}
				else if(item_select == 14){
					spawnguards(MODEL_M_Y_SWAT, WEAPON_M4);
					return;
				}
				else if(item_select == 15){
					spawnguards(MODEL_M_Y_GMAF_HI_02, WEAPON_DEAGLE);
					return;
				}
				else if(item_select == 16){
					spawnguards(MODEL_M_Y_THIEF, WEAPON_KNIFE);
					return;
				}
				else if(item_select == 17){
					spawnguards(MODEL_M_Y_NHELIPILOT, WEAPON_SNIPERRIFLE);
					return;
				}
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(item_select == 6){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						FIX_CAR(pveh);
						SET_VEHICLE_DIRT_LEVEL(pveh,0.0);
						print("Vehicle fixed & washed!");
					}
					return;
				}
				if(item_select == 7){
					if(!hydrolics){
						print("Hold X for hydrolics");
					}
					do_toggle(hydrolics);
					return;
				}
				if(item_select == 8){
					if(!collision){
					print("All Vehicles will fly through walls, objects, and people");
					}
					do_toggle(collision);
					carsonground = true;
					return;
				}
				if(item_select == 9){
					if(!lowerpveh){
					print("All Vehicles will now be lowered");
					}
					do_toggle(lowerpveh);
					return;
				}
				if(item_select == 10){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						do_toggle(freezecar);
						if(freezecar){
							FREEZE_CAR_POSITION(pveh,true);
							print("Car is now immobile");
						}
						else{
							FREEZE_CAR_POSITION(pveh,false);
							print("Car is now mobile");
						}
						return;
					}
				}
				if(item_select == 11){
					if(!rainbowcar){
					print("All Vehicles will now be rainbow colored");
					}
					do_toggle(rainbowcar);
					return;
				}
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				if(item_select == 1){
					if(menu[item_select].value == 1){
						GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_UNARMED, AMMO_MAX, false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_DEAGLE,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_GRENADE,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MP5,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M4,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BARETTA,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
						print("You have been given advanced weapons.");
					}
					else if(menu[item_select].value == 2){
						GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_UNARMED, AMMO_MAX, false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_PISTOL,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MOLOTOV,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MICRO_UZI,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_AK47,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SHOTGUN,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M40A1,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
						print("You have been given poor weapons.");						
					}
					else if(menu[item_select].value == 3){
						uint episode = GET_CURRENT_EPISODE();
						if(episode == 2){
							GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_UNARMED, AMMO_MAX, false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_9,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_10,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_13,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_14,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_15,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_1,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_16,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
							print("You have been given TBOGT weapons.");
							return;
						}
						print("You must be on The Ballad of Gay Tony to use this");
					}
					return;
				}
				else if(item_select == 3){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_GRENADE,AMMO_MAX,false);
					print("You have been given some grenades");				
				}
				else if(item_select == 4){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_PISTOL,AMMO_MAX,false);
					print("You have been given a Glock 17");		
				}
				else if(item_select == 5){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_DEAGLE,AMMO_MAX,false);
					print("You have been given a Desert Eagle");		
				}
				else if(item_select == 6){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SHOTGUN,AMMO_MAX,false);
					print("You have been given a Pump Shotgun");		
				}
				else if(item_select == 7){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BARETTA,AMMO_MAX,false);
					print("You have been given a Tactical Shotgun");		
				}
				else if(item_select == 8){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MICRO_UZI,AMMO_MAX,false);
					print("You have been given a Micro Uzi");		
				}
				else if(item_select == 9){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MP5,AMMO_MAX,false);
					print("You have been given an MP5");		
				}
				else if(item_select == 10){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_AK47,AMMO_MAX,false);
					print("You have been given an AK-47");		
				}
				else if(item_select == 11){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M4,AMMO_MAX,false);
					print("You have been given an AR-15");		
				}
				else if(item_select == 12){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M40A1,AMMO_MAX,false);
					print("You have been given an M40A1");		
				}
				else if(item_select == 13){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
					print("You have been given a Sniper Rifle");		
				}
				else if(item_select == 14){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
					print("You have been given an RPG");		
				}
				else if(item_select == 15){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
					print("You have been given a baseball bat");		
				}
				else if(item_select == 16){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
					print("You have been given a pool stick");			
				}
				else if(item_select == 17){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_KNIFE,1,false);
					print("You have been given a knife");			
				}
				else if(item_select == 18){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MOLOTOV,AMMO_MAX,false);
					print("You have been given a molotov");			
				}
				return;
			}
			if(last_selected[1] == 5){
				if(item_select == 1){
					if(!objectgun) print("Use the Glock to shoot the selected object");
					do_toggle(objectgun);
					return;
				}
				else if(item_select == 2){
					if(!del_objgun) print_long("~b~Every shot will delete the last shot object");
					do_toggle(del_objgun);
					return;
				}
				else if(item_select == 3){
					object_launch = 0x3675A6C3;
					print("Object launcher will now shoot Dildos");
				}
				else if(item_select == 4){
					object_launch = 0x2718C626;
					print("Object launcher will now shoot Red cubes");
				}
				else if(item_select == 5){
					object_launch = 0xDD28B247;
					print("Object launcher will now shoot Blue cubes");
				}
				else if(item_select == 6){
					object_launch = 0xBB1F6E71;
					print("Object launcher will now shoot Green cubes");
				}
				else if(item_select == 7){
					object_launch = 0x90FA92C6;
					print("Object launcher will now shoot Bowling Balls");
				}
				else if(item_select == 8){
					object_launch = 0x3C4E43BC;
					print("Object launcher will now shoot Donuts");
				}
				else if(item_select == 9){
					object_launch = 0xFE520830;
					print("Object launcher will now shoot Bricks");
				}
				else if(item_select == 10){
					object_launch = 0x94A8F60F;
					print("Object launcher will now shoot Bins");
				}
				else if(item_select == 11){
					object_launch = 0xEB12D336;
					print("Object launcher will now shoot Dumpsters");
				}
				else if(item_select == 12){
					object_launch = 0x6066DF1D;
					print("Object launcher will now shoot gumball machines");
				}
				else if(item_select == 13){
					object_launch = 0xF4A206E4;
					print("Object launcher will now shoot Bowling Pins");
				}
				else if(item_select == 14){
					object_launch = 0x7FC5F693;
					print("Object launcher will now shoot Sprunk Boxes");
				}
				else if(item_select == 15){
					object_launch = 0xD318157E;
					print("Object launcher will now shoot TV's");
				}
			}
			if(last_selected[1] == 7){
				if(item_select == 1){
					if(!cargun) print("Use the Deagle to shoot the selected car");
					do_toggle(cargun);
					return;
				}
				else if(item_select == 2){
					if(!del_cargun) print_long("~b~Every shot will delete the last shot car");
					do_toggle(del_cargun);
					return;
				}
				else if(item_select == 3){
					if(!exp_cargun) print_long("~b~Every shot car will explode on impact");
					do_toggle(exp_cargun);
					return;
				}
				else if(item_select == 4){
					car_launch = MODEL_SULTANRS;
					print("Car launcher will now shoot Sultan RS's");
					return;
				}
				else if(item_select == 5){
					car_launch = MODEL_BUS;
					print("Car launcher will now shoot Bus's");
					return;
				}
				else if(item_select == 6){
					car_launch = MODEL_FLATBED;
					print("Car launcher will now shoot Bus's");
					return;
				}
			}
		}
		if(last_selected[0] == 5){
			if(last_selected[1] == 1){
				if(item_select == 1){
					s_r = 160;
					s_g = 32;
					s_b = 240;
					return;
				}
				if(item_select == 2){
					s_r = 255;
					s_g = 0;
					s_b = 0;
					return;
				}
				if(item_select == 3){
					s_r = 0;
					s_g = 191;
					s_b = 255;
					return;
				}
				if(item_select == 4){
					s_r = 0;
					s_g = 255;
					s_b = 0;
					return;
				}
				if(item_select == 5){
					s_r = 255;
					s_g = 0;
					s_b = 255;
					return;
				}
				if(item_select == 6){
					s_r = 218;
					s_g = 165;
					s_b = 32;
					return;
				}
				if(item_select == 7){
					s_r = 105;
					s_g = 105;
					s_b = 105;
					return;
				}
				if(item_select == 8){
					s_r = 0;
					s_g = 0;
					s_b = 255;
					return;
				}
				if(item_select == 9){
					do_toggle(rainbowmenu);
					return;
				}
			}
			if(last_selected[1] == 2){
				if(item_select == 1){
					int i = 0;
					for(i;i <= 5;i++){
						create_throwable_object(0x9976ECC4);
					}
				}
				if(item_select == 2){
					create_throwable_object(0x6066DF1D);
				}
				if(item_select == 3){
					create_throwable_object(0x2718C626);
					create_throwable_object(0xDD28B247);
					create_throwable_object(0xCCEA11CA);
					create_throwable_object(0xBB1F6E71);
					create_throwable_object(0xA6E545FD);
					create_throwable_object(0x5C5030D4);
				}
				if(item_select == 4){
					int i = 0;
					for(i;i <= 5;i++){
						create_throwable_object(0x9D2A7EF8);
					}
				}
				if(item_select == 5){
					int i = 0;
					for(i;i <= 5;i++){
						create_throwable_object(0x501811B6);
					}
				}
				if(item_select == 6){
					int i = 0;
					for(i;i <= 5;i++){
						create_throwable_object(0x48FA2738);
					}
				}
				if(item_select == 7){
					create_throwable_object(0x8079978D);
				}
				if(item_select == 8){
					create_throwable_object(0x3129B913);
				}
				if(item_select == 9){
					create_throwable_object(0xF4A206E4);
				}	
				if(item_select == 10){	
					create_throwable_object(0x7FC5F693);	
				}
				if(item_select == 11){	
					create_throwable_object(0xD318157E);	
				}	
				if(item_select == 12){	
					create_throwable_object(0x90FA92C6);	
				}
			}
			if(last_selected[1] == 3){
				if(item_select == 1){
					create_big_explosion(2247.4224,755.9057,5.853);
					WAIT(500);
					create_big_explosion(2231.6912,737.4642,5.853);
					WAIT(500);
					create_big_explosion(2214.0000,718.9000,5.83);
					WAIT(500);
					print("Launching strike at Aiport helipads!");				
					return;
				}
				if(item_select == 2){
					create_big_explosion(2621.6484,445.9162,5.35);
					print("Launching strike at Aiport Tower!");
					return;
				}
				if(item_select == 3){
					create_big_explosion(2268.2544,519.2332,5.4396);
					WAIT(500);
					create_big_explosion(2228.9453,526.2129,5.4401);
					WAIT(500);
					create_big_explosion(2221.8818,484.9935,5.4562);
					WAIT(500);
					create_big_explosion(2234.6369,456.6962,5.4562);
					print("Launching strike at Aiport parking!");
					return;
				}
				if(item_select == 4){
					xmc_airstrike();
					return;
				}
			}
		}
	}
	if(menu_level == 3){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){ //Online players
				if(last_selected[2] == 1){ //All players
					uint player_loop = player_count - 1;
					uint i;
					if(item_select == 1){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								REMOVE_ALL_CHAR_WEAPONS(players[i].ped);
								WAIT(10);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_DEAGLE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_GRENADE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_MP5,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_M4,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_BARETTA,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_POOLCUE,1,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_ARMOUR,1,false);
								ADD_ARMOUR_TO_CHAR(players[i].ped,99);
							}
						}
						print("Gave everyone weapons");
						return;
					}
					else if(item_select == 2){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								REMOVE_ALL_CHAR_WEAPONS(players[i].ped);
								WAIT(10);
							}
						}
						print("Removed everyones weapons");
						return;
					}
					else if(item_select == 3){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								GET_CHAR_COORDINATES(players[i].ped,&x,&y,&z);
								ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,50.0,true,false,0.7);
								WAIT(10);
							}
						}
						print("Everyone was exploded");
						return;
					}
					else if(item_select == 4){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								START_CHAR_FIRE(players[i].ped);
								WAIT(10);
							}
						}
						print("Everyone was set on fire");
						return;
					}
					else if(item_select == 5){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								Object otmp;
								CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
								
								ATTACH_OBJECT_TO_PED(otmp,players[i].ped,0,0.0,0.0,-0.11,0.0,0.0,3.0,false);
								WAIT(10);
							}
						}
						print("Hippoed everyone");
						return;
					}
					else if(item_select == 6){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
									// Vehicle pveh;
									GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										if(tick >= 200){
											//print("Error");
											//return;
											continue;
										}
										WAIT(0);
									}
									DELETE_CAR(&pveh);
									WAIT(10);
									MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
								}
							}
							WAIT(50);
						}
						print("Deleted everyones cars");
						return;
					}
					else if(item_select == 7){
						//// float x,y,z;
						GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
						FREEZE_CHAR_POSITION(pPlayer,true);
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
									teleport_char(players[i].ped,x,y,z);
									WAIT(100);
								}
							}
						}
						print("Party time!");
						WAIT(500);
						FREEZE_CHAR_POSITION(pPlayer,false);
						return;
					}
					else if(item_select == 8){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
									teleport_char(players[i].ped,-1079.8,-469.7,2.62);
									WAIT(100);
								}
							}
						}
						print("Put in derby");
						return;
					}
					else if(item_select == 9){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								REMOVE_ALL_CHAR_WEAPONS(players[i].ped);
								WAIT(10);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_ROCKET,AMMO_MAX,false);
								print("Everyone should freeze when aiming weapon");
								return;
							}
						}	   
					}
					else if(item_select == 10){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
									GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											//print("Error");
											//return;
											continue;
										}
										WAIT(0);
									}
									APPLY_FORCE_TO_CAR(pveh,true,0.0,0.0,1000.0,0.0,0.0,0.0,true,true,true,true);
								}
							}
						}
					print("Slingshoted everyones cars");
					return;
					}
				}
				else{
					uint index = (last_selected[2] - 2);
					if(item_select == 1){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(menu[item_select].value == 1){
								REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
								WAIT(10);
								GIVE_WEAPON_TO_CHAR(players[index].ped, WEAPON_UNARMED, AMMO_MAX, false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_POOLCUE,1,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_DEAGLE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_GRENADE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MP5,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BARETTA,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_M4,AMMO_MAX,false);
								
							}
							else if(menu[item_select].value == 2){
								REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
								WAIT(10);
								GIVE_WEAPON_TO_CHAR(players[index].ped, WEAPON_UNARMED, AMMO_MAX, false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_PISTOL,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MOLOTOV,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MICRO_UZI,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_AK47,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_SHOTGUN,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_M40A1,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_POOLCUE,1,false);					
							}
							else if(menu[item_select].value == 3){
								uint episode = GET_CURRENT_EPISODE();
								if(episode == 2){
									REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
									WAIT(10);
									GIVE_WEAPON_TO_CHAR(players[index].ped, WEAPON_UNARMED, AMMO_MAX, false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_9,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_10,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_13,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_14,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_15,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_1,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_16,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_POOLCUE,1,false);
								}
								else{
									print("You must be on The Ballad of Gay Tony to use this option");
									return;
								}
							}
							GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_ARMOUR,1,false);
							ADD_ARMOUR_TO_CHAR(players[index].ped,99);
							print("Player is now armed & dangerous!");
							return;
						}
					}
					else if(item_select == 2){ 
						if(DOES_CHAR_EXIST(players[index].ped)){
							REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
							print("Player is now unarmed!");
							return;
						}
					}
					else if(item_select == 3){
						int tmp = players[index].id;
						do_toggle(players[tmp].mprotection);
						return;
					}
					else if(item_select == 4){
						int tmp = players[index].id;
						do_toggle(players[tmp].force);
						return;
					}
					else if(item_select == 7){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 200){
										print("Error");
										return;
									}
									WAIT(0);
								}
								SET_CAR_CAN_BE_DAMAGED(pveh,true);
								SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
								SET_CAN_BURST_CAR_TYRES(pveh,true);
							}
							print("Whiskey Tango, this is Rubber Ducky comin' in hot!");
							// // float x,y,z;
							GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
							create_big_explosion(x,y,z);						
						}
					}
					else if(item_select == 8){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(GET_HOST_ID() != GET_PLAYER_ID()){
								if(!IS_CHAR_IN_ANY_CAR(players[index].ped)){
									// float x,y,z;
									GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
									ADD_EXPLOSION(x,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
									ADD_EXPLOSION(x + 1.5,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
									ADD_EXPLOSION(x,y + 1.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
									ADD_EXPLOSION(x - 1.5,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
									ADD_EXPLOSION(x,y - 1.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
									ADD_EXPLOSION(x + 0.5,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
									ADD_EXPLOSION(x,y + 0.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
									ADD_EXPLOSION(x - 0.5,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
									ADD_EXPLOSION(x,y - 0.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
									print("Tazed Nigga!");
								}
								else print("Player must be on foot");
							}
							else print("You can't be host");
						}
					}
					else if(item_select == 9){
						#ifndef PERSONAL
						if(is_whitelisted(index)){
							print("Player is whitelisted");
							return;
						}
						#endif
						if(DOES_CHAR_EXIST(index)){
							if(GET_PLAYER_ID() == GET_HOST_ID())
								NETWORK_KICK_PLAYER(players[index].id,true);
							else
								print("You are not host");
							return;
						}
					}
					else if(item_select == 10){
						#ifndef PERSONAL
						if(is_whitelisted(index)){
							print("Player is whitelisted");
							return;
						}
						#endif
						if(DOES_CHAR_EXIST(players[index].ped)){
							#ifndef PERSONAL
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 200){
										print("~r~Player is in car, and can't delete");
										return;
									}
									WAIT(0);
								}
								DELETE_CAR(&pveh);
								MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
							}
							REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
							WAIT(10);
							GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_ROCKET,AMMO_MAX,false);
							print("~g~Sent Player Freeze gun");
							#else
							GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
							if(!DOES_GROUP_EXIST(Bgroup)){
								CREATE_GROUP(0, Bgroup, true);
								SET_GROUP_LEADER(Bgroup, pPlayer);
							}
							SET_GROUP_MEMBER(Bgroup,players[index].ped);
							SET_GROUP_FORMATION(Bgroup, 2);
							REMOVE_CHAR_FROM_GROUP(players[index].ped);
							print("~g~Player Frozen");
							#endif
							return;
						}
						return;
					}
					else if(item_select == 11){
						if(DOES_CHAR_EXIST(players[index].ped)){
							START_CHAR_FIRE(players[index].ped);
							WAIT(10);
							print("Player was set on Fire.");
						}
					return;
					}
					else if(item_select == 12){
						if(DOES_CHAR_EXIST(players[index].ped)){
							Object otmp;
							CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
							ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0,0.0,0.0,-0.11,0.0,0.0,3.0,false);
							WAIT(10);
							print("Get Hippoed Nigga");
						}
						return;
					}
					else if(item_select == 14){
						#ifndef PERSONAL
						if(is_whitelisted(index)){
							print("Player is whitelisted");
							return;
						}
						#endif
						if((DOES_CHAR_EXIST(players[index].ped)) && (IS_CHAR_IN_ANY_CAR(pPlayer))){
							float mx,my,mz;
							GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
							GET_CHAR_COORDINATES(players[index].ped,&mx,&my,&mz);
							GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz,&dist);
							if((dist >= 10) && (DOES_GROUP_EXIST(Bgroup))){
								print_long("Victim to far away");
								group_loop = false;
								return;
							}
							GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
							GET_DRIVER_OF_CAR(pveh,&driver);
							if(pPlayer == driver){
								GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
								if(!DOES_GROUP_EXIST(Bgroup)){
									CREATE_GROUP(0, Bgroup, true);
									SET_GROUP_LEADER(Bgroup, pPlayer);
								}
								SET_GROUP_MEMBER(Bgroup,players[index].ped);
								SET_GROUP_FORMATION(Bgroup, 2);
							//	SET_GROUP_SEPARATION_RANGE(Bgroup, 9999);
								group_onlineped = players[index].ped;
								group_loop = true;
								print("~r~Forcing player into car");
								return;
							}
							else print("You must be driver");
						}
						else print("You must be in a car");
						return;
					}
				}
			}
		}
		if(last_selected[0] == 1){
			if(last_selected[1] == 2){
				if(last_selected[2] == 1){
					if(item_select == 1){
						if(menu[item_select].value == 1){
							//Request the anim and make sure it exists then load it
							//This also sets what group of anims your going to be selecting from
							REQUEST_ANIMS("amb@park_taichi_a");
							//Do not proceed until animation group is loaded
							//mainly to avoid freezing
							while(!HAVE_ANIMS_LOADED("amb@park_taichi_a")) WAIT(0);
							//Anims are like a group of dances/moves. Call one in the group you loaded above down here
							//then also say stuff like how long to play dance and if to repeat
							// amb@park_taichi_a = Anim Group    taichi01 = Specific Dance in the loaded anim group
							//pPlayer = you      8.0 = seconds to play
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"taichi01","amb@park_taichi_a",8.0,0,0);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@park_taichi_b");
							while(!HAVE_ANIMS_LOADED("amb@park_taichi_b")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"taichi02","amb@park_taichi_b",8.0,0,0);
							return;
						}					
					}
					if(item_select == 2){
						if(menu[item_select].value == 1){
							REQUEST_ANIMS("amb@dance_maleidl_a");
							while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_a")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_a","amb@dance_maleidl_a",8.0,0,0);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@dance_maleidl_b");
							while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_b")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_maleidl_b",8.0,0,0);
							return;
						}
						if(menu[item_select].value == 3){
							REQUEST_ANIMS("amb@dance_maleidl_c");
							while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_c")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_c","amb@dance_maleidl_c",8.0,0,0);
							return;
						}
						if(menu[item_select].value == 4){
							REQUEST_ANIMS("amb@dance_maleidl_b");
							while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_b")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_maleidl_b",8.0,0,0);
							return;
						}
					}
					if(item_select == 3){
						if(menu[item_select].value == 1){
							REQUEST_ANIMS("amb@dance_femidl_a");
							while(!HAVE_ANIMS_LOADED("amb@dance_femidl_a")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_a","amb@dance_femidl_a",8.0,0,0);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@dance_femidl_b");
							while(!HAVE_ANIMS_LOADED("amb@dance_femidl_b")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_femidl_b",8.0,0,0);
							return;
						}
						if(menu[item_select].value == 3){
							REQUEST_ANIMS("amb@dance_femidl_c");
							while(!HAVE_ANIMS_LOADED("amb@dance_femidl_c")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_c","amb@dance_femidl_c",8.0,0,0);
							return;
						}					
					}
					if(item_select == 4){
						REQUEST_ANIMS("missstripclublo");
						while(!HAVE_ANIMS_LOADED("missstripclublo")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"pole_dance_a","missstripclublo",8.0,0,0);
						return;
					}
					if(item_select == 5){
						SWITCH_PED_TO_RAGDOLL(pPlayer,20,30,false,false,false,false);
						SWITCH_PED_TO_ANIMATED(pPlayer,true);
						GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),true);
						WAIT(30);
						SWITCH_PED_TO_ANIMATED(pPlayer,false);
						GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),false);
						return;
					}
					if(item_select == 6){
						if(!ragdoll) print("Press LB + B to ragdoll");
						do_toggle(ragdoll);
						return;
					}
					if(item_select == 7){
						REQUEST_ANIMS("misscar_sex");
						while(!HAVE_ANIMS_LOADED("misscar_sex")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"m_handjob_intro_low","misscar_sex",8.0,0,0x20);
						return;
					}
					if(item_select == 8){
						REQUEST_ANIMS("busted");
						while(!HAVE_ANIMS_LOADED("busted")) WAIT(0); 
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"idle_2_hands_up","busted",8.0,0,0x20);
						return;
					}
					if(item_select == 9){
						REQUEST_ANIMS("amb@smoking");
						while(!HAVE_ANIMS_LOADED("amb@smoking")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"stand_smoke","amb@smoking",8.0,0,0x20);
						return;
					}
				}
				else if(last_selected[2] == 2){
					if(item_select == 1){
						SAY_AMBIENT_SPEECH(pPlayer, "Thanks", 1, 1, 0);
						print("~g~Thanks!");
						return;
					}
					else if(item_select == 2){
						HIGH_FALL_SCREAM(pPlayer);
						print("~g~AAAAHHHHHHH!");
						return;
				   }
					else if(item_select == 3){
						SAY_AMBIENT_SPEECH(pPlayer, "GET_OUT_OF_HERE", 1, 1, 0);
						print("~g~Get out of here!");
						return;
					}
					else if(item_select == 4){
						SAY_AMBIENT_SPEECH(pPlayer, "GENERIC_HI", 1, 1, 0);
						print("~g~Hi!");
						return;
					}
					else if(item_select == 5){
						SAY_AMBIENT_SPEECH(pPlayer, "HOOKER_SEX", 1, 1, 0);
						print("~g~Sexy time!");
						return;
					}
					return;
				}
			}
			if(last_selected[1] == 13){
				if(last_selected[2] == 1){
					if(item_select == 1){
						delete_one_spawnguards();
						return;
					}
					else if(item_select == 2){
						delete_all_spawnguards();
						return;
					}
					else if(item_select == 3){
						tele_spawnguards();
						return;
					}
					else if(item_select == 5){
						kill_spawnguards();
						return;
					}
				}
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2){
					// Vehicle pveh;
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						if(IS_VEHICLE_EXTRA_TURNED_ON(pveh,item_select))
							TURN_OFF_VEHICLE_EXTRA(pveh,item_select,true);
						else
							TURN_OFF_VEHICLE_EXTRA(pveh,item_select,false);
							
						reset_menu();
						return;
					}
					print("You must be in a vehicle");
				}
				if(last_selected[2] == 3){
					// Vehicle pveh;
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						if(item_select == 1){
							uint color1,color2;
							GET_CAR_COLOURS(pveh,&color1,&color2);
							CHANGE_CAR_COLOUR(pveh,(menu[item_select].value - 1),color2);
							return;
						}
						if(item_select == 2){
							uint color1,color2;
							GET_CAR_COLOURS(pveh,&color1,&color2);
							CHANGE_CAR_COLOUR(pveh,color1,(menu[item_select].value - 1));
							return;
						}
						if(item_select == 3){
							uint color1,color2;
							GET_EXTRA_CAR_COLOURS(pveh,&color1,&color2);
							SET_EXTRA_CAR_COLOURS(pveh,(menu[item_select].value - 1),color2);
							return;
						}	
						if(item_select == 4){
							uint color1,color2;
							GET_EXTRA_CAR_COLOURS(pveh,&color1,&color2);
							SET_EXTRA_CAR_COLOURS(pveh,color1,(menu[item_select].value - 1));
							return;
						}						
					}
					print("You must be in a vehicle");
					return;
				}
				if(last_selected[2] == 4){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						if(item_select == 1){
							Object lights;
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.4,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							SET_OBJECT_VISIBLE(lights, true);
							print("Added Blue Neons");
							return;
						}
						else if(item_select == 2){
							if(GET_CURRENT_EPISODE() == 2){
								Object lights;
								CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
								WAIT(1);
								ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
								SET_OBJECT_LIGHTS(lights, true);
								SET_OBJECT_VISIBLE(lights, true);
								SET_OBJECT_INVINCIBLE(lights, 1);
								CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
								WAIT(1);
								ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
								SET_OBJECT_LIGHTS(lights, true);
								SET_OBJECT_VISIBLE(lights, true);
								SET_OBJECT_INVINCIBLE(lights, 1);
								CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
								WAIT(1);
								ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
								SET_OBJECT_LIGHTS(lights, true);
								SET_OBJECT_VISIBLE(lights, true);
								SET_OBJECT_INVINCIBLE(lights, 1);
								CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
								WAIT(1);
								ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
								SET_OBJECT_LIGHTS(lights, true);
								SET_OBJECT_VISIBLE(lights, true);
								SET_OBJECT_INVINCIBLE(lights, 1);
								print("Added Yellow Neons");
								return;
							}
							else{
								print("You must be on ~r~TBOGT to use");
								return;
							}
						}
						else if(item_select == 3){
							Object lights;
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							print("Added Red Neons");
							return;
						}
						else if(item_select == 4){
							Object lights;
							//blue
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.4,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							SET_OBJECT_VISIBLE(lights, true);
							//red
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							print("Added Pink Neons");
							return;
						}
					}
				}
				if(last_selected[2] == 5){
					if(item_select == 1){
						spawn_car(MODEL_SANCHEZ);
						WAIT(10);
						GET_CAR_CHAR_IS_USING(GetPlayerPed(),&pveh);
						SET_CAR_VISIBLE(pveh,0);
						attachobjecttocar(pveh,0x1F3154CE,-0.0085,-0.0377,0.1170,0,0,1.5600);
						attachobjecttocar(pveh,0x1B11B700,-0.1500,0.5005,-0.1988,0,0,1.5797);
						attachobjecttocar(pveh,0x1B11B700,0.1102,0.5017,-0.2000,0,0,-1.5630);
						attachobjecttocar(pveh,0x1B11B700,-0.1370,-0.6510,-0.1318,0,0,1.5653);
						attachobjecttocar(pveh,0x1B11B700,0.1050,-0.6508,-0.1363,0,0,-1.5547);
						print("~g~BMX Sanchez by Big Fish 500 and Buffeting");
						return;
					}
					if(item_select == 2){
						Vehicle car;
						spawn_car(MODEL_PHANTOM);
						WAIT(10);
						GET_CAR_CHAR_IS_USING(GetPlayerPed(),&car);
						SET_CAR_VISIBLE(car,0);
						attachobjecttocar(car,0x5BE14B23,-0.2623,2.0525,0.2407,0,0,0);
						attachobjecttocar(car,0x928B899D,-0.2630,3.6310,1.2702,4.6663,0,3.1468);
						attachobjecttocar(car,0xF40BE44B,0.7122,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,-1.5710,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,0.9575,0.8092,-0.5478,0,1.5418,0);
						WAIT(10);
						attachobjecttocar(car,0xF40BE44B,-1.8090,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,-1.5710,3.7305,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,0.7122,3.7305,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,-1.8090,3.7305,-0.5478,0,1.5418,0);
						WAIT(10);
						attachobjecttocar(car,0xF40BE44B,0.9575,3.7305,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,1.2240,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,-2.0780,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xB76637D8,0.2417,2.0260,0.7427,3.1242,0,-1.5610);
						WAIT(10);
						attachobjecttocar(car,0xB76637D8,-0.8500,2.0260,0.7427,3.1242,0,-1.5610);
						attachobjecttocar(car,0xB76637D8,-0.2168,2.1908,1.7035,0,0,4.6952);
						attachobjecttocar(car,0x572BBD50,-0.2508,-0.3298,0.7502,0,0,0);
						WAIT(10);
						attachobjecttocar(car,0x455B19AF,-0.2635,4.4328,0.7648,0,0,3.1288);
						attachobjecttocar(car,0xF814AD1E,-1.7610,0.8108,-0.6930,0,1.5860,0);
						attachobjecttocar(car,0xF814AD1E,-1.7610,3.7425,-0.6930,0,1.5860,0);
						WAIT(10);
						attachobjecttocar(car,0x7F53DD7E,-0.2195,0.8285,-0.2305,0.7232,0,1.5207);
						attachobjecttocar(car,0x7F53DD7E,-0.2195,3.7613,-0.2305,0.7232,0,1.5207);
						attachobjecttocar(car,0x7F53DD7E,-0.3333,3.7613,-0.2305,0.7232,0,4.7585);
						attachobjecttocar(car,0x7F53DD7E,-0.3333,0.8285,-0.2305,0.7232,0,4.7585);
						WAIT(10);
						attachobjecttocar(car,0x1AE7947B,0.3250,0.5665,0.3285,1.5662,0,0);
						attachobjecttocar(car,0x1AE7947B,-0.2618,0.5665,0.3285,1.5662,0,0);
						attachobjecttocar(car,0x1AE7947B,-0.8925,0.5665,0.3285,1.5662,0,0);
						attachobjecttocar(car,0x3FF24020,1.1743,3.7443,-0.5195,0.0017,0,1.5385);
						WAIT(10);
						attachobjecttocar(car,0x3FF24020,-1.6692,3.7443,-0.5305,0.0393,0,4.7470);
						attachobjecttocar(car,0x3FF24020,1.4160,0.8272,-0.5305,0.0393,0,1.5385);
						attachobjecttocar(car,0x3FF24020,-1.9380,0.8272,-0.5305,0.0393,0,4.7470);
						attachobjecttocar(car,0x41303AF8,-0.2735,4.0410,1.2805,0,0,0);
						WAIT(10);
						print("~g~Monster Truck by Boubouvirus");
						return;
					}
				}	
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2 && GET_CURRENT_EPISODE() == 2){
					if(item_select == 1){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_9,AMMO_MAX,false);
						print("You have been given a .44 Pistol.");
						return;
					}
					if(item_select == 2){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_10,AMMO_MAX,false);
						print("You have been given an Explosive AA12.");
						return;
					}
					if(item_select == 3){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_11,AMMO_MAX,false);
						print("You have been given an AA12.");
						return;
					}
					if(item_select == 4){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_12,AMMO_MAX,false);
						print("You have been given a P-90.");
						return;
					}
					if(item_select == 5){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_13,AMMO_MAX,false);
						print("You have been given an Uzi.");
						return;
					}
					if(item_select == 6){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_14,AMMO_MAX,false);
						print("You have been given an M249.");
						return;
					}
					if(item_select == 7){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_15,AMMO_MAX,false);
						print("You have been given an Explosive Sniper.");
						return;
					}
					if(item_select == 8){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_1,AMMO_MAX,false);
						print("You have been given a Grenade Launcher.");
						return;
					}
					if(item_select == 9){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_16,AMMO_MAX,false);
						print("You have been given some Sticky Bombs.");
						return;
					}					
				}
			}
		}
	}
	if(menu_level == 4){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){
				if(last_selected[2] != 1){
					if(last_selected[3] == 5){
						uint index = (last_selected[2] - 2);
							if(item_select == 1){
								 if(DOES_CHAR_EXIST(players[index].ped)){
									//// float x,y,z;
									GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
									teleport_char(pPlayer,x,y,z);
									print("Teleported to player");
									return;
								}
							}
							else if(item_select == 2){
								if(DOES_CHAR_EXIST(players[index].ped)){
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										// Vehicle pveh;
										uint i;
										Ped tmp;
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										for(i = 0;i <= 2;i++){
											if(IS_CAR_PASSENGER_SEAT_FREE(pveh,i)){
												WARP_CHAR_INTO_CAR_AS_PASSENGER(pPlayer,pveh,i);
												print("Teleported to player's car");
												return;
											}
										}
									}
									else print("Player ain't in no vehicle!");
									return;
								}
							}
							else if(item_select == 3){
								if(DOES_CHAR_EXIST(players[index].ped)){
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										//// float x,y,z;
										GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
										if(!IS_CHAR_IN_ANY_CAR(pPlayer)) FREEZE_CHAR_POSITION(pPlayer,true);
										else{
											GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
											FREEZE_CAR_POSITION(pveh,true);
										}
										teleport_char(players[index].ped,x,y,z);
										WAIT(1000);
										if(!IS_CHAR_IN_ANY_CAR(pPlayer)) FREEZE_CHAR_POSITION(pPlayer,false);
										else{
											GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
											FREEZE_CAR_POSITION(pveh,false);
										}
										return;
									}
									else print("Player ain't in no vehicle!");
									return;
								}
							}
							else if(item_select == 4){
								if(DOES_CHAR_EXIST(players[index].ped)){
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										// // float x,y,z;
										if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
											Vector3 pos;
											GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&pos);
											GET_GROUND_Z_FOR_3D_COORD(pos.x,pos.y,1000,&z);
											teleport_char(players[index].ped,pos.x,pos.y,z + 5);
											print("Player teleported to waypoint");
											return;
										}
										else{
										print("You need to set a waypoint!");
										return;
										}
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
							else if(item_select == 5){
								if(DOES_CHAR_EXIST(players[index].ped)){
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("Error");
												return;
											}
											WAIT(0);
										}
										REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
										SET_CAR_COORDINATES(pveh,-1079.8,-469.7,2.62);
										WAIT(500);
										DELETE_CAR(&pveh);
										MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
										return;
									}
									else print("Player ain't in no vehicle!");
									return;
								}						
							}
							else if(item_select == 6){
								if(DOES_CHAR_EXIST(players[index].ped)){
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										teleport_char(players[index].ped,2175.3516,761.2235,30.0);
										print("Player teleported to Airport");
										return;
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
						return;
					}
					else if(last_selected[3] == 6){
						uint index = (last_selected[2] - 2);
						if(item_select == 1){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									// Vehicle pveh;
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									ATTACH_PED_TO_CAR(pPlayer,pveh,0,0.00,0.00,1.5,0.00,0.00,1,1);
									print("Player attached to vehicle");
								}
								else print("Player needs to be in a vehicle");
							}
							return;
						}
						else if(item_select == 2){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("Error");
											return;
										}
										WAIT(0);
									}
									DELETE_CAR(&pveh);
									MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
								}
								else print("Player not in vehicle");
							}
						}
						else if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("Error");
											return;
										}
										WAIT(0);
									}
									APPLY_FORCE_TO_CAR(pveh,true,0.0,0.0,1000.0,0.0,0.0,0.0,true,true,true,true);
								}
								else print("Player not in vehicle");
							}
						}
						else if(item_select == 4){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("Error");
											return;
										}
										WAIT(0);
									}
								//	FREEZE_CAR_POSITION(pveh,true);
									SET_CAR_CAN_BE_DAMAGED(pveh,true);
									SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
									SET_CAN_BURST_CAR_TYRES(pveh,true);
									BURST_CAR_TYRE(pveh,0);
									BURST_CAR_TYRE(pveh,1);
									BURST_CAR_TYRE(pveh,4);
									BURST_CAR_TYRE(pveh,5);
									SET_ENGINE_HEALTH(pveh,0.0);
									SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
									print("Made player's car retarded");
								}
							}
							return;
						}
						else if(item_select == 5){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("Error");
											return;
										}
										WAIT(0);
									}
									SET_CAR_PROOFS(pveh, true, true, true, true, true);
									SET_CAR_CAN_BE_DAMAGED(pveh,false);
									SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,false);
									SET_CAN_BURST_CAR_TYRES(pveh,false);
									print("Made player's car Invincible");
								}
							}
							return;
						}
						else if(item_select == 6){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									float speed;
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("Error");
											return;
										}
										WAIT(0);
									}
									GET_CAR_SPEED(pveh,&speed);
									SET_CAR_FORWARD_SPEED(pveh,(speed * 6));
									print("Boosted Player's car");
								}
							}
							return;
						}
						else if(item_select == 7){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									float speed;
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("Error");
											return;
										}
										WAIT(0);
									}
									GET_CAR_SPEED(pveh,&speed);
									SET_CAR_FORWARD_SPEED(pveh,(speed / 10));
									print("Halted Player's car");
								}
							}
							return;
						}
						else if(item_select == 8){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(pPlayer)){
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										float x,y,z,heading;
										int paveh;
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_CAR_CHAR_IS_USING(pPlayer,&paveh);
										GET_DRIVER_OF_CAR(paveh,&driver);
										if(driver == pPlayer){
											if((!IS_CHAR_IN_ANY_BOAT(players[index].ped)) && (!IS_CHAR_IN_ANY_HELI(players[index].ped))){
												GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
												REQUEST_CONTROL_OF_NETWORK_ID(nvid);
												while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
													tick++;
													REQUEST_CONTROL_OF_NETWORK_ID(nvid);
													if(tick >= 200){
														print("Error");
														return;
													}
													WAIT(0);
												}      
												if(!IS_CAR_ATTACHED(pveh)){
													SET_CHAR_VISIBLE(pPlayer, false);
													SET_CAR_VISIBLE(paveh, false);
													GET_CAR_HEADING(pveh,&heading);
													GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
													SET_CAR_HEADING(paveh,heading);
													teleport_char(pPlayer,x,y,z);
													FREEZE_CAR_POSITION(pveh,true);
													ATTACH_CAR_TO_CAR(pveh,paveh,0,0,0,-0.3,0,0,0);
													LOCK_CAR_DOORS(paveh,4);
													LOCK_CAR_DOORS(pveh,4);
													print_long("Players vehicle now under your control. Press again to ~r~disable");
													return;
												}
												else if(IS_CAR_ATTACHED(pveh)){
													SET_CHAR_VISIBLE(pPlayer, true);
													SET_CAR_VISIBLE(paveh, true);
													LOCK_CAR_DOORS(paveh,1);
													LOCK_CAR_DOORS(pveh,1);
													FREEZE_CAR_POSITION(pveh,false);
													DETACH_CAR(pveh);
													print("Players vehicle no longer under control");
													return;
												}
											}
											else print("Player must be in a car or bike");
										}
										else print("You must be the driver of your own vehicle");
									}
									else print("Player not in Vehicle");
								}
								else print("You are not in a Vehicle");
							}
							return;
						}
						else if(item_select == 9){
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								uint lock;
								// Vehicle pveh;
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 200){
										print("Error");
										return;
									}
									WAIT(0);
								}      
								GET_CAR_DOOR_LOCK_STATUS(pveh,&lock);
								if(lock == VEHICLE_DOOR_UNLOCKED){
									LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_LOCKED_BOTH_SIDES);
									print("Doors locked!");
								}
								else{
									LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_UNLOCKED);
									print("Doors unlocked!");
								}
							}
							return;
						}
						else if(item_select == 10){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_HELI(pPlayer)){
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										float heading;
										float offset_y, offset_z;
										Vehicle paveh,pveh;
										Object Object1;
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_CAR_CHAR_IS_USING(pPlayer,&paveh);
										GET_DRIVER_OF_CAR(paveh,&driver);
										if(driver == pPlayer){
											GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
												tick++;
												REQUEST_CONTROL_OF_NETWORK_ID(nvid);
												if(tick >= 200){
													print("Error");
													return;
												}
												WAIT(0);
											}
											if(!IS_CAR_ATTACHED(pveh)){
												Vector3 minimum,maximum;
												GET_CAR_MODEL(paveh, &model);
												GET_MODEL_DIMENSIONS(model, &minimum, &maximum);
												if (IS_CAR_MODEL(paveh, MODEL_SKYLIFT)){
														// Skylift
														offset_y = 1.15f;
														offset_z = 0.22f;
													
													GET_CAR_HEADING(paveh,&heading);
													GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
													SET_CAR_HEADING(pveh,heading);
													teleport_char(players[index].ped,x,y,z);
													FREEZE_CAR_POSITION(pveh,true);
													ATTACH_CAR_TO_CAR(pveh,paveh,0,0.0,offset_y,offset_z,0.0,0.0,0.0);
													LOCK_CAR_DOORS(paveh,4);
													LOCK_CAR_DOORS(pveh,4);
												}
												else{
													REQUEST_MODEL(MODEL_CAR_WINCH);
													while(!HAS_MODEL_LOADED(MODEL_CAR_WINCH)) WAIT(0);
													CREATE_OBJECT(MODEL_CAR_WINCH,x,y,z,&Object1,true);
													ATTACH_OBJECT_TO_CAR(Object1,paveh,0,0,-1.2403,-0.3493,0,-1.07,1.5397);
													MARK_MODEL_AS_NO_LONGER_NEEDED(MODEL_CAR_WINCH);
													CREATE_OBJECT(MODEL_CAR_WINCH,x,y,z,&Object1,true);
													ATTACH_OBJECT_TO_CAR(Object1,paveh,0,0,1.6342,1.0,0,-1.3320,1.6270);
													MARK_MODEL_AS_NO_LONGER_NEEDED(MODEL_CAR_WINCH);
													GET_CAR_HEADING(paveh,&heading);
													GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
													SET_CAR_HEADING(pveh,heading);
													teleport_char(players[index].ped,x,y,z);
													FREEZE_CAR_POSITION(pveh,true);	
													ATTACH_CAR_TO_CAR(pveh,paveh,0,0,-3,-1.5,0,0,0);
													LOCK_CAR_DOORS(paveh,4);
													LOCK_CAR_DOORS(pveh,4);
												}
												print_long("Vehicle attached to heli.");
												return;
											}
											else if(IS_CAR_ATTACHED(pveh)){
												LOCK_CAR_DOORS(paveh,1);
												LOCK_CAR_DOORS(pveh,1);
												FREEZE_CAR_POSITION(pveh,false);
												DETACH_CAR(pveh);
												print("Vehicle detached from heli.");
												return;
											}
										}
										else print("You must be the driver.");
									}
									else print("Player is not in a vehicle.");
								}
								else print("You are not in a helicopter.");
							}
							return;
						}
						return;
					}
					if(last_selected[3] == 12){
						uint index = (last_selected[2] - 2);
						if(item_select == 1){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef PERSONAL
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								Object otmp;
								CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0,0.0,0.0,-0.11,0.0,0.0,3.0,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached Hippo to Player");
							}
							return;
						}
						else if(item_select == 2){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef PERSONAL
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								Object otmp;
								uint cubes[6],rand;

								cubes[0] = 0x2718C626; //Red
								cubes[1] = 0xDD28B247; //Blue
								cubes[2] = 0xCCEA11CA; //Yellow
								cubes[3] = 0xBB1F6E71; //Green 
								cubes[4] = 0xA6E545FD; //Purple
								cubes[5] = 0x5C5030D4; //Orange

								GENERATE_RANDOM_INT_IN_RANGE(0,5,&rand);

								CREATE_OBJECT(cubes[rand],0.0,0.0,0.0,&otmp,true);
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0x4B5,0.0,0.0,0.0,0.0,0.0,3.0,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached Cube to Player");
							}
							return;
						}
						else if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef PERSONAL
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								Object otmp;
								CREATE_OBJECT(0xB570F614,0.0,0.0,0.0,&otmp,true);
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0,0,.25,-.50,-1.55,3.10,0,0);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached Dick to Player");
							}
							return;
						}
					}
					if(last_selected[3] == 13){
						uint index = (last_selected[2] - 2);
						if(item_select == 1){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef PERSONAL
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
								int test, guards;
								GET_GROUP_SIZE(Bgroup, &test, &guards);	
								if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
									print("No guards Exist or Available");
									return;
								}
								if(DOES_GROUP_EXIST(Bgroup)){
									for(i = 0;i <= 7; i++){
										if(DOES_CHAR_EXIST(gameped[i]) && DOES_CHAR_EXIST(players[index].ped)){
											int nvid;
											GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
											SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
												tick++;
												REQUEST_CONTROL_OF_NETWORK_ID(nvid);
												if(tick >= 250){
													continue;
												}
												WAIT(0);
											}
											TASK_COMBAT(gameped[i], players[index].ped);
											if((i >= 7) || (i == 7) || (i > 6)){
												print("Sent all Guards after the Player");
												return;
											}
										}
									}
								}
							}
							print("Sent all Guards after the Player");
							return;
						}
					}
					if(last_selected[3] == 15){
						uint index = (last_selected[2] - 2);
						if(item_select == 1){
							if(DOES_CHAR_EXIST(players[index].ped)){
								spawn_car_for_char(players[index].ped, MODEL_INFERNUS);
								print("Spawned an Infernus for Player");
							}
							return;
						}
						else if(item_select == 2){
							if(DOES_CHAR_EXIST(players[index].ped)){
								spawn_car_for_char(players[index].ped, MODEL_SULTANRS);
								print("Spawned a Sultan RS for Player");
							}
							return;
						}
						else if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								spawn_car_for_char(players[index].ped, MODEL_BANSHEE);
								print("Spawned a Banshee for Player");
							}
							return;
						}
						else if(item_select == 4){
							if(DOES_CHAR_EXIST(players[index].ped)){
								spawn_car_for_char(players[index].ped, MODEL_COMET);
								print("Spawned a Comet for Player");
							}
							return;
						}
						else if(item_select == 5){
							if(DOES_CHAR_EXIST(players[index].ped)){
								spawn_car_for_char(players[index].ped, MODEL_DINGHY);
								print("Spawned a Dinghy Boat for Player");
							}
							return;
						}
						else if(item_select == 6){
							if(DOES_CHAR_EXIST(players[index].ped)){
								spawn_car_for_char(players[index].ped, MODEL_ANNIHILATOR);
								print("Spawned an Annihilator for Player");
							}
							return;
						}
						else if(item_select == 7){
							if(!GET_CURRENT_EPISODE() == 2) {
								print("You must be on ~r~TBOGT");
								return;
							}
							if(DOES_CHAR_EXIST(players[index].ped)){
								spawn_car_for_char(players[index].ped, MODEL_BULLET);
								print("Spawned a Bullet GT for Player");
							}
							return;
						}
						else if(item_select == 8){
							if(!GET_CURRENT_EPISODE() == 2) {
								print("You must be on ~r~TBOGT");
								return;
							}
							if(DOES_CHAR_EXIST(players[index].ped)){
								spawn_car_for_char(players[index].ped, MODEL_APC);
								print("Spawned an APC Tank for Player");
							}
							return;
						}
						else if(item_select == 9){
							if(!GET_CURRENT_EPISODE() == 2) {
								print("You must be on ~r~TBOGT");
								return;
							}
							if(DOES_CHAR_EXIST(players[index].ped)){
								spawn_car_for_char(players[index].ped, MODEL_BUZZARD);
								print("Spawned an Buzzard heli for Player");
							}
							return;
						}
					}
					if(last_selected[3] == 16){
						uint index = (last_selected[2] - 2);
						if(item_select == 1){
							Object admin_obj;
							GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
							REQUEST_MODEL(MODEL_CJ_PROC_BRICK4);    
							while(!HAS_MODEL_LOADED(MODEL_CJ_PROC_BRICK4)) WAIT(0);
							CREATE_OBJECT(MODEL_CJ_PROC_BRICK4, x, y, z, &admin_obj, 1);
							while(!DOES_OBJECT_EXIST(admin_obj)) WAIT(0);
							SET_OBJECT_INVINCIBLE(admin_obj,0);
							FREEZE_OBJECT_POSITION(admin_obj,0);
							SET_OBJECT_DYNAMIC(admin_obj,1);
							SET_OBJECT_AS_STEALABLE(admin_obj,1);
							SET_OBJECT_COLLISION(admin_obj,1);
							GIVE_PED_PICKUP_OBJECT(pPlayer, admin_obj, true);
							print("~g~Sent a Greeting. Discard object in hand.");
							return;
						}
						else if(item_select == 2){
							Object admin_obj;
							GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
							REQUEST_MODEL(MODEL_CJ_PROC_BRICK3);    
							while(!HAS_MODEL_LOADED(MODEL_CJ_PROC_BRICK3)) WAIT(0);
							CREATE_OBJECT(MODEL_CJ_PROC_BRICK3, x, y, z, &admin_obj, 1);
							while(!DOES_OBJECT_EXIST(admin_obj)) WAIT(0);
							SET_OBJECT_INVINCIBLE(admin_obj,0);
							FREEZE_OBJECT_POSITION(admin_obj,0);
							SET_OBJECT_DYNAMIC(admin_obj,1);
							SET_OBJECT_AS_STEALABLE(admin_obj,1);
							SET_OBJECT_COLLISION(admin_obj,1);
							GIVE_PED_PICKUP_OBJECT(pPlayer, admin_obj, true);
							print("~g~Sent a Warning. Discard object in hand.");
							return;
						}
						else if(item_select == 3){
							Object admin_obj;
							GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
							REQUEST_MODEL(MODEL_CJ_PROC_BRICK);    
							while(!HAS_MODEL_LOADED(MODEL_CJ_PROC_BRICK)) WAIT(0);
							CREATE_OBJECT(MODEL_CJ_PROC_BRICK, x, y, z, &admin_obj, 1);
							while(!DOES_OBJECT_EXIST(admin_obj)) WAIT(0);
							SET_OBJECT_INVINCIBLE(admin_obj,0);
							FREEZE_OBJECT_POSITION(admin_obj,0);
							SET_OBJECT_DYNAMIC(admin_obj,1);
							SET_OBJECT_AS_STEALABLE(admin_obj,1);
							SET_OBJECT_COLLISION(admin_obj,1);
							GIVE_PED_PICKUP_OBJECT(pPlayer, admin_obj, true);
							print("~g~Sent a Menu Disable. Discard object in hand.");
							return;
						}
						else if(item_select == 4){
							Object admin_obj;
							GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
							REQUEST_MODEL(MODEL_CJ_PROC_BRICK2);    
							while(!HAS_MODEL_LOADED(MODEL_CJ_PROC_BRICK2)) WAIT(0);
							CREATE_OBJECT(MODEL_CJ_PROC_BRICK2, x, y, z, &admin_obj, 1);
							while(!DOES_OBJECT_EXIST(admin_obj)) WAIT(0);
							SET_OBJECT_INVINCIBLE(admin_obj,0);
							FREEZE_OBJECT_POSITION(admin_obj,0);
							SET_OBJECT_DYNAMIC(admin_obj,1);
							SET_OBJECT_AS_STEALABLE(admin_obj,1);
							SET_OBJECT_COLLISION(admin_obj,1);
							GIVE_PED_PICKUP_OBJECT(pPlayer, admin_obj, true);
							print_long("~g~Sent a Freeze. Discard object in hand.");
							return;
						}
					}
				}
			}
			if(last_selected[1] == 13){
				if(last_selected[2] == 1){
					if(last_selected[3] == 4){
						if(item_select == 1){
							arm_spawnguards(WEAPON_RLAUNCHER);
							return;
						}
						else if(item_select == 2){
							arm_spawnguards(WEAPON_POOLCUE);
							return;
						}
						else if(item_select == 3){
							arm_spawnguards(WEAPON_M4);
							return;
						}
						else if(item_select == 4){
							arm_spawnguards(WEAPON_DEAGLE);
							return;
						}
						else if(item_select == 5){
							arm_spawnguards(WEAPON_BASEBALLBAT);
							return;
						}
						else if(item_select == 6){
							arm_spawnguards(WEAPON_KNIFE);
							return;
						}
						else if(item_select == 7){
							arm_spawnguards(WEAPON_AK47);
							return;
						}
						else if(item_select == 8){
							arm_spawnguards(WEAPON_SHOTGUN);
							return;
						}
						else if(item_select == 9){
							arm_spawnguards(WEAPON_SNIPERRIFLE);
							return;
						}
						else if(item_select == 10){
							arm_spawnguards(WEAPON_MP5);
							return;
						}
					}
				}
			}
			
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					spawn_car(menu[item_select].value);
					return;
				}
			}
		}
	}
}
void looped_functions(void){
	//player options
	SET_CHAR_INVINCIBLE(pPlayer,godmode);
	GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
	
	#ifndef PERSONAL
	if(xmc_in_game){
		if(!DOES_CHAR_EXIST(xmc_char)) xmc_in_game = false;
		else{
			while(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK){
				print("~r~Menu has been remotely disabled.");
				modderprotect = false;
				WAIT(0);
			}

			if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK2){
				print_long("~r~Remote Message: Your Console has been frozen. Please don't be an ass next time :)");
				WAIT(1000);
				SET_CAR_VISIBLE(GetPlayerPed(), 0);
			}
			
			if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK3){
				modderprotect = false;
				print("~r~Remote Message: Warning from ~g~UtomAfryus69.");
			}

			if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK4){
				print("~b~ Hello there :) This ~g~UtomAfryus69 ~b~talking, creator of this menu.");
			}
		}
	}
	#endif
	
	if(ammo){
		if(IS_CHAR_SHOOTING(pPlayer)){
			uint weapon,ammo, max_ammo;
			GET_CURRENT_CHAR_WEAPON(pPlayer,&weapon);
			if(weapon != WEAPON_GRENADE && weapon != WEAPON_MOLOTOV){
				GET_MAX_AMMO_IN_CLIP(pPlayer,weapon,&ammo);
				GET_MAX_AMMO(pPlayer, weapon, &max_ammo);
				ENABLE_MAX_AMMO_CAP(false);
				SET_CHAR_AMMO(pPlayer, weapon, max_ammo);
				SET_AMMO_IN_CLIP(pPlayer,weapon,ammo);
			}
		}
	}
	else ENABLE_MAX_AMMO_CAP(true);

	if(objectgun){
		int wep;
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if((IS_CHAR_SHOOTING(pPlayer)) && (wep == WEAPON_PISTOL) && (!IS_CHAR_IN_ANY_CAR(pPlayer))){
			object_aim();
			object_shoot();
		}
	}
	
	if(cargun){
		int wep;
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if((IS_CHAR_SHOOTING(pPlayer)) && (wep == WEAPON_DEAGLE) && (!IS_CHAR_IN_ANY_CAR(pPlayer))){
			car_shoot();
		}
	}

	if(burstfire){
		int PlayerWep;
	//	int MaxAmmo,ClipMax;
		GET_CURRENT_CHAR_WEAPON(pPlayer, &PlayerWep);
		if(PlayerWep == WEAPON_RLAUNCHER){
			/**
			GET_MAX_AMMO_IN_CLIP(pPlayer, PlayerWep, &ClipMax);
			GET_MAX_AMMO(pPlayer, PlayerWep, &MaxAmmo);
			SET_PLAYER_FAST_RELOAD(GetPlayerIndex(), true);
			ENABLE_MAX_AMMO_CAP(false);
			SET_CHAR_AMMO(pPlayer, PlayerWep, MaxAmmo);
			SET_AMMO_IN_CLIP(pPlayer, PlayerWep, ClipMax);
			**/
			if(IS_BUTTON_PRESSED(0,BUTTON_L) && IS_BUTTON_PRESSED(0,BUTTON_R)){
				if(IS_CHAR_SHOOTING(pPlayer)) rapidrpg();
			}
		}
	}
	else if(!fastreload) SET_PLAYER_FAST_RELOAD(GetPlayerIndex(), false);
	
	if(lowerpveh){
		int tick,nvid;
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer))&& (!IS_CHAR_ON_ANY_BIKE(pPlayer)) && (IS_VEHICLE_ON_ALL_WHEELS(pveh)))
				APPLY_FORCE_TO_CAR(pveh,true,0.0,0,-0.2,0.0,0.0,0.0,true,true,true,true);
		}
	}
	
	
	if(pprotection){
		uint pos[4];
		GET_POSITION_OF_ANALOGUE_STICKS(0,&pos[0],&pos[1],&pos[2],&pos[3]);
		if(pos[0] == 0 && pos[1] == 0)
			FREEZE_CHAR_POSITION(pPlayer,true);
		else
			FREEZE_CHAR_POSITION(pPlayer,false);
	}
	
	if(lowerpveh){
		int tick,nvid;
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer))&& (!IS_CHAR_ON_ANY_BIKE(pPlayer)) && (IS_VEHICLE_ON_ALL_WHEELS(pveh)))
				APPLY_FORCE_TO_CAR(pveh,true,0.0,0,-0.2,0.0,0.0,0.0,true,true,true,true);
		}
	}
	
	if(collision){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer))){
				SET_CAR_COLLISION(pveh, false);
			}
			else{
				SET_CAR_COLLISION(pveh, false);
			}
		}
	}
	else{
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			SET_CAR_COLLISION(pveh, true);
		}
	}
	
	if(superrun){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_PRESSED(0,BUTTON_A)){
				APPLY_FORCE_TO_PED(pPlayer,true,0.0,100.0,0.0,0.0,0.0,0.0,true,true,true,true);
			}
		}
	}
	if(superjump){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_PRESSED(0,BUTTON_X)){
				APPLY_FORCE_TO_PED(pPlayer,true,0.0,0.0,20.0,0.0,0.0,0.0,true,true,true,true);
			}
		}	
	}

	if(chronicle){
		// float x,y,z;
		GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
		ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
		ADD_EXPLOSION(x,y,z + 5,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
		ADD_EXPLOSION(x + 5,y,z,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
		ADD_EXPLOSION(x - 5,y,z,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
		ADD_EXPLOSION(x,y + 5,z,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
		ADD_EXPLOSION(x,y - 5,z,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
	}
	
	if(lowerpveh){
		int tick,nvid;
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer))&& (!IS_CHAR_ON_ANY_BIKE(pPlayer)) && (IS_VEHICLE_ON_ALL_WHEELS(pveh)))
				APPLY_FORCE_TO_CAR(pveh,true,0.0,0,-0.3,0.0,0.0,0.0,true,true,true,true);
		}
	}
	
	if(hydrolics){
		if(IS_BUTTON_PRESSED(0,BUTTON_X)){
			if (IS_CHAR_IN_ANY_CAR(pPlayer)){
				if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer))){
				//	RESET_CAR_WHEELS(pveh, true);
					if(IS_VEHICLE_ON_ALL_WHEELS(pveh)){
						if(IS_CHAR_ON_ANY_BIKE(pPlayer)) APPLY_FORCE_TO_CAR(pveh, 0.0f, 0.0f, 0.0f, 500.0f , 0.0f,0.0f,0.0f, 0, 1, 1, 1 );
						else APPLY_FORCE_TO_CAR(pveh, 0.0f, 0.0f, 0.0f, 70.0f , 0.0f,0.0f,-70.0f, 0, 1, 1, 1 );		
					}
				}
			}
		}
	}
	
	if(chaos){
		float dX,dY,dZ;
		Ped gameped;
		GET_CHAR_COORDINATES(GetPlayerPed(),&dX, &dY, &dZ);
		ClosestCar = GET_CLOSEST_CAR(dX,dY,dZ, 15, false, 70);
		
		if( DOES_VEHICLE_EXIST(ClosestCar)){
			APPLY_FORCE_TO_CAR(ClosestCar, 3, 30.0, -20.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1);
			EXPLODE_CAR(ClosestCar, true, false);
		}	
		GET_CHAR_COORDINATES(GetPlayerPed(),&dX, &dY, &dZ);
		GET_CLOSEST_CHAR(dX,dY,dZ, 30.0F, 1 ,1, &gameped);
		if(DOES_CHAR_EXIST(gameped)){
			if(IS_CHAR_IN_ANY_CAR(gameped)){
				GET_CAR_CHAR_IS_USING(gameped, &pveh);	
				APPLY_FORCE_TO_CAR(ClosestCar, 3, 30.0, -20.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1);
				EXPLODE_CAR(ClosestCar, true, false);
			}
			else if(!IS_CHAR_IN_ANY_CAR(gameped)){
				if(!IS_CHAR_ON_FIRE(gameped)){
					START_CHAR_FIRE(gameped);
				}
			}
		}
	}
	
	if(ragdoll){
		if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_JUST_PRESSED(0,BUTTON_B)){
			if(!IS_PED_RAGDOLL(pPlayer)){
				SWITCH_PED_TO_RAGDOLL(pPlayer,20000,30000,false,false,false,false);
				SWITCH_PED_TO_ANIMATED(pPlayer,true);
				GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),true);
			}
			else{
				SWITCH_PED_TO_ANIMATED(pPlayer,false);
				GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),false);
			}
		}
	}
	
	if(vhelper){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			SET_CAR_CAN_BE_DAMAGED(pveh,false);
			SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,false);
			SET_CAN_BURST_CAR_TYRES(pveh,false);
			SET_HELI_BLADES_FULL_SPEED(pveh);
			SET_CAR_PROOFS(pveh, true, true, true, true, true);
		}
	}
	else{
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			SET_CAR_CAN_BE_DAMAGED(pveh,true);
			SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
			SET_CAN_BURST_CAR_TYRES(pveh,true);
			SET_CAR_PROOFS(pveh, false, false, false, false, false);
		}
	}
	
	if(carsonground){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			SET_CAR_ON_GROUND_PROPERLY(pveh);
		}
	}
	
	if(bikefly){
		float speed;
		if((IS_CHAR_ON_ANY_BIKE(pPlayer)) && IS_BUTTON_PRESSED(0,BUTTON_R)){
			GET_CAR_SPEED(pveh,&speed);
			SET_CAR_FORWARD_SPEED(pveh,(speed * 1.05));
		}
		if(IS_CHAR_ON_ANY_BIKE(pPlayer) && IS_BUTTON_PRESSED(0,BUTTON_L)){
			if (!IS_VEHICLE_ON_ALL_WHEELS(pveh)){
				GET_CAR_SPEED(pveh,&speed);
				SET_CAR_FORWARD_SPEED(pveh,(speed / 1.05));
			}
		}
	}
	
	if(nfs){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			float speed;
			if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer))){
				if(IS_BUTTON_PRESSED(0,BUTTON_R)){
					GET_CAR_SPEED(pveh,&speed);
					SET_CAR_FORWARD_SPEED(pveh,(speed * 1.02));
				}
				if(IS_BUTTON_JUST_PRESSED(0,BUTTON_L)){
					GET_CAR_SPEED(pveh,&speed);
					SET_CAR_FORWARD_SPEED(pveh,(speed / 6));
				}
			}
			else{
				if(IS_BUTTON_PRESSED(0,BUTTON_R)){
					GET_CAR_SPEED(pveh,&speed);
					SET_CAR_FORWARD_SPEED(pveh,(speed * 1.02));
				}
				if(IS_BUTTON_JUST_PRESSED(0,BUTTON_L)){
					GET_CAR_SPEED(pveh,&speed);
					SET_CAR_FORWARD_SPEED(pveh,(speed / 6));
				}
			}
		}
	}
	
	if(helistrike){
		if((IS_CHAR_IN_ANY_HELI(pPlayer)) && (IS_BUTTON_JUST_PRESSED(0,STICK_LEFT))) helibomb();
	}
	
	if(rainbowmenu){
		GENERATE_RANDOM_INT_IN_RANGE(0,255,&s_r);
		GENERATE_RANDOM_INT_IN_RANGE(0,255,&s_g);
		GENERATE_RANDOM_INT_IN_RANGE(0,255,&s_b);
	}
	
	if(rainbowcar){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			int color[4];
			GENERATE_RANDOM_INT_IN_RANGE(0,133,&color[0]);
			GENERATE_RANDOM_INT_IN_RANGE(0,133,&color[1]);
			GENERATE_RANDOM_INT_IN_RANGE(0,133,&color[2]);
			GENERATE_RANDOM_INT_IN_RANGE(0,133,&color[3]);
			CHANGE_CAR_COLOUR(pveh, color[0], color[1]);
			SET_EXTRA_CAR_COLOURS(pveh, color[2], color[3]);
		}
	}
	
	//misc
	if(chat_thingy){
		int i;
		float pos_y = 0.875;
		for(i = 16;i >= 0;i--){
			if(i < 0) continue;
			if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
			if(!NETWORK_IS_PLAYER_TALKING(i)) continue;
			if(NETWORK_IS_PLAYER_MUTED_BY_ME(i)) continue;
			GET_PLAYER_RGB_COLOUR(i,&r,&g,&b);
			set_up_draw(3,0.3,0.3,r,g,b,255);
			draw_text("STRING",0.70,pos_y,GET_PLAYER_NAME(i));
			pos_y -= 0.03;			
		}
	}
	
	if(group_loop){
		if(DOES_CHAR_EXIST(group_onlineped)){
			float mx,my,mz;
			GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
			GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
			GET_CHAR_COORDINATES(group_onlineped,&mx,&my,&mz);
			GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz,&dist);
			if((dist >= 10) && (DOES_GROUP_EXIST(Bgroup))){
				print_long("Victim to far away");
				REMOVE_GROUP(Bgroup);
			//	REMOVE_CHAR_FROM_GROUP(group_onlineped);
			//	REMOVE_CHAR_FROM_GROUP(pPlayer);
			//	SET_GROUP_FORMATION(Bgroup, 0);
				group_loop = false;
				return;
			}
			if(IS_CHAR_IN_ANY_CAR(group_onlineped)){
				GET_CAR_CHAR_IS_USING(group_onlineped,&pveh);
				GET_DRIVER_OF_CAR(pveh,&driver);
				if(pPlayer == driver){
					if(DOES_GROUP_EXIST(Bgroup)){
						REMOVE_GROUP(Bgroup);
						LOCK_CAR_DOORS(pveh,4);
					//	REMOVE_CHAR_FROM_GROUP(group_onlineped);
					//	REMOVE_CHAR_FROM_GROUP(pPlayer);
					//	SET_GROUP_FORMATION(Bgroup, 0);
						print_long("~b~Online Player sucessfully Kidnapped, locking doors.");
						group_loop = false;
					}
				}
			}
		}
	}
	
	if(GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT("player_menuiv") != 0 && show_menu)
		menu_shutdown();
	
	//garage
	if(in_paint && IS_CHAR_IN_ANY_CAR(pPlayer)){
		if(menu[item_select].value != menu[item_select].extra_val){
			uint color1,color2,spec1,spec2;
			GET_CAR_COLOURS(pveh,&color1,&color2);
			GET_EXTRA_CAR_COLOURS(pveh,&spec1,&spec2);
			if(item_select == 1)
				CHANGE_CAR_COLOUR(pveh,(menu[item_select].value - 1),color2);
			if(item_select == 2)
				CHANGE_CAR_COLOUR(pveh,color1,(menu[item_select].value - 1));
			if(item_select == 3)
				SET_EXTRA_CAR_COLOURS(pveh,(menu[item_select].value - 1),spec2);				
			if(item_select == 4)
				SET_EXTRA_CAR_COLOURS(pveh,spec1,(menu[item_select].value - 1));

			menu[item_select].extra_val = menu[item_select].value;
		}
	}
	return;
}

void better_grenade_loop(void){
	if(grenade_active){
		if(!IS_PED_HOLDING_AN_OBJECT(pPlayer)){
			uint tick;
			// float x,y,z;
			grenade_active = false;
			while(!HAS_OBJECT_COLLIDED_WITH_ANYTHING(tmp_object_loop)){
				tick++;
				if(tick > 2000) return;
				WAIT(0);
			}
			GET_OBJECT_COORDINATES(tmp_object_loop,&x,&y,&z);
			ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,20.0,true,false,0.7f);
			ADD_EXPLOSION(x,y,z + 1,EXPLOSION_SHIP_DESTROY,20.0,true,false,0.7f);
			DELETE_OBJECT(&tmp_object_loop);
			MARK_OBJECT_AS_NO_LONGER_NEEDED(&tmp_object_loop);
		}
	}
	if(IS_PED_HOLDING_AN_OBJECT(pPlayer)){
		tmp_model = GET_MODEL_PED_IS_HOLDING(pPlayer);
		if(tmp_model == 0x501811B6 || tmp_model == 0x48FA2738){//object to be new grenade
			grenade_active = true;
			tmp_object_loop = GET_OBJECT_PED_IS_HOLDING(pPlayer);
		}
		else grenade_active = false;
	}
}

void do_online_player_loop(void){
	int i;
	uint armor;
	// float x,y,z;
	Ped tmp;
	for(i = 0;i <= 16;i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)){
			players[i].mprotection = false;
			players[i].force = false;
			continue;
		}
		GET_PLAYER_CHAR(i,&tmp);
		if(DOES_CHAR_EXIST(tmp)){
			if(players[i].mprotection){
				GET_CHAR_ARMOUR(tmp,&armor);
				if(armor < 100){
					GIVE_WEAPON_TO_CHAR(tmp,WEAPON_ARMOUR,1,false);
					ADD_ARMOUR_TO_CHAR(tmp,100);
				}
				if(HAS_CHAR_GOT_WEAPON(tmp, WEAPON_ROCKET)){
					REMOVE_WEAPON_FROM_CHAR(tmp, WEAPON_ROCKET);
				}
				if(IS_CHAR_ON_FIRE(tmp)){
					EXTINGUISH_CHAR_FIRE(tmp);
				}
			}
			if(players[i].force){
				GET_CHAR_COORDINATES(tmp,&x,&y,&z);	  	
				ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,15.0,false,true,0.0);
			}
		}
	}
	return;
}

void check_xmc_loop(void){
	#ifndef PERSONAL
	Ped online_char;
	int i;
	if(!DOES_CHAR_EXIST(xmc_char)){
		for(i;i <= 16;i++){
			if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
			if(GET_PLAYER_ID() == i) continue;
			if(is_admin(i)){
				GET_PLAYER_CHAR(i,&online_char);
				online_char = xmc_char;
				xmc_in_game = true;
				return;
			}
		}
	}
	#endif
	return;
}