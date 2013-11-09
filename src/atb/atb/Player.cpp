#include "Player.h"

bool Player::freezGame()
{
	hitfreeze--;
	return (hitfreeze>0);
}