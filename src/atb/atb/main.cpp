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

const int numChars = 2;
const int portraitSz = 32;


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
	
	//List of characters to choose from.  Optimize later
	std::string characters[numChars]; 
	characters[0] = "cfort";
	characters[1] = "drew";
	
	ALLEGRO_BITMAP* charBMs[numChars];

	std::stringstream sa;
	sa << STAGE_DIR << "p1sel" << ANIM_FORMAT;
	ALLEGRO_BITMAP* p1Arrow = al_load_bitmap(sa.str().c_str());
	sa.str("");
	sa << STAGE_DIR << "p2sel" << ANIM_FORMAT;
	ALLEGRO_BITMAP* p2Arrow = al_load_bitmap(sa.str().c_str());

	//std::stringstream sc;
	for(int i = 0; i < numChars; i++)
	{
		//sc << CHAR_DIR << characters[i] << CHAR_PORT << ANIM_FORMAT; 
		std::string cImg = CHAR_DIR + characters[i] + CHAR_PORT + ANIM_FORMAT;
		ALLEGRO_BITMAP* c = al_load_bitmap(cImg.c_str());
		charBMs[i] = c;
	}

	Barge* barge = new Barge("c:/atb.ini");
	int timer = 0;
	//Character Select song
	ALLEGRO_SAMPLE* sample = al_load_sample("data/testmus.ogg");
	
	int p1SelChar = 0;
	int p2SelChar = 0;

	//Character Select Loop
	while ((Player1 == NULL || Player2 == NULL))
	{
		barge->poll();
		al_set_target_bitmap(mainBuffer);
		barge->draw(background, 0,0,false,false);

		
		// Calculate equally distanced locations for characters to display
		int initXLoc = (baseX/(numChars*2)) - (portraitSz/2);
		int xLocDist = (baseX/numChars) + (portraitSz/2);
		int yLoc = (baseY/numChars) - (portraitSz/2);

		for(int i = 0; i < numChars; i++)
		{
			int xLoc = initXLoc + xLocDist * i;
			if(i == p1SelChar)
			{
				//std::cout << "drawing p1 on " << i << std::endl;
				barge->draw(p1Arrow, xLoc, yLoc-portraitSz, false, false);
			}
			if(i == p2SelChar)
			{
				barge->draw(p2Arrow, xLoc, yLoc+portraitSz, false, false);
			}
				barge->draw(charBMs[i], xLoc, yLoc, false, false);
		}
		
		typedef int Keys[8];
		Keys* p1Input = &(barge->p1keys);
		Keys* p2Input = &(barge->p2keys);
		if(Player1 == NULL)
		{
			if((*p1Input)[LEFTKEY] == 1)
			{
				if(p1SelChar == 0)
				{
					p1SelChar = numChars-1;
				}
				else
				{
					p1SelChar--;
				}
			}
			if((*p1Input)[RIGHTKEY] == 1)
			{
				if(p1SelChar == numChars-1)
				{
					p1SelChar = 0;
				}
				else
				{
					p1SelChar++;
				}
			}
			if((*p1Input)[AKEY] == 1)
			{
				Player1 = new Player(characters[0],false);
			}
		}
		if(Player2 == NULL)
		{
			if((*p2Input)[LEFTKEY] == 1)
			{
				if(p2SelChar == 0)
				{
					p2SelChar = numChars-1;
				}
				else
				{
					p2SelChar--;
				}
			}
			if((*p2Input)[RIGHTKEY] == 1)
			{
				if(p2SelChar == numChars-1)
				{
					p2SelChar = 0;
				}
				else
				{
					p2SelChar++;
				}
			}
			if((*p2Input)[AKEY] == 1)
			{
				Player2 = new Player(characters[0],true);
			}
		}

		al_set_target_backbuffer(display);
		al_draw_scaled_bitmap(mainBuffer,
			0,0,baseX,baseY,0,0,windowX,windowY,0);
		al_flip_display();
	}
	Player1->other = Player2;
	Player2->other = Player1;
	Player1->barge = barge;
	Player2->barge = barge;
	
	
	sb.str("");
	sb << STAGE_DIR << "stage" << ANIM_FORMAT;
	background = al_load_bitmap(sb.str().c_str());

	//Play Stage Song
	al_play_sample(sample,1,0,1,ALLEGRO_PLAYMODE_LOOP,0);
	//Game Start loop
	int scroll = 0;
	while(rounds1 < numRounds && rounds2 < numRounds)
	{
		barge->poll();
		al_set_target_bitmap(mainBuffer);
		barge->draw(background, scroll * -1,0,false,false);
		scroll = (Player1->xPos + Player2->xPos)/2 - (SCREENWIDTH/2);
		if (scroll < 0)
		{
			scroll = 0;
		}
		if (scroll > 320)
		{
			scroll = 320;
		}
		if (!Player1->freezeGame() && !Player2->freezeGame())
		{
			Player1->handleInputs();
			Player2->handleInputs();
			Player1->doPhysics();
			Player2->doPhysics();
			Player1->attackVectors();
			Player2->attackVectors();
			Player1->getHit();
			Player2->getHit();
			Player2->animate();
			Player1->animate();
		}
		Player2->blit(scroll);
		Player1->blit(scroll);
		//Player2->boxBlit(scroll);
		//Player1->boxBlit(scroll);

		
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
	for(int i = 0; i < numChars; i++)
	{
		al_destroy_bitmap(charBMs[i]);
	}
	al_destroy_bitmap(p1Arrow);
	al_destroy_bitmap(p2Arrow);
	al_uninstall_system();
}