#include <stdio.h>
#include <zlib.h>
#include <physfs.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include "Sprite.h"
#include "Barge.h"
#include "Player.h"

const int baseX = 320;
const int baseY = 240;

const int windowX = 640;
const int windowY = 480;

int main(int argc, char **argv)
{
	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(16);
	
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	ALLEGRO_DISPLAY* display = al_create_display(windowX,windowY);

	ALLEGRO_BITMAP* mainBuffer = al_create_bitmap(baseX,baseY);

	al_init_primitives_addon();
	al_init_image_addon();
	
	//Setup Background bitmap
	std::stringstream sb;
	sb << STAGE_DIR << "characterselect" << ANIM_FORMAT;
	ALLEGRO_BITMAP* background = al_load_bitmap(sb.str().c_str());

	//To be made during character select
	Player* Player1 = NULL;
	Player* Player2 = NULL;
	int rounds1= 0,rounds2 = 0;
	int numRounds = 2;//How many rounds does a player need to win the match

	Barge* barge = new Barge("c:/atb.ini");
	int timer = 0;
	//Character Select song
	ALLEGRO_SAMPLE* sample = al_load_sample("data/testmus.ogg");
	al_play_sample(sample,1,0,1,ALLEGRO_PLAYMODE_LOOP,0);

	//Character Select Loop
	while ((Player1 == NULL || Player2 == NULL) && timer<200)
	{
		barge->poll();
		al_set_target_bitmap(mainBuffer);
		barge->draw(background, 0,0,false,false);

		al_set_target_backbuffer(display);
		al_draw_scaled_bitmap(mainBuffer,
			0,0,baseX,baseY,0,0,windowX,windowY,0);
		al_flip_display();
		timer++;
		//Needs to be handled by actual character select eventually
		Player1 = new Player("chunex",false); //Pretend Players selected a character
		Player2 = new Player("chunex",true);
		Player1->barge = barge;
		Player2->barge = barge;
	}
	sb.str("");
	sb << STAGE_DIR << "stage" << ANIM_FORMAT;
	background = al_load_bitmap(sb.str().c_str());

	//Play Stage Song
	al_stop_samples();
	sample = al_load_sample("data/testmus.ogg");
	al_play_sample(sample,1,0,1,ALLEGRO_PLAYMODE_LOOP,0);
	//Game Start loop
	while(rounds1 < numRounds && rounds2 < numRounds)
	{
		barge->poll();
		al_set_target_bitmap(mainBuffer);
		barge->draw(background, 0,0,false,false);

		Player1->handleInputs();
		Player1->doPhysics();
		Player1->animate();
		Player1->blit(0);
		Player2->handleInputs();
		Player2->doPhysics();
		Player2->animate();
		Player2->blit(0);
		
		al_set_target_backbuffer(display);
		al_draw_scaled_bitmap(mainBuffer,
			0,0,baseX,baseY,0,0,windowX,windowY,0);
		al_flip_display();

	}

	al_stop_samples();
	al_destroy_sample(sample);
	delete(Player1);
	delete(Player2);
	delete(barge);
	al_destroy_bitmap(mainBuffer);
	al_destroy_display(display);
	al_destroy_bitmap(background);
	al_uninstall_system();
}