#include "ScoreBoard.h"

USING_NS_CC;

ScoreBoard*
ScoreBoard::CreateScoreBoard(int score)
{
	ScoreBoard* layer = ScoreBoard::create();
	layer->showScore(score);
	return layer;
}

bool
ScoreBoard::init()
{
	Size winsize = Director::getInstance()->getWinSize();
	Sprite* scoreBoard = Sprite::create("Img/scoreBoard.png");
	scoreBoard->setPosition(winsize.width / 2, winsize.height /2);
	this->addChild(scoreBoard);
	ActionInterval* FadeIn = FadeIn::create(1.0);
	scoreBoard->runAction(FadeIn);
	
	return true;
}
void
ScoreBoard::showScore(int score)
{
	int highScore = UserDefault::getInstance()->getIntegerForKey("highScore"); 
	Size visibleSize_ = Director::getInstance()->getVisibleSize();

	if(score >= 10000)
	{
		char coinScore[50] = {0};
		sprintf(coinScore, "HIGH SCORE \n%d", highScore);
		LabelBMFont *font = LabelBMFont::create(coinScore, "fonts/FlappyFont.fnt", visibleSize_.width / 1.2, kCCTextAlignmentCenter);
		font->setPosition(visibleSize_.width / 2, visibleSize_.height / 2);
		this->addChild(font);
		return;
	}

	if(highScore < score)
	{
		char coinScore[50] = {0};
		sprintf(coinScore, "HIGH SCORE!!\n%d", score);
		LabelBMFont *font = LabelBMFont::create(coinScore, "fonts/FlappyFont.fnt", visibleSize_.width / 1.2, kCCTextAlignmentCenter);
		font->setPosition(visibleSize_.width / 2, visibleSize_.height / 2);
		this->addChild(font);

		UserDefault::getInstance()->setIntegerForKey("highScore", score);
		UserDefault::getInstance()->flush();
		return;
	}
		char coinScore[50] = {0};
		sprintf(coinScore, "Try Again ", highScore);

		LabelBMFont *font = LabelBMFont::create(coinScore, "fonts/FlappyFont.fnt", visibleSize_.width * 2, kCCTextAlignmentCenter);
		font->setPosition(visibleSize_.width / 2, visibleSize_.height / 2);
		font->setScale(0.8);
		this->addChild(font);
}