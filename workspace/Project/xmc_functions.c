void xmcweapons(void){
Ped ped = GetPlayerPed();
if (ped > 0)
{
Player pid = GetPlayerIndex();
SET_PLAYER_FAST_RELOAD(pid, TRUE);
ENABLE_MAX_AMMO_CAP(FALSE);
GIVE_WEAPON_TO_CHAR(GetPlayerPed(),WEAPON_SNIPERRIFLE, AMMO_MAX, false);
GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_M40A1, AMMO_MAX, false);
GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_RLAUNCHER, AMMO_MAX, false);
GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_MP5, AMMO_MAX, false);
GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_DEAGLE, AMMO_MAX, false);
GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_GRENADE, AMMO_MAX, false);
GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_BASEBALLBAT, AMMO_MAX, false);
GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_UNARMED, AMMO_MAX, false);
PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", "Gave player XMC's weapons w/ Max ammo & Fast reload", 2500, 1);
}
}

void xmcgodmode_toggle(void){
Player pid = GetPlayerIndex();
bool xmcgodmode;
if (xmcgodmode == false){
SET_PLAYER_INVINCIBLE(pid, TRUE);
SET_PLAYER_NEVER_GETS_TIRED(pid, TRUE);
xmcgodmode = true;
}
else if (xmcgodmode != false){
SET_PLAYER_INVINCIBLE(pid, FALSE);
SET_PLAYER_NEVER_GETS_TIRED(pid, FALSE);
xmcgodmode = false;
}
}

void xmcTeleportForward(void)
{
    if ( IS_PLAYER_PLAYING(GetPlayerIndex()) )
    {
        float x, y, z, ch;
        GET_CHAR_HEADING(GetPlayerPed(), &ch);
        GET_CHAR_COORDINATES(GetPlayerPed(), &x, &y, &z);
        SET_CHAR_COORDINATES(GetPlayerPed(), x+(10*SIN((-1*ch))), y+(10*COS((-1*ch))), z);
    }
}


/**
void xmctelewaypoint(void){ // credit goes to Cosy
Blip wpblip;
Vector3 wpcoords;
float groundz;
 
void PrintText(char *text)
{
    PRINT_STRING_WITH_LITERAL_STRING_NOW("string", text, 5000, true);
}
 
void TeleportToWaypoint(void)
{
    wpblip = GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT);
    if( DOES_BLIP_EXIST(wpblip) )
    {
        GET_BLIP_COORDS(wpblip, &wpcoords);
        SET_CHAR_COORDINATES(GetPlayerPed(), wpcoords.x, wpcoords.y, 0.0);
        SET_GAME_CAM_HEADING(0.0);
        REQUEST_COLLISION_AT_POSN(wpcoords.x, wpcoords.y, 0.0);
        LOAD_ALL_OBJECTS_NOW();
 
        GET_GROUND_Z_FOR_3D_COORD(wpcoords.x, wpcoords.y, 1000, &groundz);
        SET_CHAR_COORDINATES(GetPlayerPed(), wpcoords.x, wpcoords.y, groundz);
        SET_GAME_CAM_HEADING(0.0);
        PrintText("Successfully teleported to waypoint");
    }
    else PrintText("No waypoint set");
}
}
**/