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

#define UPKEY 0
#define DOWNKEY 1
#define LEFTKEY 2
#define RIGHTKEY 3
#define LPKEY 4
#define HPKEY 5
#define LKKEY 6
#define HKKEY 7
#define STARTKEY 8
#define SELKEY 9

#define PLAYER_NUMBER_OF_KEYS 10

class Barge
{
public:

	// Public facing inputs array
	int p1keys[10];
	int p2keys[10];

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