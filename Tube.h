#ifndef __TUBE_H__
#define __TUBE_H__
#include "cocos2d.h"

USING_NS_CC;

namespace TUBETYPE
{
	enum
	{
		OneBySix = 0,
		SixByOne,
		TwoByFive,
		FiveByTwo,
		ThreeByTwo
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
	Point GetTubePosition();
private:
	Sprite* vBottomSprite;
	Sprite* vTopSprite;
	const PhysicsMaterial MATERIAL_NONE;


	Point StartingTopPnt_;
	Point StartingBottomPnt_;
	float endingPoint_;
	float capImgSize_x;
	float capImgSize_y;
	float tubeImgSize_x;
	float tubeImgSize_y;




};



#endif
