#include "Sprite.h"

std::vector<std::string> Sprite::strTokenize(std::string s, char delim)
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

Sprite::Sprite(std::string name)
{
	charName = name;
	animNum = 0;
	frameNum = 0;
	frameCnt = 0;
	std::stringstream ss;
	ss << CHAR_DIR << charName << ANIM_DIR;
	std::string filePath = ss.str();
	ss.str("");
	ss << filePath << "anim.cfg";
	ALLEGRO_CONFIG* animCfg;

	animCfg = al_load_config_file(ss.str().c_str());

	ss.str("");

	numAnimations = 0;
	int found = 0;
	while (numAnimations == 0)
	{

		found++;
	}
}

Sprite::~Sprite()
{
	for (unsigned int y = 0; y < ANIM_NUM; y++)
	{
		for (unsigned int x = 0; x < frames[y].size(); x++)
		{
			if (frames[y][x] != NULL)
			{
				al_destroy_bitmap(frames[y][x]);
			}
		}
	}
}

void Sprite::animate()
{
	if (frameCnt > length[animNum][frameNum])
	{
		frameCnt = 0;

		if (frameNum < animLength[animNum] - 1)
		{
			frameNum++;
		}
		else
		{
			if (loop[animNum] > 0)
			{
				frameNum = loop[animNum];
			}
		}
	}
	frameCnt++;
}

void Sprite::playAnimation(int num)
{
	if (animNum != num)
	{
		animNum = num;
		frameCnt = 0;
		frameNum = 0;
	}
}

void Sprite::switchAnimation(int num)
{
	if (animNum != num)
	{
		animNum = num;
		frameCnt = 0;
	}
}

void Sprite::forceAnimation(int num)
{
	animNum = num;
	frameCnt = 0;
	frameNum = 0;
}

void Sprite::resetAnimation(int frame = 0)
{
	frameNum = frame;
	frameCnt = 0;
}

unsigned int Sprite::animationLength(int num)
{
	return animLength[num];
}

unsigned int Sprite::numFrames(int num)
{
	unsigned int len;
	for (int i = 0; i < animLength[num]; i++)
	{
		len += length[num][i];
	}
	return len;
}

ALLEGRO_BITMAP* Sprite::getFrame()
{
	return frames[animNum][frameNum];
}