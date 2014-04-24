#ifndef __TUBE_H__
#define __TUBE_H__
#include "cocos2d.h"

USING_NS_CC;

namespace TUBETYPE
{
	enum
	{
		ThreeByFour = 0,
		FourByThree,
		TwoByFive,
		FiveByTwo
	};
};
class Tube : public Layer
{
public:	
	Tube();
	~Tube();
	static Tube* CreateTube(Point, Point, float);
	virtual bool init();
	virtual void update(float dt);

	void SetPoints(Point, Point, float);
	void CreateTube();
private:
	typedef std::vector<Sprite*> BottomVector;
	BottomVector vBottomSprite;
	typedef std::vector<Sprite*> TopVector;
	TopVector vTopSprite;

	Point StartingTopPnt_;
	Point StartingBottomPnt_;
	float endingPoint_;
	float capImgSize_x;


	Sprite* pTubebody_;
	Sprite* pTubebodyRev_;
	Sprite* pTubeTop_;
	Sprite* pTubeBottom_;


};



#endif
