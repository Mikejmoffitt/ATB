/*

ATB Sprite Class
This class is the graphic representation of the fighter. It stores bitmap data
for animations, as well as hitbox data, and can be told to play a certain 
animation, check for box collisions with another passed sprite, and be
instructed to be blitted somewhere on screen. 

*/
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

#include "Barge.h"
#include "dirDefs.h"
#include "spriteDefs.h"

class Sprite
{
public:

	// Responsible for drawing and handling inputs (in this case, just drawing)
	Barge* barge;

	std::string charName;
	Sprite(std::string name);
	~Sprite();

	// Blits current appropriate frame
	void blit(int x, int y, bool flip, bool tint);

	// Like above, but renders hitboxes
	void boxBlit(int x, int y, bool flip);

	// A single animation tick is activated here
	void animate();

	// Change the current animation sequence
	void playAnimation(int num);
	
	// Like above, but does not reset frame counter
	void switchAnimation(int num);

	// Switch animation and force reset counter even if it matches
	void forceAnimation(int num);

	// Resets whichever animation is playing to given frame (default 0)
	void resetAnimation(int frame);

	// Gets the length in frames of an animation
	unsigned int animationLength(int num);

	// Get number of frames of an animation (not duration!)
	unsigned int numFrames(int num);

	// Accessors for readability
	ALLEGRO_BITMAP* getFrame();

	// renders the sprite using the barge's drawing function

	// Check box collision
	// Pointer to other sprite, which local box, which box from the other

	// Basically, check if this sprite's box #(myBox) is overlapping the other
	// sprite's #(otherBox).
//	bool boxCol(Sprite* other, int myBox, int otherBox);

	// Accessors for hit box 
	int getBoxX(int box);
	int getBoxY(int box);
	int getBoxW(int box);
	int getBoxH(int box);

private:

	ALLEGRO_BITMAP* greenBox;
	ALLEGRO_BITMAP* redBox;
	ALLEGRO_BITMAP* blueBox;

	// Split a line into some elements
	std::vector<std::string> strTokenize(std::string s, char delim);
	std::vector<int> strToki(std::string s, char delim);
	

	// Which animation slots are actually used
	unsigned int numAnimations;

	// Animation state variables
	unsigned int animNum; // Which animation is being played
	unsigned int frameNum; // Incremented when frameCnt > length[anim][frame]
	unsigned int frameCnt; // Incremented every tick

	// Each animation property is accessde by array index for the given anim
	// For example to check whether animation 6 loops I would look at 
	// loop[6]
	int loop[ANIM_NUM];
	unsigned int animLength[ANIM_NUM];

	// THESE ARE ARRAYS OF VECTORS. NOT THE OTHER WAY AROUND.

	// For things with 2 level hierarchy, like animation frames, the format
	// is an array of vectors (keeping vector usage single-dimensional).
	// I would try to get frame[animnum][frame].
	std::vector<ALLEGRO_BITMAP*> frames[ANIM_NUM];
	std::vector<int> xOff[ANIM_NUM];
	std::vector<int> yOff[ANIM_NUM];
	std::vector<unsigned int> length[ANIM_NUM];

	// Hitboxes are tricky - we'll have accessors and setters for these - but
	// the format will be [box num][anim number][frame] where the last one is a
	// vector of integers.

	std::vector<int> boxX[NUM_BOXES][ANIM_NUM]; // X offset from top-left 
	std::vector<int> boxY[NUM_BOXES][ANIM_NUM]; // Y offset from top-left
	std::vector<int> boxW[NUM_BOXES][ANIM_NUM]; // Width
	std::vector<int> boxH[NUM_BOXES][ANIM_NUM]; // Height
};