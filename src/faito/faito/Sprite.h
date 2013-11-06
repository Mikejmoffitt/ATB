/*

ATB Sprite Class
This class is the representation of the fighter. It stores bitmap data
for animations, as well as hitbox data, and can be told to play a certain 
animation, check for box collisions with another passed sprite, and be
instructed to be blitted somewhere on screen. 

*/

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>
#include <sstream>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_primitives.h"

#define ANIM_NUM 160
#define ANIM_LENGTH 64
#define NUM_BOXES 5

#define CHAR_DIR "data/char/"
#define ANIM_DIR "/anim/"
#define ANIM_FORMAT ".png"

class Sprite
{
public:

	std::string charName
	Sprite(std::string name);

	// Each animation property is accessde by array index for the given anim
	// For example to check whether animation 6 loops I would look at 
	// loop[6]
	int loop[ANIM_NUM];

	// For things with double level hierarchy, like animation frames, the format
	// is an array of vectors (keeping vector usage single-dimensional).
	// I would try to get frame[which animation][which frame].
	std::vector<ALLEGRO_BITMAP*> frames[ANIM_NUM];
	std::vector<int> xOff[ANIM_NUM];
	std::vector<int> yOff[ANIM_NUM];
	std::vector<int> length[ANIM_NUM];

	// Hitboxes are tricky - we'll have accessors and setters for these - but
	// the format will be [box num][anim number][frame] where the last one is a
	// vector of integers.

	std::vector<int> boxX[NUM_BOXES][ANIM_NUM]; // X offset from top-left of sprite
	std::vector<int> boxY[NUM_BOXES][ANIM_NUM]; // Y offset
	std::vector<int> boxW[NUM_BOXES][ANIM_NUM]; // Width
	std::vector<int> boxH[NUM_BOXES][ANIM_NUM]; // Height

};


#endif