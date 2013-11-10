#include "Player.h"


std::vector<std::string> Player::strTokenize(std::string s, char delim)
{
	const char EOL = '\n';
	std::vector<std::string> e;
	int reserve = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == delim)
		{
			reserve++; // Calculate number of elements to prevent
			//needless vector resizing
		}
	}

	e.reserve(reserve);

	std::string elem;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == delim || s[i] == EOL)
		{
			e.push_back(elem);
			elem = "";
		}
		else
		{
			elem.push_back(s[i]);
		}
	}
	return e;
}

std::vector<int> Player::strToki(std::string s, char delim)
{
	const char EOL = '\n';
	std::vector<int> e;
	int reserve = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == delim)
		{
			reserve++; // Calculate number of elements to prevent
			//needless vector resizing
		}
	}
	e.reserve(reserve);

	std::string elem;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == delim || s[i] == EOL)
		{
			e.push_back(atoi(elem.c_str()));
			elem = "";
		}
		else
		{
			elem.push_back(s[i]);
		}
	}
	return e;
}

std::vector<double> Player::strTokd(std::string s, char delim)
{
	const char EOL = '\n';
	std::vector<double> e;
	int reserve = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == delim)
		{
			reserve++; // Calculate number of elements to prevent
			//needless vector resizing
		}
	}
	e.reserve(reserve);

	std::string elem;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == delim || s[i] == EOL)
		{
			e.push_back(atof(elem.c_str()));
			elem = "";
		}
		else
		{
			elem.push_back(s[i]);
		}
	}
	return e;
}

Player::Player(std::string playerName, bool isP2)
{
	punchSnd = al_load_sample("data/hitsound/PunchHeavy.wav");
	blockSnd = al_load_sample("data/hitsound/block.ogg");
	name = playerName;
	sprite = new Sprite(name);
	isPlayer2 = isP2;
	std::stringstream ss;

	ss << CHAR_DIR << playerName << "/player.cfg";
	
	metaCfg = al_load_config_file(ss.str().c_str());

	// Load meta information
	displayName = al_get_config_value(metaCfg,"playerMeta","displayName");
	health = atoi(al_get_config_value(metaCfg,"playerMeta","health"));
	gravity = atof(al_get_config_value(metaCfg,"playerMeta","gravity"));
	gravityStd = atof(al_get_config_value(metaCfg,"playerMeta","gravity"));
	fwdSpeed = atof(al_get_config_value(metaCfg,"playerMeta","fwdSpeed"));
	backSpeed = atof(al_get_config_value(metaCfg,"playerMeta","backSpeed"));
	fwdJumpSpeed = atof(al_get_config_value(metaCfg,"playerMeta","fwdJumpSpeed"));
	backJumpSpeed = atof(al_get_config_value(metaCfg,"playerMeta","backJumpSpeed"));
	jumpStrength = atof(al_get_config_value(metaCfg,"playerMeta","jumpStrength"));
	jumpDelayMax = atof(al_get_config_value(metaCfg,"playerMeta","jumpDelay"));
	landDelayMax = atof(al_get_config_value(metaCfg,"playerMeta","landDelay"));

	// Standard animation indexes
	stdAnimIndexes[STANDANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","standAnim"));
	stdAnimIndexes[CROUCHANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","crouchAnim"));
	stdAnimIndexes[FORWARDANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","forwardAnim"));
	stdAnimIndexes[BACKANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","backAnim"));
	stdAnimIndexes[JUMPANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","jumpAnim"));
	stdAnimIndexes[JUMPFWDANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","jumpFwdAnim"));
	stdAnimIndexes[JUMPBACKANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","jumpBackAnim"));
	stdAnimIndexes[THROWANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","throwAnim"));
	stdAnimIndexes[GRABANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","grabAnim"));
	stdAnimIndexes[DOWNANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","downAnim"));
	stdAnimIndexes[GETUPANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","getUpAnim"));
	stdAnimIndexes[WINANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","winAnim"));
	stdAnimIndexes[LOSEANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","loseAnim"));
	stdAnimIndexes[BLOCKANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","blockAnim"));
	stdAnimIndexes[BLOCKLOWANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","blockLowAnim"));
	stdAnimIndexes[REELAIRANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","reelAirAnim"));
	stdAnimIndexes[PREJUMPANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","preJumpAnim"));
	stdAnimIndexes[REELANIM] = atoi(al_get_config_value(metaCfg,"playerAnims","reelAnim"));

	std::string inputVar = "n";
	std::string buttonVar = "p";
	std::string locusVar = "ground";

	ss.str("");

	for (int l_input = 0; l_input < INPUT_NUM; l_input++)
	{
		switch (l_input)
		{
		case I_N:
			inputVar = "n-";
			break;
		case I_B:
			inputVar = "b-";
			break;
		case I_F:
			inputVar = "f-";
			break;
		case I_QCF:
			inputVar = "qcf-";
			break;
		case I_QCB:
			inputVar = "qcb-";
			break;
		case I_FDP:
			inputVar = "fdp-";
			break;
		case I_BDP:
			inputVar = "bdp-";
			break;
		case I_FCHARGE:
			inputVar = "fcharge-";
			break;
		case I_BCHARGE:
			inputVar = "bcharge-";
			break;
		}
		for (int l_button = 0; l_button < BUTTON_NUM; l_button++)
		{
			switch (l_button)
			{
			case 0:
				buttonVar = "p-";
				break;
			case 1:
				buttonVar = "k-";
				break;
			}
			for (int l_locus = 0; l_locus < LOCUS_NUM; l_locus++)
			{
				switch (l_locus)
				{
				case L_GROUND:
					locusVar = "ground";
					break;
				case L_AIR:
					locusVar = "air";
					break;
				case L_AIRMOVING:
					locusVar = "airmoving";
					break;
				case L_CROUCH:
					locusVar = "crouch";
					break;
				}
				ss.str("");
				ss << inputVar << buttonVar << locusVar;
				
				if (al_get_config_value(metaCfg,ss.str().c_str(),"enabled") != NULL)
				{
					a_enabled[l_input][l_button][l_locus] = atoi(
						al_get_config_value(metaCfg,ss.str().c_str(),"enabled"));

					if (a_enabled[l_input][l_button][l_locus])
					{
						std::cout << "enabled for " << ss.str() << std::endl;
						a_whiffSnd[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"whiffSnd"));
						a_hitSnd[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"hitSnd"));
						a_animNum[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"animNum"));
						std::cout << "Animation number " << a_animNum[l_input][l_button][l_locus] << std::endl;
						a_damage[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"damage"));
						a_chipDamage[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"chipDamage"));
						a_knockDown[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"knockdown"));
						a_freeze[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"freeze"));
						a_hitStun[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"hitStun"));
						a_normalCancel[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"normalCancel"));
						a_hitType[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"hitType"));

						std::vector<int> tempstuff = strToki(
							al_get_config_value(metaCfg,ss.str().c_str(),"vecStepDelay"),',');
						for (unsigned int i = 0; i < tempstuff.size(); i++)
						{
							a_vecStepDelay[l_input][l_button][l_locus].push_back(tempstuff[i]);
						}
				
						// Populate terrifying move data
						tempstuff = strToki(
							al_get_config_value(metaCfg,ss.str().c_str(),"relativeVecX"),',');
						for (unsigned int i = 0; i < tempstuff.size(); i++)
						{
							a_relativeVecX[l_input][l_button][l_locus].push_back(tempstuff[i]);
						}
						tempstuff = strToki(
							al_get_config_value(metaCfg,ss.str().c_str(),"relativeVecY"),',');
						for (unsigned int i = 0; i < tempstuff.size(); i++)
						{
							a_relativeVecY[l_input][l_button][l_locus].push_back(tempstuff[i]);
						}

						a_knockBackVecX[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"knockBackVecX"));
						std::cout << "knockBackVecX: " << a_knockBackVecX[l_input][l_button][l_locus] << std::endl;
						a_knockBackVecY[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"knockBackVecY"));
						std::cout << "knockBackVecY: " << a_knockBackVecY[l_input][l_button][l_locus] << std::endl;
				
						std::vector<double> dstuff = strTokd(
							al_get_config_value(metaCfg,ss.str().c_str(),"vecX"),',');
						for (unsigned int i = 0; i < dstuff.size(); i++)
						{
							a_vecX[l_input][l_button][l_locus].push_back(dstuff[i]);
						}
						dstuff = strTokd(
							al_get_config_value(metaCfg,ss.str().c_str(),"vecY"),',');

						for (unsigned int i = 0; i < dstuff.size(); i++)
						{
							a_vecY[l_input][l_button][l_locus].push_back(dstuff[i]);
						}
						dstuff = strTokd(
							al_get_config_value(metaCfg,ss.str().c_str(),"dVecX"),',');
						for (unsigned int i = 0; i < dstuff.size(); i++)
						{
							a_dVecX[l_input][l_button][l_locus].push_back(dstuff[i]);
						}
						dstuff = strTokd(
							al_get_config_value(metaCfg,ss.str().c_str(),"dVecY"),',');
						for (unsigned int i = 0; i < dstuff.size(); i++)
						{
							a_dVecY[l_input][l_button][l_locus].push_back(dstuff[i]);
						}
						if (al_get_config_value(metaCfg,ss.str().c_str(),"projectile") != NULL)
						{
							a_projectile[l_input][l_button][l_locus] = atoi(
								al_get_config_value(metaCfg,ss.str().c_str(),"projectile"));
							if (a_projectile[l_input][l_button][l_locus])
							{
								a_projectileDelay[l_input][l_button][l_locus] = atoi(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileDelay"));
								a_projectileAnim[l_input][l_button][l_locus] = atoi(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileAnim"));
								a_projectileVecX[l_input][l_button][l_locus] = atof(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileVecX"));
								a_projectileVecY[l_input][l_button][l_locus] = atof(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileVecY"));
								a_projectileDVecX[l_input][l_button][l_locus] = atof(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileDVecX"));
								a_projectileDVecY[l_input][l_button][l_locus] = atof(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileDVecY"));
								a_projectileLife[l_input][l_button][l_locus] = atoi(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileLife"));
								a_projectileHitSnd[l_input][l_button][l_locus] = atoi(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileHitSnd"));
								a_projectileX[l_input][l_button][l_locus] = atoi(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileX"));
								a_projectileY[l_input][l_button][l_locus] = atoi(
									al_get_config_value(metaCfg,ss.str().c_str(),"projectileY"));
							}
						}
					}
				}
				else
				{
					a_enabled[l_input][l_button][l_locus] = false;
				}
				
				// [INPUT_NUM][BUTTON_NUM][LOCUS_NUM];
			}
		}
	}
	std::cout << "Done loading INI info." << std::endl;

	// Clear out state variables
	qcf = 0;
	qcb = 0;
	fdp = 0;
	bdp = 0;
	fcharge = 0;
	bcharge = 0;
	hitfreeze = 0;
	direction = isPlayer2?false:true;
	crouching = false;
	grounded = true;
	yPos = GROUNDPOS;
	xPos = isPlayer2?(320 + (192/2)):(320 - (192/2));
	vecX = 0;
	vecY = 0;
	slideX = 0;

	
	downQC = 0;
	downForwardQC = 0;
	qcf = 0;
	downBackQC = 0;
	qcb = 0;
	forwardDP = 0;
	downDP = 0;
	fdp = 0;
	backDP = 0;
	downBDP = 0;
	bdp = 0;

	forwardDP = 0;
	downDP = 0;
	downBDP = 0;
	backDP = 0;

	attack_input = 0;
	attack_button = 0;
	attack_locus = 0;

	doingNormal = 0;
	doingSpecial = 0;
	jumpDelay = 0;
	landDelay = 0;
	landBlockCancel = false;
	hitStun = 0;
	blockStun = 0;
	standDelay = 0;
	knockDown = false;
	neutralJump = false;

	hitInAir = false;
}

Player::~Player()
{
	delete sprite;
	al_destroy_sample(punchSnd);
	al_destroy_sample(blockSnd);
}

void Player::getHit()
{
	bool hit = false;
	if (other->didHit == false)
	{
		for (int i = 1; i < 4; i++)
		{
			// check for the 3 vulns vs an attack box
			if (checkBox(i, 4))
			{
				hit = true;
			}
		}

		if (hit && !knockDown && standDelay == 0)
		{
			al_play_sample(punchSnd,1,0,0.8,ALLEGRO_PLAYMODE_ONCE,0);
			other->didHit = true;
			bool doBlock = false;
			// Determine if it is a block
			if (hitStun == 0 && grounded && (doingNormal == 0) && (doingSpecial == 0))
			{
				int hitType = other->a_hitType[other->attack_input][other->attack_button][other->attack_locus];
				jumpDelay = 0;
				landDelay = 0;
				if (isPlayer2)
				{
					if (direction)
					{
						if (barge->p2keys[LEFTKEY] && !barge->p2keys[DOWNKEY])
						{
							// Go into a block
							if (hitType != HIT_LOW)
							{
								doBlock = true;
							}
						}
						if (barge->p2keys[LEFTKEY] && barge->p2keys[DOWNKEY])
						{
							// Go into a block
							if (hitType != HIT_HI)
							{
								doBlock = true;
							}
						}
					}
					else
					{
						if (barge->p2keys[RIGHTKEY] && !barge->p2keys[DOWNKEY])
						{
							// Go into a block
							if (hitType != HIT_LOW)
							{
								doBlock = true;
							}
						}
						if (barge->p2keys[RIGHTKEY] && barge->p2keys[DOWNKEY])
						{
							// Go into a block
							if (hitType != HIT_HI)
							{
								doBlock = true;
							}
						}
					}
				}
				else
				{
					if (direction)
					{
						if (barge->p1keys[LEFTKEY] && !barge->p1keys[DOWNKEY])
						{
							// Go into a block
							if (hitType != HIT_LOW)
							{
								doBlock = true;
							}
						}
						if (barge->p1keys[LEFTKEY] && barge->p1keys[DOWNKEY])
						{
							// Go into a block
							if (hitType != HIT_HI)
							{
								doBlock = true;
							}
						}
					}
					else
					{
						if (barge->p1keys[RIGHTKEY] && !barge->p1keys[DOWNKEY])
						{
							// Go into a block
							if (hitType != HIT_LOW)
							{
								doBlock = true;
							}
						}
						if (barge->p1keys[RIGHTKEY] && barge->p1keys[DOWNKEY])
						{
							// Go into a block
							if (hitType != HIT_HI)
							{
								doBlock = true;
							}
						}
					}
				}
			}
			if (doBlock)
			{
				al_play_sample(blockSnd,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
				std::cout << "Block!" << std::endl;
				blockStun = other->a_hitStun[other->attack_input][other->attack_button][other->attack_locus];
				hitStun = 0;
				hitfreeze = other->a_freeze[other->attack_input][other->attack_button][other->attack_locus] / 2;
				knockDown = false;
			}
			else
			{
				std::cout << "Hit! " ;
				blockStun = 0;
				hitStun = other->a_hitStun[other->attack_input][other->attack_button][other->attack_locus];
				hitfreeze = other->a_freeze[other->attack_input][other->attack_button][other->attack_locus];
				knockDown = other->a_knockDown[other->attack_input][other->attack_button][other->attack_locus];
				if (knockDown)
				{
					standDelay = STAND_MAX;
					std::cout << "It's a knockdown! ";
				}
				if (knockDown || !grounded)
				{
					std::cout << "Launched! " << std::endl;
					vecY = other->a_knockBackVecY[other->attack_input][other->attack_button][other->attack_locus];
					hitInAir = true;

					if (yPos < GROUNDPOS)
					{
						hitInAir = true;
					}

					if (grounded)
					{
						hitInAir = true;
						yPos--;
						grounded = false;
					}
				}
				else
				{
					vecY = 0;
				}
			}
			doingNormal = 0;
			doingSpecial = 0;
			vecX = 0;
			if (yPos >= GROUNDPOS)
			{
				if (direction)
				{
					slideX = -1 * other->a_knockBackVecX[other->attack_input][other->attack_button][other->attack_locus] / 2;
				}
				else
				{
					slideX = other->a_knockBackVecX[other->attack_input][other->attack_button][other->attack_locus] / 2;
				}
			}
			else
			{
				if (direction)
				{
					vecX = -1 * other->a_knockBackVecX[other->attack_input][other->attack_button][other->attack_locus] / 2;
					slideX = 0;
				}
				else
				{
					vecX = other->a_knockBackVecX[other->attack_input][other->attack_button][other->attack_locus] / 2;
					slideX = 0;
				}
			}
			health = health - a_damage[other->attack_input][other->attack_button][other->attack_locus];
		}
	}
}

void Player::handleInputs()
{
	// Check for walking around inputs (not attack buttons)
	bool inputOk = true;
	
	typedef int Keys[8];
	Keys* inputs = isPlayer2? &(barge->p2keys) : &(barge->p1keys);
	if (hitStun > 0 || blockStun > 0)
	{
		inputOk = false;
	}
	else if (!grounded)
	{
		inputOk = false;
	}
	else if (standDelay > 0)
	{
		inputOk = false;
	}
	else if (doingNormal > 0 || doingSpecial > 0)
	{
		inputOk = false;
	}

	if (standDelay > 0 && grounded)
	{
		vecX = 0;
		slideX = 0;
		standDelay--;
		if (standDelay > sprite->numFrames(stdAnimIndexes[GETUPANIM]))
		{
			sprite->playAnimation(stdAnimIndexes[DOWNANIM]);
		}
		else
		{
			sprite->playAnimation(stdAnimIndexes[GETUPANIM]);
		}
	}

	if (doingNormal > 0)
	{
		doingNormal--;
	}
	if (doingSpecial > 0)
	{
		doingNormal--;
	}
	if (grounded)
	{
		hitInAir = false;
		if (jumpDelay > 0)
		{
			sprite->playAnimation(stdAnimIndexes[PREJUMPANIM]);
			inputOk = false;
			jumpDelay--;
			vecX = 0;
			vecY = 0;
		}

		if (landDelay > 0)
		{
			sprite->playAnimation(stdAnimIndexes[PREJUMPANIM]);
			inputOk = false;
			landDelay--;
			vecX = 0;
			vecY = 0;
		}
		if (inputOk)
		{
			didHit = false;
			// Face the other player when grounded
			// not in the middle of an anim, though
		}
	}
	else
	{
		if( !grounded && blockStun == 0 && hitStun == 0)
		{
			if((*inputs)[LEFTKEY] > 0)
			{
				xPos += DIR_INFLUENCE * -1;
			}
			if((*inputs)[RIGHTKEY] > 0)
			{
				xPos += DIR_INFLUENCE;
			}
			if((*inputs)[UPKEY] > 0)
			{
				yPos -= DIR_INFLUENCE;
			}
			if((*inputs)[DOWNKEY] > 0)
			{
				yPos += DIR_INFLUENCE;
			}
		}
	}
	
	if (!grounded && hitStun > 0)
	{
		sprite->playAnimation(stdAnimIndexes[REELAIRANIM]);
	}
	if (grounded && hitStun > 0)
	{
		sprite->playAnimation(stdAnimIndexes[REELANIM]);
	}

	if (xPos < other->xPos)
	{
		direction = true;
	}
	if (xPos > other->xPos)
	{
		direction = false;
	}

	if (blockStun > 0)
	{
		if (crouching)
		{
			sprite->playAnimation(stdAnimIndexes[BLOCKLOWANIM]);
		}
		else
		{
			sprite->playAnimation(stdAnimIndexes[BLOCKANIM]);
		}
		blockStun--;
		knockDown = 0;
	}
	if (grounded)
	{
		if (blockStun == 0 && hitStun == 0 && crouching && doingNormal == 0 && doingSpecial == 0)
		{
			sprite->playAnimation(stdAnimIndexes[CROUCHANIM]);
		}
		if (hitStun > 0)
		{
			hitStun--;
		}
		if (hitStun == 0)
		{
			knockDown = 0;
		}
	}
	if (!grounded)
	{
		if (hitStun > 1)
		{
			hitStun--;
		}
	}

	/////////////////
	//For detecting qcf qcb DP
if ((*inputs)[LEFTKEY] > 0)
{
	if(direction)//Pressing left is back
	{
		if((*inputs)[DOWNKEY] > 0)//Down left - down back
		{
			//backwards dragon punch complete
			if(downBDP > 0)
			{
				bdp = LENIENCY;
				std::cout<<"Back Dragon Punch"<<std::endl;
			}
			//qcb part 2
			if(downQC > 0)
				downBackQC = LENIENCY;
		}
		else //just pressing back
		{
			//QCB Complete
			if(downBackQC > 0)
			{
				qcb = LENIENCY;
				std::cout<<"Quarter Circle Back"<<std::endl;
			}
			backDP = LENIENCY;
		}
	}
	else //Pressing Left is forward
	{
		if((*inputs)[DOWNKEY] > 0)//Down left - down forward
		{
			//Dragon Punch Complete
			if(downDP > 0)
			{
				fdp = LENIENCY;
				std::cout<<"Forward Dragon Punch"<<std::endl;
			}
			//QCF pt 2/3
			if(downQC > 0)
				downForwardQC  = LENIENCY;
		}
		else //just pressing forward
		{
			//QCF Complete
			if(downForwardQC > 0)
			{
				qcf = LENIENCY;
				std::cout<<"Quarter Circle Forward"<<std::endl;
			}
			forwardDP = LENIENCY;
		}
	}
}
else if((*inputs)[RIGHTKEY] > 0)
{
	if(!direction)//Pressing right is back
	{
		if((*inputs)[DOWNKEY] > 0)//Down right - down back
		{
			//backwards dragon punch complete
			if(downBDP > 0)
			{
				bdp = LENIENCY;
				std::cout<<"Back Dragon Punch"<<std::endl;
			}
			//qcb part 2
			if(downQC > 0)
				downBackQC = LENIENCY;
		}
		else //just pressing back
		{
			//QCB Complete
			if(downBackQC > 0)
			{
				qcb = LENIENCY;
				std::cout<<"Quarter Circle Back"<<std::endl;
			}
			backDP = LENIENCY;
		}
	}
	else //Pressing right is forward
	{
		if((*inputs)[DOWNKEY] > 0)//Down right - down forward
		{
			//Dragon Punch Complete
			if(downDP > 0)
			{
				fdp = LENIENCY;
				std::cout<<"Forward Dragon Punch"<<std::endl;
			}
			//QCF pt 2/3
			if(downQC > 0)
				downForwardQC  = LENIENCY;
		}
		else //just pressing forward
		{
			//QCF Complete
			if(downForwardQC > 0)
			{
				qcf = LENIENCY;
				std::cout<<"Quarter Circle Forward"<<std::endl;
			}
			forwardDP = LENIENCY;
		}
	}
}
else if((*inputs)[DOWNKEY] > 0) //Just pressing down
{
	//QCF and QCB pt1
	downQC = LENIENCY;
	//FDP pt2
	if(forwardDP > 0)
		downDP = LENIENCY;
	//BDP pt2
	if(backDP > 0)
		downBDP = LENIENCY;
}



	/////////////////

	if (inputOk && !crouching)
	{
		// walking left and right
		if ((*inputs)[LEFTKEY] > 0)
		{
			sprite->playAnimation(
				direction?stdAnimIndexes[BACKANIM]:stdAnimIndexes[FORWARDANIM]);

			if (direction)
			{
				vecX = backSpeed * -1;
			}
			else
			{
				vecX = fwdSpeed * -1;
			}
		}
		else if ((*inputs)[RIGHTKEY] > 0)
		{
			sprite->playAnimation(
				direction?stdAnimIndexes[FORWARDANIM]:stdAnimIndexes[BACKANIM]);

			if (!direction)
			{
				vecX = backSpeed;
			}
			else
			{
				vecX = fwdSpeed;
			}
		}
		else 
		{
			vecX = 0;
			sprite->playAnimation(stdAnimIndexes[STANDANIM]);
		}
		if ((*inputs)[DOWNKEY] > 0)
		{
			sprite->playAnimation(stdAnimIndexes[CROUCHANIM]);
			crouching = true;
			vecX = 0;
		}
		// Handling jumps
		if ((*inputs)[UPKEY] > 0)
		{
			jumpDelay = jumpDelayMax + 1;
		}
	}
	if (inputOk && crouching)
	{
		if ((*inputs)[DOWNKEY] == 0)
		{
			crouching = false;
		}
	}

	// More jump processing
	if (jumpDelay == 1)
	{
		jumpDelay = 0;
		grounded = false;
		yPos = GROUNDPOS-1;
		vecY = jumpStrength * -1;
		if ((*inputs)[LEFTKEY] > 0)
		{
			sprite->playAnimation(direction?stdAnimIndexes[JUMPBACKANIM]:stdAnimIndexes[JUMPFWDANIM]);
			vecX = direction?(backJumpSpeed * -1):(fwdJumpSpeed * -1);
			neutralJump = false;
		}
		else if ((*inputs)[RIGHTKEY] > 0)
		{
			sprite->playAnimation(direction?stdAnimIndexes[JUMPFWDANIM]:stdAnimIndexes[JUMPBACKANIM]);
			vecX = direction?(fwdJumpSpeed):(backJumpSpeed);
			neutralJump = false;
		}
		else
		{
			sprite->playAnimation(stdAnimIndexes[JUMPANIM]);
			vecX = 0;
			neutralJump = true;
		}
		landDelay = landDelayMax;
	}
	if(downQC > 0)
		downQC--;
	if(downForwardQC > 0)
		downForwardQC--;
	if(downBackQC>0)
		downBackQC--;
	if(backQC > 0)
		backQC--;
	if(forwardDP > 0)
		forwardDP--;
	if(downDP > 0)
		downDP--;
	if(downBDP > 0)
		downBDP--;
	if(fdp > 0)
		fdp--;
	if(bdp > 0)
		bdp--;
	if(backDP > 0)
		backDP--;

	if (qcb > 0)
	{
		qcb--;
	}
	if (qcf > 0)
	{
		qcf--;
	}
	if (fdp > 0)
	{
		fdp--;
	}
	if (bdp > 0)
	{
		bdp--;
	}

	// Process actual attack inputs here
	if (inputOk || (!grounded && !knockDown && hitStun == 0 && doingNormal == 0 && doingSpecial == 0))
	{
		if ((*inputs)[4] == 1 || (*inputs)[5] == 1)
		{
			int atkInput;
			int atkButton;
			int atkLocus;

			// Figure out buttons
			if ((*inputs)[5] == 1)
			{
				atkButton = 1;
			}
			else
			{
				atkButton = 0;
			}

			// Figure out input
			if (qcf > 0)
			{
				atkInput = I_QCF;
			}
			else if (qcb > 0)
			{
				atkInput = I_QCB;
			}
			else if (fdp > 0)
			{
				atkInput = I_FDP;
			}
			else if (bdp > 0)
			{
				atkInput = I_BDP;
			}
			else if (fcharge > 0)
			{
				atkInput = I_FCHARGE;
			}
			else if (bcharge > 0)
			{
				atkInput = I_BCHARGE;
			}
			else
			{
				if (direction)
				{
					if ((*inputs)[LEFTKEY] > 0)
					{
						atkInput = I_B;
					}
					else if ((*inputs)[RIGHTKEY] > 0)
					{
						atkInput = I_F;
					}
					else
					{
						atkInput = I_N;
					}
				}
				else
				{
					if ((*inputs)[RIGHTKEY] > 0)
					{
						atkInput = I_B;
					}
					else if ((*inputs)[LEFTKEY] > 0)
					{
						atkInput = I_F;
					}
					else
					{
						atkInput = I_N;
					}
				}
			}

			// Find locus
			if (grounded)
			{
				atkLocus = crouching?L_CROUCH:L_GROUND;
			}
			else
			{
				atkLocus = neutralJump?L_AIR:L_AIRMOVING;
			}
			// short-circuit specials
			if (atkInput != I_N && atkInput != I_F && atkInput != I_B)
			{
				if (atkLocus == L_CROUCH)
				{
					atkLocus = L_GROUND;
				}
				if (atkLocus == L_AIRMOVING)
				{
					atkLocus = L_AIR;
				}
			}
			doAttack(atkInput,atkButton,atkLocus);
		}
	}
}

void Player::doAttack(int atkInput, int atkButton, int atkLocus)
{
	attack_button = atkButton;
	attack_locus = atkLocus;
	attack_input = atkInput;
	if (attack_input == I_F)
	{
		if(!a_enabled[attack_input][attack_button][attack_locus])
		{
			std::cout << "No forward" << std::endl;
			attack_input = I_N;
		}
	}
	if (attack_input == I_B)
	{
		if(!a_enabled[attack_input][attack_button][attack_locus])
		{
			std::cout << "No back" << std::endl;
			attack_input = I_N;
		}
	}

	if (attack_locus == L_AIRMOVING)
	{
		if(!a_enabled[attack_input][attack_button][attack_locus])
		{
			std::cout << "No moving in air, doing neutral." << std::endl;
			attack_locus = L_AIR;
		}
	}


	std::cout << "Trying " <<  attack_input << " , " << attack_button << " , " << attack_locus << std::endl;

	if (a_enabled[attack_input][attack_button][attack_locus])
	{
		int animNum = a_animNum[attack_input][attack_button][attack_locus];
		std::cout << "doing attack " << attack_input << " , " << attack_button << " , " << attack_locus << " anim " << animNum << std::endl;
		sprite->playAnimation(animNum);
		if (grounded)
		{
			vecX = (direction?1:-1) * a_vecX[attack_input][attack_button][attack_locus][0];
			vecY = a_vecY[attack_input][attack_button][attack_locus][0];
			if (vecY < 0)
			{
				grounded = false;
				yPos--;
			}
		}
		if (attack_input == I_N || attack_input == I_F || attack_input == I_B)
		{
			doingNormal = sprite->numFrames(animNum);
		}
		else
		{
			doingNormal = sprite->numFrames(animNum);
		}
	}
}

void Player::doPhysics()
{
	grounded = (yPos >= GROUNDPOS);
	if (grounded)
	{
		yPos = GROUNDPOS;
	}
	else
	{
		yPos = yPos + vecY;
	}
	if (xPos > BOUNDS && xPos < STAGEWIDTH - BOUNDS)
	{
		xPos = xPos + slideX;
	}
	else
	{
		other->xPos = other->xPos - slideX;
	}
	if (slideX >= SLIDEFRICTION)
	{
		slideX -= SLIDEFRICTION;
	}
	else if (slideX <= SLIDEFRICTION * -1)
	{
		slideX += SLIDEFRICTION;
	}
	else
	{
		slideX = 0;
	}

	xPos = xPos + vecX;
	if (!grounded)
	{
		vecY = vecY + gravity;
	}

	boundsPush();
}

bool Player::freezeGame()
{
	bool retval = hitfreeze > 0;
	hitfreeze--;
	return (retval);
}

void Player::checkCommands()
{

}

void Player::attackVectors()
{

}

void Player::loadSpriteBarge()
{
	sprite->barge = barge;
}
#define MAXTRIES 16

void Player::boundsPush()
{
	int tries = 0;
	while (checkBox(0,0) && tries < MAXTRIES)
	{
		if (xPos < other->xPos)
		{
			if (!grounded && other->grounded)
			{
				xPos = xPos - (0.5 * vecX) + (0.5 * other->vecX);
				tries = MAXTRIES;
			}
			else
			{
				if (xPos > BOUNDS + 1)
				{
					xPos--;
					other->xPos++;
				}
				else
				{
					other->xPos++;
				}
			}
		}
		if (xPos >= other->xPos)
		{
			if (!grounded && other->grounded)
			{
				xPos = xPos - (0.5 * vecX) + (0.5 * other->vecX);
				tries = MAXTRIES;
			}
			else
			{
				if (xPos < 640-BOUNDS-1)
				{
					xPos++;
					other->xPos--;
				}
				else
				{
					other->xPos--;
				}
			}
		}
		tries++;
	}
	if (xPos < BOUNDS)
	{
		xPos = BOUNDS;
	}
	if (xPos > 640-BOUNDS)
	{
		xPos = 640-BOUNDS;
	}
	if (other != NULL)
	{
		while (floor(xPos - other->xPos) > SCREENWIDTH-(BOUNDS*2))
		{
			xPos--;
			other->xPos++;
		}
	}
}

void Player::animate()
{
	sprite->animate();
}

void Player::blit(int scrollX)
{
	sprite->blit(floor(xPos) - (PLAYERWIDTH/2) - scrollX,yPos-(PLAYERHEIGHT),(xPos>other->xPos),isPlayer2);
}

void Player::boxBlit(int scrollX)
{
	sprite->boxBlit(floor(xPos) - (PLAYERWIDTH/2) - scrollX,yPos-(PLAYERHEIGHT),!direction);
}

bool Player::checkBox(int a, int b)
{
	int x1;
	if (direction)
	{
		x1 = xPos + (sprite->getBoxX(a));
	}
	else
	{
		x1 = xPos + (PLAYERWIDTH - sprite->getBoxX(a) - sprite->getBoxW(a));
	}
	int y1 = yPos + sprite->getBoxY(a);
	int w1 = sprite->getBoxW(a);
	int h1 = sprite->getBoxH(a);
	int x2;
	if (other->direction)
	{
		x2 = other->xPos + (other->sprite->getBoxX(b));
	}
	else
	{
		x2 = other->xPos + (PLAYERWIDTH - other->sprite->getBoxX(b) - other->sprite->getBoxW(b));
	}
	int y2 = other->yPos + other->sprite->getBoxY(b);
	int w2 = other->sprite->getBoxW(b);
	int h2 = other->sprite->getBoxH(b);
	bool retval = true;
	if (x1 + w1 < x2)
	{
		retval = false;
	}
	if (x2 + w2 < x1)
	{
		retval = false;
	}
	if (y1 + h1 < y2)
	{
		retval = false;
	}
	if (y2 + h2 < y1)
	{
		retval = false;
	}
	return retval;
}

