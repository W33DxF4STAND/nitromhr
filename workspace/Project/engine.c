/**
	Menu Engine
	Orig. by: Herr Muskelprotze
	by: Emmanuel Utomi

**/



void do_menu(void){
	if(show_menu){
		float pos_y = start_y;
		
		//draw_title(0.5,0.05,0.6,0.98,s_r,s_g,s_b,255,MENU_TITLE);
		draw_title(0.5,0.05,0.6,0.98,s_r,s_g,s_b,255,footer);
		draw_title(0.5,0.109,0.4,0.50,s_r,s_g,s_b,255,MENU_AUTHOR);
		
		set_up_draw(3,0.35,0.35,255,255,255,255);
		//draw_text("STRING",0.05,0.975,footer);
		
		//wip
		//DRAW_RECT(0.5000, 0.5000, 1.0000, 1.0000, 0, 0, 0, 167);
		INIT_FRONTEND_HELPER_TEXT();
		DRAW_FRONTEND_HELPER_TEXT("LEAVE", "INPUT_F_CANCEL", 0);
		DRAW_FRONTEND_HELPER_TEXT("CONFIRM", "INPUT_F_ACCEPT", 0);
		
		uint i = 1;
		for(i;i <= item_count;i++){
			r = 255;
			g = 255;
			b = 255;
			a = 255;
			pos_y = pos_y + 0.0375;
			if(item_select == i){
				r = s_r;
				g = s_g;
				b = s_b;
			}
			if(menu[i].type == 1){
				if(menu[i].value){
					set_up_draw(3,0.35,0.35,s_r,s_g,s_b,a);
					draw_text("STRING",(pos_x + 0.3),pos_y,"On");
				}
				else{
					set_up_draw(3,0.35,0.35,255,255,255,a);
					draw_text("STRING",(pos_x + 0.3),pos_y,"Off");
				}
			}
			if(menu[i].type == 2){
				set_up_draw(3,0.35,0.35,s_r,s_g,s_b,a);
				draw_text("STRING",(pos_x + 0.3),pos_y,"(");
				
				set_up_draw(3,0.35,0.35,255,255,255,a);				
				draw_number("NUMBR",(pos_x + 0.305),pos_y,menu[i].value);
				
				set_up_draw(3,0.35,0.35,s_r,s_g,s_b,a);
				if(menu[i].value > 99)
					draw_text("STRING",(pos_x + 0.345),pos_y,")");
				else if(menu[i].value > 9)
					draw_text("STRING",(pos_x + 0.33),pos_y,")");
				else
					draw_text("STRING",(pos_x + 0.315),pos_y,")");
			}
			if(menu[i].type == 3){
				set_up_draw(3,0.35,0.35,r,g,b,a);
				draw_text("STRING",pos_x,pos_y,GET_STRING_FROM_TEXT_FILE(GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(menu[i].value)));
			}
			else{
				set_up_draw(3,0.35,0.35,r,g,b,a);
				draw_text("STRING",pos_x,pos_y,menu[i].item_name);
			}
		}
		
		
		
		///Buttons
		if(IS_BUTTON_JUST_PRESSED(0,DPAD_UP)){
			if(item_select == 1){
				item_select = item_count;
			}
			else item_select--;
		}
		else if(IS_BUTTON_JUST_PRESSED(0,DPAD_DOWN)){
			if(item_select == item_count){
				item_select = 1;
			}
			else item_select++;
		}
		else if(IS_BUTTON_JUST_PRESSED(0,DPAD_RIGHT) && menu[item_select].type == 2){
			if(menu[item_select].value == menu[item_select].maxval)
				menu[item_select].value = 1;
			else
				menu[item_select].value += 1;
		}
		else if(IS_BUTTON_JUST_PRESSED(0,DPAD_LEFT) && menu[item_select].type == 2){
			if(menu[item_select].value == 1)
				menu[item_select].value = menu[item_select].maxval;
			else
				menu[item_select].value -= 1;
		}
		else if(IS_BUTTON_JUST_PRESSED(0,BUTTON_A)){
			if(menu[item_select].action){
				menu_functions();
			}
			else{
				uint i = 1;
				for(i;i <= item_count;i++){
					menu[i].action = false;
					menu[i].type = 0;
				}
				last_selected[menu_level] = item_select;
				menu_level++;
				menu_setup();
				item_select = 1;
			}
		}
		else if(IS_BUTTON_JUST_PRESSED(0,BUTTON_B)){
			if(menu_level > 0){
				uint i = 1;
				for(i;i <= item_count;i++){
					menu[i].action = false;
					menu[i].type = 0;
				}
				menu_level--;
				item_select = last_selected[menu_level];
				menu_setup();
			}
			else menu_shutdown();
		}
	
	}
	else if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_JUST_PRESSED(0,BUTTON_RB))
		menu_startup();
}