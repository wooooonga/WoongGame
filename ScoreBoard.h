#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include "cocos2d.h"
USING_NS_CC;

class ScoreBoard : public Layer
{
public:
	ScoreBoard() {}
	~ScoreBoard() {}
	static ScoreBoard* CreateScoreBoard(int score);
	virtual bool init();
	void showScore(int score);
	CREATE_FUNC(ScoreBoard);

};


#endif