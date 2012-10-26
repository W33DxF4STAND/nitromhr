
typedef struct __data{
        int projectile;
        //int actionid;
       
        float aimx;
        float aimy;
        float aimz;
       
        float playx;
        float playy;
        float playz;
       
        float velx;
        float vely;
        float velz;
       
        float dist;
} _data;
 
_data data[15];
 
void fire_projectile(void){
        int i = 0;
        for(i;i <= 10;i++){
			if(!DOES_OBJECT_EXIST(data[i].projectile)){
                        //data[i].actionid = weapon;
               
                        data[i].aimx = aim_tmp.x;
                        data[i].aimy = aim_tmp.y;
                        data[i].aimz = aim_tmp.z;
                               
                        data[i].playx = play_tmp.x;
                        data[i].playy = play_tmp.y;
                        data[i].playz = play_tmp.z;
                       
                        GET_DISTANCE_BETWEEN_COORDS_3D(aim_tmp.x,aim_tmp.y,aim_tmp.z,play_tmp.x,play_tmp.y,play_tmp.z,&data[i].dist);
                        #define SPEED 500
                        data[i].velx = SPEED * (aim_tmp.x - play_tmp.x) / data[i].dist;
                        data[i].vely = SPEED * (aim_tmp.y - play_tmp.y) / data[i].dist;
                        data[i].velz = SPEED * (aim_tmp.z - play_tmp.z) / data[i].dist;
                       
                        CREATE_OBJECT(MODEL_dildo,play_tmp.x,play_tmp.y,play_tmp.z,&data[i].projectile,true);
                        SET_OBJECT_RECORDS_COLLISIONS(data[i].projectile,true);
                        FREEZE_OBJECT_POSITION(data[i].projectile,false);
                        SET_OBJECT_VISIBLE(data[i].projectile,true);
                        SET_OBJECT_COLLISION(data[i].projectile,true);
                       
                        SET_OBJECT_INITIAL_VELOCITY(data[i].projectile,data[i].velx,data[i].vely,data[i].velz);
                       
                        return;
                }
        }
}
 
void projectile_action(void){
	int i = 0;
	for(i;i <= 10;i++){
		if(DOES_OBJECT_EXIST(data[i].projectile)){
			if(HAS_OBJECT_COLLIDED_WITH_ANYTHING(data[i].projectile) || data[i].dist > 150){
									//FREEZE_OBJECT_POSITION(data[i].projectile,true);
									//GET_OBJECT_COORDINATES(data[i].projectile,&data[i].aimx,&data[i].aimy,&data[i].aimz);
								   
									//ADD_EXPLOSION(data[i].aimx,data[i].aimy,data[i].aimz,EXPLOSION_MOLOTOV,5.0,true,false,0.0);
								   
				DELETE_OBJECT(&data[i].projectile);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&data[i].projectile);
			}
			else{
				GET_OBJECT_COORDINATES(data[i].projectile,&data[i].aimx,&data[i].aimy,&data[i].aimz);
												   
				GET_DISTANCE_BETWEEN_COORDS_3D(data[i].aimx,data[i].aimy,data[i].aimz,data[i].playx,data[i].playy,data[i].playz,&data[i].dist);
	 
				SET_OBJECT_INITIAL_VELOCITY(data[i].projectile,data[i].velx,data[i].vely,data[i].velz);
				SET_OBJECT_COLLISION(data[i].projectile,true);                 
						   
			}
		}
	}
}
/**
void rocket_aim(void){
		GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &wWeapon);
		if((wWeapon == WEAPON_PISTOL) && (IS_BUTTON_PRESSED(0,BUTTON_L))){
		
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
//				prjT = (3.0 * COS(gcrotX));       // adj side calculation to be used as a tangent below
//				prjX = gcX - (prjT * SIN(gcrotZ));// calculates how far to spawn the object from the game_cam on the X plane
//				prjY = gcY + (prjT * COS(gcrotZ));// calculates how far to spawn the object from the game_cam on the Y plane
//				prjZ = gcZ + (3.0 * SIN(gcrotX)); // calculates how far to spawn the object from the game_cam on the Z plane
//			}
//		}
//}
/**
void rocket_shoot(void){
	GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &wWeapon);
	if((wWeapon == WEAPON_PISTOL) && (IS_CHAR_SHOOTING(pPlayer))){
		
		REQUEST_MODEL(MODEL_dildo);
		while(!HAS_MODEL_LOADED(MODEL_dildo)){
			WAIT(0);
		}
		
		CREATE_OBJECT(MODEL_dildo, prjX, prjY, prjZ, &ObjectProjectile, 1);
		MARK_MODEL_AS_NO_LONGER_NEEDED(MODEL_dildo);
		if(DOES_OBJECT_EXIST(ObjectProjectile)){
			//SET_OBJECT_VISIBLE(ObjectProjectile, 0);
			SET_OBJECT_AS_STEALABLE(ObjectProjectile, 1);
			SET_OBJECT_ROTATION(ObjectProjectile, objrotX, 0.0, objrotZ);
			SET_OBJECT_RECORDS_COLLISIONS(ObjectProjectile, true);
			//SET_OBJECT_DYNAMIC(ObjectProjectile, 1);
			APPLY_FORCE_TO_OBJECT(ObjectProjectile, 1, 0.0, 90.0, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1);
			WAIT(100);
		}
		if (HAS_OBJECT_COLLIDED_WITH_ANYTHING(ObjectProjectile)){
			GET_OBJECT_COORDINATES(ObjectProjectile, &x,&y,&z);
			ADD_EXPLOSION(x,y,z,EXPLOSION_CAR,10.0f,true,false,0.7f);
			DELETE_OBJECT(&ObjectProjectile);
		}
	}
}

void dildo_aim(void){
		GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &wWeapon);
		if((wWeapon == WEAPON_DEAGLE) && (IS_BUTTON_PRESSED(0,BUTTON_L))){
		
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
//				prjT = (3.0 * COS(gcrotX));       // adj side calculation to be used as a tangent below
//				prjX = gcX - (prjT * SIN(gcrotZ));// calculates how far to spawn the object from the game_cam on the X plane
//				prjY = gcY + (prjT * COS(gcrotZ));// calculates how far to spawn the object from the game_cam on the Y plane
//				prjZ = gcZ + (3.0 * SIN(gcrotX)); // calculates how far to spawn the object from the game_cam on the Z plane
//			}
//		}
//}
/**
void dildo_shoot(void){
	GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &wWeapon);
	if((wWeapon == WEAPON_DEAGLE) && (IS_CHAR_SHOOTING(pPlayer))){
		
		REQUEST_MODEL(MODEL_dildo);
		while(!HAS_MODEL_LOADED(MODEL_dildo)){
			WAIT(0);
		}
		
		CREATE_OBJECT(MODEL_dildo, prjX, prjY, prjZ, &ObjectProjectile, 1);
		MARK_MODEL_AS_NO_LONGER_NEEDED(MODEL_dildo);
		if(DOES_OBJECT_EXIST(ObjectProjectile)){
			SET_OBJECT_AS_STEALABLE(ObjectProjectile, 1);
			SET_OBJECT_ROTATION(ObjectProjectile, objrotX, 0.0, objrotZ);
			SET_OBJECT_RECORDS_COLLISIONS(ObjectProjectile, true);
			//SET_OBJECT_DYNAMIC(ObjectProjectile, 1);
			APPLY_FORCE_TO_OBJECT(ObjectProjectile, 1, 0.0, 90.0, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1);
			WAIT(100);
		}
		if (HAS_OBJECT_COLLIDED_WITH_ANYTHING(ObjectProjectile)){
			//GET_OBJECT_COORDINATES(ObjectProjectile, &expx,&expy,&expz);
			WAIT(500);
			if(DOES_OBJECT_EXIST(ObjectProjectile)){
				DELETE_OBJECT(&ObjectProjectile);
			}
		}
	}
}
**/