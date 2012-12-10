/**
	Settings, Keybinds, and Structure for core
	by: Herr Muskelprotze

**/

//Xbox 360 buttons
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

//PS3 Buttons
#define L3  0x12
#define L2  0x5
#define R2  0x7
#define L1  0x4
#define R1  0x6
#define START      0xC
#define SELECT     0xD
#define SQUARE     0xE
#define TRIANGLE   0xF
#define X          0x10
#define CIRCLE     0x11
#define STICK_L    0x12  //L3
#define STICK_R    0x13  //R3

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
	bool mprotection;
	bool force;
	
} online_players;

online_players players[18];

int item_count = 0,
	item_select = 1,
	menu_level = 0,
	player_count = 0,
	last_selected[5];

uint r,g,b,a,s_r,s_g,s_b;
Ped pPlayer, tmp_player_ped;

Object tmp_object_loop;
uint tmp_model, model;
uint object_launch = 0x3675A6C3;
uint car_launch = MODEL_SULTANRS;
uint rocket_ship_model = 0x19AF4794;
uint inferno_fire_model = 0xF3C45209;
Object Inferno_obj;
Ped driver, ClosestChar;
Vehicle ClosestCar, pveh;
Group Bgroup;
float x, y, z, dist;

Ped gameped[7];
Ped group_onlineped;
char* footer;

Object ObjectProjectile, InfernoRocket;
Vehicle CarProjectile;
Camera game_cam;
bool grenade_active;
	
bool in_paint = false;	
bool xmc_in_game = false;
Ped xmc_char;

int i;
int nvid;

bool xmc1 = false,
	xmc2 = false,
	xmc3 = false,
	xmc4 = false,
	xmc5 = false,
	xmc6 = false,
	xmc7 = false,
	xmc8 = false,
	xmc9 = false,
	xmc10 = false,
	xmc11 = false,
	xmc12 = false,
	xmc13 = false,
	xmc14 = false,
	xmc15 = false;


bool show_menu = false,
	godmode = true,
	group_loop = false,
	helistrike = false,
	bikefly = false,
	collision = false,
	inferno = false,
	neverwanted = false,
	objectgun = false,
	exp_cargun = false,
	del_cargun = true,
	cargun = false,
	invisible = false,
	burstfire = false,
	freezecar = false,
	rainbowcar = false,
	fastreload = true,
	lowerpveh = false,
	tazer = false,
	onfire = false,
	autoaim = false,
	pprotection = false,
	superrun = false,
	rainbowmenu = false,
	del_objgun = true,
	hydrolics = false,
	superjump = false,
	chronicle = false,
	chaos = false,
	ammo = true,
	vhelper = true,
	modderprotect = true,
	carsonground = false,
	nfs = false,
	chat_thingy = true,
	drive_free = true,
	ragdoll = false;
