#include "Sprite.h"


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
	int index = 0;
	while (numAnimations == 0)
	{
		ss.str("");
		ss << index;
		std::string section = ss.str();

		// Check if there is another to load
		if (al_get_config_value(animCfg,section.c_str(),"frameName") != NULL)
		{
			// This section is valid, keep going. First we will load frames.
			std::string frameLine = al_get_config_value(animCfg,section.c_str(),"frameName");

			// Tokenize it so we can load each one one by one
			std::vector<std::string> frameTokens = strTokenize(frameLine,',');

			// The int data as well... this is terrifying, but what do you want from 48 hours?
			std::string intString = al_get_config_value(animCfg,section.c_str(),"xOff");
			std::vector<int> xOffTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"yOff");
			std::vector<int> yOffTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"durations");
			std::vector<int> lenTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box0x");
			std::vector<int> box0xTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box0y");
			std::vector<int> box0yTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box0w");
			std::vector<int> box0wTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box0h");
			std::vector<int> box0hTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box1x");
			std::vector<int> box1xTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box1y");
			std::vector<int> box1yTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box1w");
			std::vector<int> box1wTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box1h");
			std::vector<int> box1hTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box2x");
			std::vector<int> box2xTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box2y");
			std::vector<int> box2yTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box2w");
			std::vector<int> box2wTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box2h");
			std::vector<int> box2hTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box3x");
			std::vector<int> box3xTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box3y");
			std::vector<int> box3yTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box3w");
			std::vector<int> box3wTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box3h");
			std::vector<int> box3hTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box4x");
			std::vector<int> box4xTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box4y");
			std::vector<int> box4yTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box4w");
			std::vector<int> box4wTokens = strToki(intString,',');
			intString = al_get_config_value(animCfg,section.c_str(),"box4h");
			std::vector<int> box4hTokens = strToki(intString,',');

			// Load various things coordinated with the number of frames
			animLength[index] = frameTokens.size();

			// Reserve vector slots so each frame doesn't reallocate for the vector 
			frames[index].reserve(animLength[index]);
			xOff[index].reserve(animLength[index]);
			yOff[index].reserve(animLength[index]);
			length[index].reserve(animLength[index]);

			for (int i = 0; i < 5; i++)
			{
				boxX[i][index].reserve(animLength[index]);
				boxY[i][index].reserve(animLength[index]);
				boxW[i][index].reserve(animLength[index]);
				boxH[i][index].reserve(animLength[index]);
			}

			for (unsigned int i = 0; i < animLength[index]; i++)
			{
				// Frame bitmaps
				ss.str("");
				
				// Tack on the image name to the path
				ss << filePath << frameTokens[i];

				frames[index].push_back(al_load_bitmap(ss.str().c_str()));
				xOff[index].push_back(xOffTokens[i]);
				yOff[index].push_back(yOffTokens[i]);
				length[index].push_back(lenTokens[i]);

				// Push these big nasties back!
				boxX[0][index].push_back(box0xTokens[i]);
				boxY[0][index].push_back(box0yTokens[i]);
				boxW[0][index].push_back(box0wTokens[i]);
				boxH[0][index].push_back(box0hTokens[i]);
				boxX[1][index].push_back(box1xTokens[i]);
				boxY[1][index].push_back(box1yTokens[i]);
				boxW[1][index].push_back(box1wTokens[i]);
				boxH[1][index].push_back(box1hTokens[i]);
				boxX[2][index].push_back(box2xTokens[i]);
				boxY[2][index].push_back(box2yTokens[i]);
				boxW[2][index].push_back(box2wTokens[i]);
				boxH[2][index].push_back(box2hTokens[i]);
				boxX[3][index].push_back(box3xTokens[i]);
				boxY[3][index].push_back(box3yTokens[i]);
				boxW[3][index].push_back(box3wTokens[i]);
				boxH[3][index].push_back(box3hTokens[i]);
				boxX[4][index].push_back(box4xTokens[i]);
				boxY[4][index].push_back(box4yTokens[i]);
				boxW[4][index].push_back(box4wTokens[i]);
				boxH[4][index].push_back(box4hTokens[i]);
			}

			// Load loopback value for the animation
			loop[index] = atoi(al_get_config_value(animCfg,section.c_str(),"loop"));
			index++;
		}
		else
		{
			// Done loading animations.
			numAnimations = index;
		}
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
		frameNum++;
		if (frameNum >= animLength[animNum])
		{
			if (loop[animNum] > -1)
			{
				frameNum = loop[animNum];
			}
			else
			{
				frameNum -= 1;
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
	unsigned int len = 0;
	for (unsigned int i = 0; i < animLength[num]; i++)
	{
		len += length[num][i];
	}
	return len;
}

ALLEGRO_BITMAP* Sprite::getFrame()
{
	return frames[animNum][frameNum];
}

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

std::vector<int> Sprite::strToki(std::string s, char delim)
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

bool Sprite::boxCol(Sprite* other, int myBox, int otherBox)
{

}