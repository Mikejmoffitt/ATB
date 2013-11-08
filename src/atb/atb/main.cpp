#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
#include "Sprite.h"

const int baseX = 320;
const int baseY = 240;

const int windowX = 640;
const int windowY = 480;

int main(int argc, char **argv)
{
	al_init();
	
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	ALLEGRO_DISPLAY* display = al_create_display(windowX,windowY);

	ALLEGRO_BITMAP* mainBuffer = al_create_bitmap(baseX,baseY);
	
	al_init_primitives_addon();
	al_init_image_addon();
	
	Sprite* example = new Sprite("example");
	Sprite* example2 = new Sprite("chunex");
	int timer = 0;
	while (timer < 1800)
	{
		al_set_target_bitmap(mainBuffer);
		al_clear_to_color(al_map_rgb(255 - timer,(timer * 2) % 255,timer%255));
		example->animate();
		example2->animate();

		// Just shows the animation script does play properly...
		al_draw_bitmap(example2->getFrame(),-192 + (timer*2)%(320+192),32,0);
		al_draw_bitmap(example->getFrame(),64,48,0);
		al_draw_bitmap(example2->getFrame(),320 - (timer*2)%(320+192),64,ALLEGRO_FLIP_HORIZONTAL);

		al_set_target_backbuffer(display);
		al_draw_scaled_bitmap(mainBuffer,
			0,0,baseX,baseY,0,0,windowX,windowY,0);
		al_flip_display();
		timer++;
	}
	delete(example);
	delete(example2);
	al_destroy_bitmap(mainBuffer);
	al_destroy_display(display);
	al_uninstall_system();
}