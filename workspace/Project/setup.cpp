/**
	Menu setup config
	Orig. by: Herr Muskelprotze
	by: Emmanuel Utomi
	
**/

void add_item(char* item,bool act){
	item_count++;
	menu[item_count].item_name = item;
	menu[item_count].action = act;
}

void add_toggle(char* item,bool pointer){
	item_count++;
	menu[item_count].item_name = item;
	menu[item_count].action = true;
	menu[item_count].type = 1;
	menu[item_count].value = pointer;
}

void add_number(char* item,int maxvalue){
	item_count++;
	menu[item_count].item_name = item;
	menu[item_count].action = true;
	menu[item_count].type = 2;
	menu[item_count].value = 1;
	menu[item_count].maxval = maxvalue;
}

void add_gxt_hash(int model_hash){
	item_count++;
	menu[item_count].item_name = " ";
	menu[item_count].action = true;
	menu[item_count].type = 3;
	menu[item_count].value = model_hash;
}

void menu_setup(void){
	item_count = 0;
	footer = " ";
	if(menu_level == 0){
		footer = "Main Menu";
		add_item("Player Options",false);
		add_item("Vehicle Options",false);
		add_item("Weapon Options",false);
		add_item("Teleports",false);
		add_item("Others",false);
/**
Disable menu for now
		add_item("Addons",false);

**/
		return;
	}
	
	if(menu_level == 1){
		if(last_selected[0] == 1){
			footer = "Player Options";
			add_item("Online Players",false);
			add_item("Animations",false);
			add_item("Give Health & Armor",true);
			add_toggle("God Mode",godmode);
			add_toggle("Never Wanted",neverwanted);
			add_toggle("Smart protection",pprotection);
			add_toggle("Super Run",superrun);
			add_toggle("Super Jump",superjump);
			add_toggle("Chronicle",forcefield);
			add_toggle("Chaos mode",chaos);
			add_toggle("Invisibility",invisible);
			add_item("Set yourself on fire",true);
			return;
		}
		if(last_selected[0] == 2){
			footer = "Vehicle Options";
			add_item("Garage",false);
			add_toggle("Vehicle Helper",vhelper);
			add_item("Slingshot",true);
			add_toggle("Car Super Glue",carsonground);
			add_toggle("Super Speed",nfs);
			add_item("Kill Passengers",true);
			add_item("Fix & Wash Vehicle",true);
			add_item("Lock Doors",true);
			add_item("Delete Vehicle",true);
			add_item("Flip Vehicle",true);
			add_toggle("Hydrolics",hydrolics);
			add_item("Eject from vehicle",true);
			add_toggle("Flying Bikes",bikefly);
			return;
		}
		if(last_selected[0] == 3){
			footer = "Weapon Options";
			add_item("Weapon Selector",false);
			add_toggle("Unlimited Ammo",ammo);
			add_toggle("Fast Reload",fastreload);
			add_toggle("Rocket Glock",rocketpistol);
			return;
		}
		if(last_selected[0] == 4){
			footer = "Teleports";
			add_item("Waypoint",true);
			add_item("Airport Helipads",true);
			add_item("Hove Beach",true);
			add_item("Majestic Hotel",true);
			add_item("Skydive",true);
			add_item("Middle Park",true);
			add_item("Playboy X's Pad",true);
			add_item("Rotterdam Tower",true);
			add_item("Prison Cage",true);
			add_item("Crack House",true);
			add_item("Westminster Towers",true);
			add_item("Underground Parking Garage",true);
			add_item("Algonquin Safe House",true);
			add_item("Scrapyard",true);
			add_item("Construction Site",true);
			add_item("Subway",true);
			add_item("Sprunk Factory",true);
			add_item("10ft in front of you",true);
			return;
		}
		if(last_selected[0] == 5){
			footer = "Other stuff";
			add_item("Change Menu Colors",false);
			add_item("Throwable Objects",false);
			add_item("Air Strikes",false);
			add_toggle("Chat name popup",chat_thingy);
			add_toggle("Remove runway planes",drive_free);
			add_item("Start New Freemode",true);
			add_item("Return to Single Player",true);
			add_item("Get name of host",true);
			add_toggle("Modder Protection",modderprotect);
			add_item("Freeze Car",true);
			return;
		}		
	}
	if(menu_level == 2){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){
				footer = "Online Players";
				uint i = 0;
				player_count = 0;
				for(i;i <= 16;i++){
					players[player_count].connected = false;
					if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
					if(GET_PLAYER_ID() == i) continue;
					GET_PLAYER_CHAR(i,&tmp_player_ped);
					players[player_count].ped = tmp_player_ped;
					players[player_count].gamertag = GET_PLAYER_NAME(i);
					players[player_count].id = i;
					players[player_count].connected = true;
					player_count++;	
				}
				
				if(player_count > 0){
					add_item("All Players",false);
					for(i = 0;i <= player_count;i++){
						if(players[i].connected)
							add_item(players[i].gamertag,false);
					}
					return;
				}
				add_item("Game is empty",true);
				return;
			}
			if(last_selected[1] == 2){
				footer = "Animations";
				add_number("Taichi",2);
				add_number("Male Dance",4);
				add_number("Female Dance",3);
				add_item("Pole Dance",true);
				add_item("Stop Anim",true);
				add_toggle("Ragdoll",ragdoll);
				add_item("Handjob",true);
				return;
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				footer = "Garage";
				in_paint = false;
				add_item("Vehicle Spawner",false);
				add_item("Upgrades",false);
				add_item("Paint",false);
				return;
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				footer = "Weapon Spawner";
				add_number("All Weapons",3);
				add_item("TBOGT Weapons",false);
				add_item("Grenades",true);
				add_item("Glock 17",true);
				add_item("Desert Eagle",true);
				add_item("Pump Shotgun",true);
				add_item("Tactical Shotgun",true);
				add_item("Micro Uzi",true);
				add_item("MP5",true);
				add_item("AK-47",true);
				add_item("AR-15",true);
				add_item("M40-A5",true);
				add_item("Advance Sniper",true);
				add_item("Rocket Launcer",true);
				add_item("Baseball Bat",true);
				add_item("Pool Stick",true);
				return;
			}
		}
		if(last_selected[0] == 5){
			if(last_selected[1] == 1){
				footer = "Menu Colors";
				add_item("Purple",true);
				add_item("Red",true);
				add_item("Blue",true);
				add_item("Green",true);
				add_item("Pink",true);
				add_item("Gold",true);
				return;
			}
			if(last_selected[1] == 2){
				footer = "Throwable Objects";
				add_item("Big Ol' Pile of Dildos",true);
				add_item("Gumball Machine",true);
				add_item("Cubes",true);
				add_item("Throwing Knives",true);
				add_item("Grenades - that explode",true);
			}
			if(last_selected[1] == 3){
				footer = "Air Strikes";
				add_item("Airport Helipads",true);
				add_item("Airport Control Tower",true);
				add_item("Airport Parking Lot",true);
				add_item("Waypoint",true);
				return;
			}
		}
	}
	
	if(menu_level == 3){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
				#ifdef PRIVATE
					footer = "All Players";
					add_item("Give Weapons & Armor",true);
					add_item("Remove Weapons",true);
					add_item("Explode",true);
					add_item("Burn",true);
					add_item("Hippofy",true);
					add_item("Delete Vehicles",true);
					add_item("Teleport to You",true);
					add_item("Prison Derby",true);
					add_item("Freeze All Players",true);
					return;
				#else
				print("Private version only");
				return;
				#endif
				}
				else{
					int tmp = players[(last_selected[2] - 2)].id;
					footer = players[(last_selected[2] - 2)].gamertag;
					add_number("Give Weapons & Armor",3);
					add_item("Remove Weapons",true);
					add_toggle("Moddder Protection",players[tmp].mprotection);
					add_toggle("Chronicle",players[tmp].force);
					add_number("Teleport",4);
					add_item("Attach Self",true);
					add_item("Nuke",true);
					add_item("Taser",true);
					add_item("Delete Vehicle",true);
					add_item("Slingshot Vehicle",true);
					add_item("Immobilize Vehicle",true);
					add_item("Jail",true);
					add_item("Kick",true);
					add_item("Freeze",true);
					add_item("Burn",true);
					add_item("Hippofy",true);
					return;
				}
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					footer = "Vehicle Spawner";
					add_item("Sports",false);
					add_item("Vintige",false);
					add_item("Two Door",false);
					add_item("Four Door",false);
					add_item("Four Door (2)",false);
					add_item("Junkers",false);
					add_item("SUVs, Vans & Trucks",false);
					add_item("Commercial",false);
					add_item("Commercial (2)",false);
					add_item("Emergency",false);
					add_item("Service",false);
					add_item("Bikes",false);
					add_item("Boats",false);
					add_item("Helicopters",false);
					return;
				}
				if(last_selected[2] == 2){
					bool enabled;
					uint i;
					Vehicle pveh;
					char* upgrade[10];
					
					upgrade[0] = "Upgrade 1";
					upgrade[1] = "Upgrade 2";
					upgrade[2] = "Upgrade 3";
					upgrade[3] = "Upgrade 4";
					upgrade[4] = "Upgrade 5";
					upgrade[5] = "Upgrade 6";
					upgrade[6] = "Upgrade 7";
					upgrade[7] = "Upgrade 8";
					upgrade[8] = "Upgrade 9";
					upgrade[9] = "Upgrade 10";
					
					footer = "Upgrades";
					for(i = 0;i <= 9;i++){
						enabled = false;
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						if(DOES_VEHICLE_EXIST(pveh))
							enabled = IS_VEHICLE_EXTRA_TURNED_ON(pveh,(i + 1));
						add_toggle(upgrade[i],enabled);
					}
					return;
				}
				if(last_selected[2] == 3){
					uint color1,color2,spec1,spec2;
					Vehicle pveh;
					footer = "Paint";
					add_number("Color 1",134);
					add_number("Color 2",134);
					add_number("Color 3",134);
					add_number("Color 4",134);
					
					in_paint = true;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					if(DOES_VEHICLE_EXIST(pveh)){
						GET_CAR_COLOURS(pveh,&color1,&color2);
						GET_EXTRA_CAR_COLOURS(pveh,&spec1,&spec2);
						menu[1].value = color1 + 1;
						menu[2].value = color2 + 1;
						menu[3].value = spec1 + 1;
						menu[4].value = spec2 + 1;
						
						menu[1].extra_val = menu[1].value;
						menu[2].extra_val = menu[2].value;
						menu[3].extra_val = menu[3].value;
						menu[4].extra_val = menu[4].value;
					}
					return;
				}
				if(last_selected[2] == 4){
					footer = "Underglow";
				}
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2){
					footer = "TBOGT Weapons";
					if(GET_CURRENT_EPISODE() == 2){
						add_item(".44 Pistol",true);
						add_item("Explosive AA12",true);
						add_item("AA12",true);
						add_item("P-90",true);
						add_item("Uzi",true);
						add_item("M249",true);
						add_item("Explosive Sniper",true);
						add_item("Grenade Launcher",true);
						add_item("Sticky Bombs",true);
						return;
					}
					else{
						add_item("You must be on TBOGT to use this",true);
						return;
					}
				}
			}
		}
	}
	if(menu_level == 4){
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					uint episode = GET_CURRENT_EPISODE();
					if(last_selected[3] == 1){
						footer = "Sports";
						add_gxt_hash(MODEL_BANSHEE);
						add_gxt_hash(MODEL_COMET);
						add_gxt_hash(MODEL_COQUETTE);
						add_gxt_hash(MODEL_FELTZER);
						add_gxt_hash(MODEL_INFERNUS);
						add_gxt_hash(MODEL_SULTAN);
						add_gxt_hash(MODEL_SULTANRS);
						add_gxt_hash(MODEL_SUPERGT);
						add_gxt_hash(MODEL_TURISMO);
						if(episode == 2){
							add_gxt_hash(MODEL_BUFFALO);
							add_gxt_hash(MODEL_BULLET);
							add_gxt_hash(MODEL_F620);
						}
						return;
					}
					if(last_selected[3] == 2){
						footer = "Vintige";
						add_gxt_hash(MODEL_BUCCANEER);
						add_gxt_hash(MODEL_DUKES);
						add_gxt_hash(MODEL_FACTION);
						add_gxt_hash(MODEL_MANANA);
						add_gxt_hash(MODEL_PEYOTE);
						add_gxt_hash(MODEL_RUINER);
						add_gxt_hash(MODEL_SABRE);
						add_gxt_hash(MODEL_SABREGT);
						add_gxt_hash(MODEL_STALION);
						add_gxt_hash(MODEL_VIGERO);
						add_gxt_hash(MODEL_VIRGO);
						add_gxt_hash(MODEL_VOODOO);
						if(episode == 2)
							add_gxt_hash(MODEL_TAMPA);
						return;
					}
					if(last_selected[3] == 3){
						footer = "Two Doors";
						add_gxt_hash(MODEL_BLISTA);
						add_gxt_hash(MODEL_FORTUNE);
						add_gxt_hash(MODEL_FUTO);
						add_gxt_hash(MODEL_SENTINEL);
						add_gxt_hash(MODEL_URANUS);
						if(episode == 2)
							add_gxt_hash(MODEL_SUPERD);
						return;
					}
					if(last_selected[3] == 4){
						footer = "Four Doors";
						add_gxt_hash(MODEL_ADMIRAL);
						add_gxt_hash(MODEL_CHAVOS);
						add_gxt_hash(MODEL_COGNOSCENTI);
						add_gxt_hash(MODEL_DF8);
						add_gxt_hash(MODEL_DILETTANTE);
						add_gxt_hash(MODEL_EMPEROR);
						add_gxt_hash(MODEL_ESPERANTO);
						add_gxt_hash(MODEL_FEROCI);
						add_gxt_hash(MODEL_HAKUMAI);
						add_gxt_hash(MODEL_INGOT);
						add_gxt_hash(MODEL_INTRUDER);
						add_gxt_hash(MODEL_LOKUS);
						add_gxt_hash(MODEL_MARBELLA);
						add_gxt_hash(MODEL_MERIT);
						return;
					}
					if(last_selected[3] == 5){
						footer = "Four Doors (2)";
						add_gxt_hash(MODEL_ORACLE);
						add_gxt_hash(MODEL_PINNACLE);
						add_gxt_hash(MODEL_PMP600);
						add_gxt_hash(MODEL_PREMIER);
						add_gxt_hash(MODEL_PRES);
						add_gxt_hash(MODEL_PRIMO);
						add_gxt_hash(MODEL_ROM);
						add_gxt_hash(MODEL_SCHAFTER);
						add_gxt_hash(MODEL_SOLAIR);
						add_gxt_hash(MODEL_STRATUM);
						add_gxt_hash(MODEL_VINCENT);
						add_gxt_hash(MODEL_WASHINGTON);
						add_gxt_hash(MODEL_WILLARD);
						if(episode == 2){
							add_gxt_hash(MODEL_SERRANO);
							add_gxt_hash(MODEL_SCHAFTER2);
						}
						return;
					}
					if(last_selected[3] == 6){
						footer = "Junkers";
						add_gxt_hash(MODEL_EMPEROR2);
						add_gxt_hash(MODEL_SABRE2);
						add_gxt_hash(MODEL_VIGERO2);
						return;
					}
					if(last_selected[3] == 7){
						footer = "SUVs, Vans & Trucks";
						add_gxt_hash(MODEL_BOBCAT);
						add_gxt_hash(MODEL_CAVALCADE);
						add_gxt_hash(MODEL_FXT);
						add_gxt_hash(MODEL_E109);
						add_gxt_hash(MODEL_HABANERO);
						add_gxt_hash(MODEL_HUNTLEY);
						add_gxt_hash(MODEL_LANDSTALKER);
						add_gxt_hash(MODEL_MINIVAN);
						add_gxt_hash(MODEL_MOONBEAM);
						add_gxt_hash(MODEL_PATRIOT);
						add_gxt_hash(MODEL_PERENNIAL);
						add_gxt_hash(MODEL_RANCHER);
						add_gxt_hash(MODEL_REBLA);
						if(episode == 2)
							add_gxt_hash(MODEL_CAVALCADE2);
						return;
					}
					if(last_selected[3] == 8){
						footer = "Commercial";
						add_gxt_hash(MODEL_AIRTUG);
						add_gxt_hash(MODEL_BENSON);
						add_gxt_hash(MODEL_BIFF);
						add_gxt_hash(MODEL_BOXVILLE);
						add_gxt_hash(MODEL_BURRITO);
						add_gxt_hash(MODEL_FLATBED);
						add_gxt_hash(MODEL_FEROCI2);
						add_gxt_hash(MODEL_PERENNIAL2);
						add_gxt_hash(MODEL_FORKLIFT);
						add_gxt_hash(MODEL_BURRITO2);
						add_gxt_hash(MODEL_MRTASTY);
						add_gxt_hash(MODEL_MULE);
						add_gxt_hash(MODEL_PACKER);
						add_gxt_hash(MODEL_PHANTOM);	
						return;
					}
					if(last_selected[3] == 9){
						footer = "Commercial (2)";
						add_gxt_hash(MODEL_PONY);
						add_gxt_hash(MODEL_RIPLEY);
						add_gxt_hash(MODEL_STOCKADE);
						add_gxt_hash(MODEL_SPEEDO);
						add_gxt_hash(MODEL_STEED);
						add_gxt_hash(MODEL_YANKEE);
						if(episode == 2)
							add_gxt_hash(MODEL_CADDY);
						return;
					}
					if(last_selected[3] == 10){
						footer = "Emergency";
						add_gxt_hash(MODEL_AMBULANCE);
						add_gxt_hash(MODEL_NSTOCKADE);
						add_gxt_hash(MODEL_FBI);
						add_gxt_hash(MODEL_FIRETRUK);
						add_gxt_hash(MODEL_NOOSE);
						add_gxt_hash(MODEL_POLPATRIOT);
						add_gxt_hash(MODEL_POLICE);
						add_gxt_hash(MODEL_POLICE2);
						add_gxt_hash(MODEL_PSTOCKADE);
						if(episode == 2){
							add_gxt_hash(MODEL_APC);
							add_gxt_hash(MODEL_POLICE3);
							add_gxt_hash(MODEL_POLICEW);
							add_gxt_hash(MODEL_POLICE4);
							add_gxt_hash(MODEL_POLICEB);						
						}
						return;
					}
					if(last_selected[3] == 11){
						footer = "Service";
						add_gxt_hash(MODEL_BUS);
						add_gxt_hash(MODEL_CABBY);
						add_gxt_hash(MODEL_ROMERO);
						add_gxt_hash(MODEL_TAXI);
						add_gxt_hash(MODEL_TAXI2);
						add_gxt_hash(MODEL_TRASH);
						add_gxt_hash(MODEL_STRETCH);
						if(episode == 2){
							add_gxt_hash(MODEL_LIMO2);
						}
						return;
					}
					if(last_selected[3] == 12){
						footer = "Bikes";
						add_gxt_hash(MODEL_FAGGIO);
						add_gxt_hash(MODEL_BOBBER);
						add_gxt_hash(MODEL_HELLFURY);
						add_gxt_hash(MODEL_NRG900);
						add_gxt_hash(MODEL_PCJ);
						add_gxt_hash(MODEL_SANCHEZ);
						add_gxt_hash(MODEL_ZOMBIEB);
						if(episode == 2){
							add_gxt_hash(MODEL_HEXER);
							add_gxt_hash(MODEL_FAGGIO2);
							add_gxt_hash(MODEL_BATI2);
							add_gxt_hash(MODEL_VADER);
							add_gxt_hash(MODEL_AKUMA);
							add_gxt_hash(MODEL_HAKUCHOU);
							add_gxt_hash(MODEL_DOUBLE);
						}
						return;
					}
					if(last_selected[3] == 13){
						footer = "Boats";
						add_gxt_hash(MODEL_DINGHY);
						add_gxt_hash(MODEL_JETMAX);
						add_gxt_hash(MODEL_MARQUIS);
						add_gxt_hash(MODEL_PREDATOR);
						add_gxt_hash(MODEL_REEFER);
						add_gxt_hash(MODEL_SQUALO);
						add_gxt_hash(MODEL_TROPIC);
						add_gxt_hash(MODEL_TUGA);
						if(episode == 2){
							add_gxt_hash(MODEL_SMUGGLER);
							add_gxt_hash(MODEL_FLOATER);
							add_gxt_hash(MODEL_BLADE);
						}
						return;
					}
					if(last_selected[3] == 14){
						footer = "Helicopters";
						add_gxt_hash(MODEL_ANNIHILATOR);
						add_gxt_hash(MODEL_TOURMAV);
						add_gxt_hash(MODEL_MAVERICK);
						add_gxt_hash(MODEL_POLMAV);
						if(episode == 2){
							add_gxt_hash(MODEL_BUZZARD);
							add_gxt_hash(MODEL_SWIFT);
							add_gxt_hash(MODEL_SKYLIFT);
						}
						return;
					}
				}
			}	
		}
	}
}

void reset_menu(void){
	uint i = 1;
	for(i;i <= item_count;i++){
		menu[i].action = false;
		menu[i].type = 0;
	}
	menu_setup();
}