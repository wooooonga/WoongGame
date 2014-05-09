#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__
namespace TAGNAME
{
	enum
	{
		TURTLE = 1,
		TUBE = 2,
		BOTTOMBOX = 3,
		FRAMEBOX = 4,
		HOWTOPLAY
	};

}

namespace GAMESTATE
{
	enum
	{
		READY = 0,
		START,
		FINISH
	};
};

namespace EVENT
{
	enum Sound
	{
		PLAY_BG_MUSIC = 1,
		TURTLE_COLLISION_TUBE = 2
	};

}

#endif