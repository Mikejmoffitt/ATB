/*

ATB Sprite Class
This class is the graphic representation of the fighter. It stores bitmap data
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

#define BOX_BODY 0
#define BOX_VULN0 1
#define BOX_VULN1 2
#define BOX_VULN2 3
#define BOX_ATTACK 4

class Sprite
{
public:

	std::string charName;
	Sprite(std::string name);
	~Sprite();

	// Blits current appropriate frame
	void blit(int x, int y);

	// Like above, but renders hitboxes
	void boxBlit(int x, int y, int box);

	// Gets the frame for the current animation (for rendering)
	ALLEGRO_BITMAP* getFrame();

	// A single animation tick is activated here
	void animate();

	// Change the current animation sequence
	void playAnimation(int num);
	
	// Like above, but does not reset frame counter
	void switchAnimation(int num);

	// Switch animation and force reset counter even if it matches
	void forceAnimation(int num);

	// Resets whichever animation is playing to given frame (default 0)
	void resetAnimation(int frame = 0);

	// Gets the length in frames of an animation
	unsigned int animationLength(int num);

	// Get number of frames of an animation (not duration!)
	unsigned int numFrames(int num);

private:

	// Animation state variables
	int animNum; // Which animation is being played
	int frameNum; // Incremented when frameCnt > length[anim][frame]
	int frameCnt; // Incremented every tick

	// Each animation property is accessde by array index for the given anim
	// For example to check whether animation 6 loops I would look at 
	// loop[6]
	int loop[ANIM_NUM];

	// For things with 2 level hierarchy, like animation frames, the format
	// is an array of vectors (keeping vector usage single-dimensional).
	// I would try to get frame[which animation][which frame].
	std::vector<ALLEGRO_BITMAP*> frames[ANIM_NUM];
	std::vector<int> xOff[ANIM_NUM];
	std::vector<int> yOff[ANIM_NUM];
	std::vector<int> length[ANIM_NUM];

	// Hitboxes are tricky - we'll have accessors and setters for these - but
	// the format will be [box num][anim number][frame] where the last one is a
	// vector of integers.

	std::vector<int> boxX[NUM_BOXES][ANIM_NUM]; // X offset from top-left 
	std::vector<int> boxY[NUM_BOXES][ANIM_NUM]; // Y offset from top-left
	std::vector<int> boxW[NUM_BOXES][ANIM_NUM]; // Width
	std::vector<int> boxH[NUM_BOXES][ANIM_NUM]; // Height
};


#endif