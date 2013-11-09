#include "Player.h"

bool Player::freezeGame()
{
	hitfreeze--;
	return (hitfreeze>0);
}

Player::Player(std::string playerName, bool isP2)
{
	name = playerName;
	sprite = new Sprite(name);
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

	



	// Clear out state variables
	qcf = 0;
	qcb = 0;
	fdp = 0;
	bdp = 0;
	fcharge = 0;
	bcharge = 0;
}