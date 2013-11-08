#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
#include "Sprite.h"

int main(int argc, char **argv)
{
	al_init();
	
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	ALLEGRO_DISPLAY* display = al_create_display(640,480);

	ALLEGRO_BITMAP* mainBuffer = al_create_bitmap(320,240);
	
	al_init_primitives_addon();
	al_init_image_addon();
	
	Sprite* example = new Sprite("example");
	int timer = 0;
	while (timer < 180)
	{
		al_set_target_bitmap(mainBuffer);
		al_clear_to_color(al_map_rgb(255 - timer,(timer * 2) % 255,timer%255));
		example->animate();

		// Just shows the animation script does play properly...
		al_draw_bitmap(example->getFrame(),64,64,0);

		al_set_target_backbuffer(display);
		al_draw_scaled_bitmap(mainBuffer,0,0,320,240,0,0,640,480,0);
		al_flip_display();
		al_wait_for_vsync();
		timer++;
	}
	delete(example);
	al_destroy_bitmap(mainBuffer);
	al_destroy_display(display);
	al_uninstall_system();
	system("pause");
}