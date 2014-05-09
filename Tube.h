#ifndef __TUBE_H__
#define __TUBE_H__
#include "cocos2d.h"

USING_NS_CC;

namespace TUBETYPE
{
	enum
	{
		OneByFive = 0,
		FiveByOne,
		TwoByFour,
		FourByTwo,
		ThreeByThree,
	};
};
struct TubeNum
{
	int bottom;
	int top;
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
	void CreateTube(TubeNum);
	void SetArrowPosition(TubeNum);
	TubeNum	SetNewTubeType();
	Point	GetTubePosition();
	bool	GetWaitingTubeState()	{return hasWaitingTube_;}
private:
	Node* pCollisionTubeBottom;
	Node* pCollisionTubeTop;
	Sprite* pPlantBottom_;
	Sprite* pPlantTop_;
	cocos2d::Vector<SpriteFrame*> aniFrames1;
	cocos2d::Vector<SpriteFrame*> aniFrames2;

	const PhysicsMaterial MATERIAL_NONE;

	Point	StartingTopPnt_;
	Point	StartingBottomPnt_;

	TubeNum watingTubeType;
	Size	plantImgSize_;
	float	endingPoint_;
	float	capImgSize_x;
	float	capImgSize_y;
	float	tubeImgSize_x;
	float	tubeImgSize_y;
	int		scrollSpeed_;
	int		tubeCount_;
	bool	hasWaitingTube_;

};



#endif
