#include "Player.h"

bool Player::freezeGame()
{
	hitfreeze--;
	return (hitfreeze>0);
}
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
	name = playerName;
	sprite = new Sprite(name);
	sprite->barge = barge;
	isPlayer2 = isP2;
	std::stringstream ss;

	ss << CHAR_DIR << playerName << "/player.cfg";
	metaCfg = al_load_config_file(ss.str().c_str());

	// Load basic animation cues
	displayName = al_get_config_value(metaCfg,"playerMeta","displayName");
	health = atoi(al_get_config_value(metaCfg,"playerMeta","health"));
	gravity = atof(al_get_config_value(metaCfg,"playerMeta","gravity"));
	fwdSpeed = atof(al_get_config_value(metaCfg,"playerMeta","fwdSpeed"));
	backSpeed = atof(al_get_config_value(metaCfg,"playerMeta","backSpeed"));
	fwdJumpSpeed = atof(al_get_config_value(metaCfg,"playerMeta","fwdJumpSpeed"));
	backJumpSpeed = atof(al_get_config_value(metaCfg,"playerMeta","backJumpSpeed"));
	jumpStrength = atof(al_get_config_value(metaCfg,"playerMeta","jumpStrength"));
	jumpDelayMax = atof(al_get_config_value(metaCfg,"playerMeta","jumpDelay"));
	landDelayMax = atof(al_get_config_value(metaCfg,"playerMeta","landDelay"));

	std::string inputVar = "n";
	std::string buttonVar = "p";
	std::string locusVar = "ground";

	ss.str("");

	for (int l_input = 0; l_input < INPUT_NUM; l_input++)
	{
		switch (l_input)
		{
		case I_N:
			inputVar = "[n]-";
			break;
		case I_B:
			inputVar = "[b]-";
			break;
		case I_F:
			inputVar = "[f]-";
			break;
		case I_QCF:
			inputVar = "[qcf]-";
			break;
		case I_QCB:
			inputVar = "[qcb]-";
			break;
		case I_FDP:
			inputVar = "[fdp]-";
			break;
		case I_BDP:
			inputVar = "[bdp]-";
			break;
		case I_FCHARGE:
			inputVar = "[fcharge]-";
			break;
		case I_BCHARGE:
			inputVar = "[bcharge]-";
			break;
		}
		for (int l_button = 0; l_button < BUTTON_NUM; l_button++)
		{
			switch (l_button)
			{
			case 0:
				buttonVar = "[p]-";
			case 1:
				buttonVar = "[k]-";
			}
			for (int l_locus = 0; l_locus < LOCUS_NUM; l_locus++)
			{
				switch (l_locus)
				{
				case L_GROUND:
					locusVar = "[ground]";
				case L_AIR:
					locusVar = "[air]";
				case L_AIRMOVING:
					locusVar = "[airmoving]";
				case L_CROUCH:
					locusVar = "[crouch]";
				case L_SPECIAL:
					locusVar = "[special]";
				}

				ss << inputVar << buttonVar << locusVar;

				std::cout << "Loading " << ss.str() << " for " << name << std::endl;

				if (al_get_config_value(metaCfg,ss.str().c_str(),"enabled") != NULL)
				{

					a_enabled[l_input][l_button][l_locus] = atoi(
						al_get_config_value(metaCfg,ss.str().c_str(),"enabled"));
					a_whiffSnd[l_input][l_button][l_locus] = atoi(
						al_get_config_value(metaCfg,ss.str().c_str(),"whiffSnd"));
					a_hitSnd[l_input][l_button][l_locus] = atoi(
						al_get_config_value(metaCfg,ss.str().c_str(),"hitSnd"));
					a_animNum[l_input][l_button][l_locus] = atoi(
						al_get_config_value(metaCfg,ss.str().c_str(),"animNum"));
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
					a_knockBackVecY[l_input][l_button][l_locus] = atoi(
						al_get_config_value(metaCfg,ss.str().c_str(),"knockBackVecY"));
				
					std::vector<double> dstuff = strTokd(
						al_get_config_value(metaCfg,ss.str().c_str(),"vecX"),',');
					for (unsigned int i = 0; i < tempstuff.size(); i++)
					{
						a_vecX[l_input][l_button][l_locus].push_back(dstuff[i]);
					}
					std::vector<double> dstuff = strTokd(
						al_get_config_value(metaCfg,ss.str().c_str(),"vecY"),',');
					for (unsigned int i = 0; i < tempstuff.size(); i++)
					{
						a_vecY[l_input][l_button][l_locus].push_back(dstuff[i]);
					}
					std::vector<double> dstuff = strTokd(
						al_get_config_value(metaCfg,ss.str().c_str(),"dVecX"),',');
					for (unsigned int i = 0; i < tempstuff.size(); i++)
					{
						a_dVecX[l_input][l_button][l_locus].push_back(dstuff[i]);
					}
					std::vector<double> dstuff = strTokd(
						al_get_config_value(metaCfg,ss.str().c_str(),"dVecY"),',');
					for (unsigned int i = 0; i < tempstuff.size(); i++)
					{
						a_dVecY[l_input][l_button][l_locus].push_back(dstuff[i]);
					}
					if (al_get_config_value(metaCfg,ss.str().c_str(),"projectile") != NULL)
					{
						a_projectile[l_input][l_button][l_locus] = atoi(
							al_get_config_value(metaCfg,ss.str().c_str(),"projectile"));
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
}