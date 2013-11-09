#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

#include "dirDefs.h"
#include "Sprite.h"
#include "Barge.h"

#define GROUNDPOS 216
#define MIN_X 640+72
#define MAX_X 320-72

#define BOUNDS 16

#define STAGEWIDTH 640
#define SCREENWIDTH 320

#define PLAYERWIDTH 192
#define PLAYERHEIGHT 128

#define STANDANIM 0
#define CROUCHANIM 1
#define FORWARDANIM 2
#define BACKANIM 3
#define JUMPANIM 4
#define JUMPFWDANIM 5
#define JUMPBACKANIM 6
#define THROWANIM 7
#define GRABANIM 8
#define DOWNANIM 9
#define GETUPANIM 10
#define WINANIM 11
#define LOSEANIM 12
#define BLOCKANIM 13
#define BLOCKLOWANIM 14
#define REELANIM 15
#define PREJUMPANIM 16
#define LENIENCY 2


#define DIR_INFLUENCE 0.55

#define NUM_STD_ANIMS 17

class Player
{
public:
	Sprite* sprite;
	Barge* barge;
	Player* other;

	ALLEGRO_CONFIG* metaCfg;
	ALLEGRO_CONFIG* animCfg;

	Player(std::string playerName, bool isP2);
	~Player();

	std::string name;
	std::string displayName;
	//Activates when ONLY direction pressed
	int down,downForward,forward,downBack,back;

	
	// Check if other has the attacking hitbox (4) overlapping our 
	// player's vuln boxes (1-3)
	void getHit();

	// inputs for player left / right, or start an attack animation
	void handleInputs();

	// Move the player around
	void doPhysics();

	// Whether or not to pause the action (and decrease hitfreeze)
	bool freezeGame();

	// Check for command inputs
	void checkCommands();

	// Check for charge inputs
	void checkCharge();

	// Run the attack vector processor for movements
	void attackVectors();

	// Pushes player back if out of bounds or touching the other player
	void boundsPush();

	// Runs animation sequence (if freeze is 0)
	void animate();

	// Renders the player on screen based on coordinates
	void blit(int scrollX);

	// Renders the player on screen based on coordinates
	void boxBlit(int scrollX);

	// Checks if hitbox a is colliding with enemy hitbox b
	bool checkBox(int a, int b);

	// Detected valid input buffers when > 0
	int qcf;
	int qcb;
	int fdp;
	int bdp;
	int fcharge;
	int bcharge;

	void loadSpriteBarge();
	// Load properties 
	
	// Game state variables
	int health;

	
	int hitfreeze; // pause all action
	bool direction; // Right == true
	bool crouching;
	bool grounded;
	double slideX; // Sliding from doing an attack on the ground
	double vecX;
	double vecY;
	double xPos;
	double yPos;

private:

	

	std::vector<std::string> strTokenize(std::string s, char delim);
	std::vector<int> strToki(std::string s, char delim);
	std::vector<double> strTokd(std::string s, char delim);

	// Attack parameters
#define INPUT_NUM 9
#define BUTTON_NUM 2
#define LOCUS_NUM 4

#define I_N 0
#define I_B 1
#define I_F 2
#define I_QCF 3
#define I_QCB 4
#define I_FDP 5
#define I_BDP 6
#define I_FCHARGE 7
#define I_BCHARGE 8

#define L_GROUND 0
#define L_AIR 1
#define L_AIRMOVING 2
#define L_CROUCH 3
#define L_SPECIAL 4

#define HIT_HI 0
#define HIT_MED 1
#define HIT_LOW 2

	// Regular meta stuff
	int  a_enabled[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int  a_whiffSnd[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int  a_hitSnd[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int  a_animNum[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int  a_damage[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int  a_chipDamage[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	bool a_knockDown[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int  a_freeze[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int  a_hitStun[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	bool a_normalCancel[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int  a_hitType[INPUT_NUM][BUTTON_NUM][LOCUS_NUM]; 

	// Movement stuff!
	double              a_knockBackVecX[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	double              a_knockBackVecY[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	std::vector<int>    a_vecStepDelay[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	std::vector<bool>   a_relativeVecX[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	std::vector<bool>   a_relativeVecY[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	std::vector<double> a_vecX[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	std::vector<double> a_vecY[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	std::vector<double> a_dVecX[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	std::vector<double> a_dVecY[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];

	// Projectile properties
	bool   a_projectile[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int    a_projectileDelay[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int    a_projectileAnim[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	double a_projectileVecX[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	double a_projectileVecY[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	double a_projectileDVecX[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	double a_projectileDVecY[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int    a_projectileLife[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int    a_projectileHitSnd[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int    a_projectileX[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
	int    a_projectileY[INPUT_NUM][BUTTON_NUM][LOCUS_NUM];	

	// Animation indexes for standard anims
	int stdAnimIndexes[NUM_STD_ANIMS];

	bool isPlayer2;

	// Stored player properties
	double fwdSpeed;
	double backSpeed;
	double fwdJumpSpeed;
	double backJumpSpeed;
	double gravityStd;
	double gravity;
	double jumpStrength;
	int jumpDelayMax;
	int landDelayMax;


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
};