#pragma once

/* 

The barge class handles inputs and has a wrapper draw function. 

*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "bargeDefs.h"

class Barge
{
public:

	// Public facing inputs array
	int p1keys[8];
	int p2keys[8];

	Barge(std::string fname);
	~Barge();
	
	bool usingJoy1;
	bool usingJoy2;
	void poll();
	void setDefaultConfig();
	// Polls for keys

	void draw(ALLEGRO_BITMAP* chr, int xPos, int yPos, bool flip, bool tint);

private:

	ALLEGRO_CONFIG* gameCfg;
    ALLEGRO_JOYSTICK* joyPad1;
    ALLEGRO_JOYSTICK* joyPad2;
	ALLEGRO_JOYSTICK_STATE joyState;
	ALLEGRO_KEYBOARD_STATE keyState;

	// Input mappings for scancodes
	int kbKeys1[PLAYER_NUMBER_OF_KEYS]; 
	int joyKeys1[PLAYER_NUMBER_OF_KEYS];
	int kbKeys2[PLAYER_NUMBER_OF_KEYS-4]; 
	int joyKeys2[PLAYER_NUMBER_OF_KEYS-4];


};