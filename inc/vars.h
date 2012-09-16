/**
	Settings, Keybinds, and Structure for core
	by: Herr Muskelprotze

**/
#define BUTTON_SELECT 0xD
#define BUTTON_START 0xC
#define BUTTON_X 0xE
#define BUTTON_Y 0xF
#define BUTTON_A 0x10
#define BUTTON_B 0x11
#define DPAD_UP 0x8
#define DPAD_DOWN 0x9
#define DPAD_LEFT 0xA
#define DPAD_RIGHT 0xB
#define BUTTON_L 0x5
#define BUTTON_R 0x7
#define BUTTON_LB 0x4
#define BUTTON_RB 0x6
#define STICK_LEFT 0x12
#define STICK_RIGHT 0x13

#define L3  0x12
#define L2  0x5
#define R2  0x7
#define L1  0x4
#define R1  0x6

#define pos_x 0.25
#define start_y 0.14


typedef struct _menu_struct{
	char* item_name;
	bool action;
	int type;
	int value;
	int extra_val;
	int maxval;
} menu_struct;

menu_struct menu[20];

typedef struct _online_players{
	//index
	char* gamertag;
	Ped ped;
	int id;
	bool connected;
	
	//id
	bool juggernaut;
	bool force;
	
} online_players;

typedef struct __data{
	int projectile;
	int actionid;
	
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

online_players players[18];


int item_count = 0,
	item_select = 1,
	menu_level = 0,
	player_count = 0,
	last_selected[5];

uint r,g,b,a,s_r,s_g,s_b;
Ped pPlayer,
	tmp_player_ped;
	
char* footer;

Object tmp_object_loop;
uint tmp_model;
bool grenade_active;
	
bool in_paint = false;	

bool show_menu = false,
	godmode = true,
	neverwanted = false,
	pprotection = false,
	superrun = false,
	superjump = false,
	forcefield = false,
	chaos = false,
	ammo = true,
	superguns = false,
	vhelper = true,
	flywalls = false,
	carsonground = false,
	nfs = false,
	chat_thingy = true,
	chat_thingy_use_color = true;
	drive_free = true,
	ragdoll = false;