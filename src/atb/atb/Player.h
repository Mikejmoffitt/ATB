#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

#include "Sprite.h"
#include "Barge.h"

#define GROUND_POS 200
#define MIN_X 640+72
#define MAX_X 320-72

class Player
{
public:
	Sprite* sprite;
	Barge* sprite;
	Player* other;

	std::string name;
	
	// Check if other has the attacking hitbox (4) overlapping our 
	// player's vuln boxes (1-3)
	void getHit();

	// Move the player left / right
	void handleInputs();

	// Whether or not to pause the action (and decrease hitfreeze)
	bool freezeGame();

	// Check for command inputs
	void checkCommands();

	// Check for charge inputs
	void checkCharge();

	// Detected valid input buffers when > 0
	int qcf;
	int qcb;
	int fdp;
	int bdp;
	int fcharge;
	int bcharge;

private:

	bool isPlayer2;

	// Stored player properties
	double fwdSpeed;
	double backSpeed;
	double fwdJumpSpeed;
	double backJumpSpeed;
	double gravity;

	// Game state variables
	int health;

	
	int hitfreeze; // pause all action
	bool direction; // Right == true
	bool crouching;
	bool grounded;
	double xPos;
	double yPos;
	double slideX; // Sliding from doing an attack on the ground
	double vecX;
	double vecY;

	// Whether a normal is in progress
	int doingNormal;

	// Whether a special is in progress
	int doingSpecial;

	// If >0, player is preparing to jump. Player jumps when it == 1.
	int jumpDelay;

	// Whether to land delay (set upon jumping, decreases when grounded==true)
	int landDelay;

	// Whether landDelay can be canceled into a block
	bool landBlockCancel;

	// Frames where character is reeling from being hit and can't input
	int hitStun;

	// Frams where character is blocking and can't input
	int blockStun;

	// Frames where character is on the ground, going to stand up
	int standDelay;

	// Whether player is going to be knocked down upon landing
	bool knockDown;

	// Amount to slide back from hits, etc.
	double slideX;
};