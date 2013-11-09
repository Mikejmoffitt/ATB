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

	Player* example = new Player("chunex",false);

	Barge* barge = new Barge("c:/atb.ini");
	example->barge = barge;
	int timer = 0;
	ALLEGRO_SAMPLE* sample = al_load_sample("data/testmus.ogg");
	al_play_sample(sample,1,0,1,ALLEGRO_PLAYMODE_LOOP,0);
	while (timer < 1800)
	{
		barge->poll();
		al_set_target_bitmap(mainBuffer);
		al_clear_to_color(al_map_rgb(255 - timer,(timer * 2) % 255,timer%255));

		// Just shows the animation script does play properly...

		al_set_target_backbuffer(display);
		al_draw_scaled_bitmap(mainBuffer,
			0,0,baseX,baseY,0,0,windowX,windowY,0);
		al_flip_display();
		timer++;
	}
	al_stop_samples();
	al_destroy_sample(sample);
	delete(example);
	delete(barge);
	al_destroy_bitmap(mainBuffer);
	al_destroy_display(display);
	al_uninstall_system();
}