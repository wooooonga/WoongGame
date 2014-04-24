#include "Tube.h"

USING_NS_CC;

Tube::Tube() 
	:capImgSize_x(64.f)	{}
Tube::~Tube() {}

Tube* 
Tube::CreateTube(Point _top, Point _bottom, float _endPoint)
{
	Tube* pTube = new Tube;
	pTube->SetPoints(_top, _bottom, _endPoint);
	pTube->init();
	return pTube;
}
bool
Tube::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->scheduleUpdate();
	CreateTube();
	return true;
}

void
Tube::SetPoints(Point _top, Point _bottom, float _end)
{
	StartingTopPnt_ = _top;
	StartingBottomPnt_ = _bottom;
	endingPoint_ = _end;
}
void
Tube::CreateTube()
{
	Point positionForCap;
	int bottomNum	= 0 ,
		topNum		= 0;
	srand(time(NULL));
	int ChoiceTube	= std::rand() * 100 % 3;
	
	switch(ChoiceTube)
	{
	case TUBETYPE::ThreeByFour :	
		bottomNum	= 3;
		topNum		= 4;
		break;
	case TUBETYPE::FourByThree :
		bottomNum	= 4;
		topNum		= 3;
		break;
	case TUBETYPE::TwoByFive :
		bottomNum	= 2;
		topNum		= 5;
		break;
	case TUBETYPE::FiveByTwo :
		bottomNum	= 5;
		topNum		= 2;
		break;

	default:
		break;
	}

	for(int i = 0; i < bottomNum; i++)
	{
		Sprite* bottom = Sprite::create("Img/MarioTube_Body.png");
		bottom->setPosition(StartingBottomPnt_.x, StartingBottomPnt_.y + (i * bottom->getBoundingBox().size.height));
		bottom->setPosition( Point(StartingBottomPnt_.x, StartingBottomPnt_.y + (i * bottom->getBoundingBox().size.height)));
		bottom->setAnchorPoint(Point(0.f, 0.f));
		PhysicsBody *tubeBody = PhysicsBody::createBox(bottom->getContentSize());
		tubeBody->setMass(0);
		bottom->setPhysicsBody(tubeBody);
		this->addChild(bottom);
		vBottomSprite.push_back(bottom);
	}

	positionForCap = vBottomSprite.back()->getPosition();
	Sprite* pTubeCap = Sprite::create("Img/MarioTube_Top.png");
	pTubeCap->setAnchorPoint(Point(0.f, 0.f));
	pTubeCap->setPosition(positionForCap.x, positionForCap.y + pTubeCap->getBoundingBox().size.height);
	this->addChild(pTubeCap);
	vBottomSprite.push_back(pTubeCap);

	for(int i = 0; i < topNum; i++)
	{
		Sprite* top = Sprite::create("Img/MarioTube_Body.png");
		top->setPosition(StartingTopPnt_.x, StartingTopPnt_.y - (i * top->getBoundingBox().size.height));
		top->setAnchorPoint(Point(0.f, 1.f));
		vTopSprite.push_back(top);
		top->setPosition(Point(StartingTopPnt_.x, StartingTopPnt_.y - (i * top->getBoundingBox().size.height)));
		this->addChild(top);

	}
	positionForCap = vTopSprite.back()->getPosition();
	Sprite* pTubeCap_r = Sprite::create("Img/MarioTube_Down.png");
	pTubeCap_r->setAnchorPoint(Point(0.f, 1.f));
	pTubeCap_r->setPosition(positionForCap.x, positionForCap.y - pTubeCap_r->getBoundingBox().size.height);
	this->addChild(pTubeCap_r);
	vTopSprite.push_back(pTubeCap_r);

}

void
Tube::update(float dt)
{
	this->setPosition(this->getPosition().x + (dt * 60 * -1), this->getPosition().y);
	if(this->getPosition().x + endingPoint_ + capImgSize_x < -1)
	{
		this->removeAllChildren();
		this->setPosition(0, 0);
		CreateTube();
	}

}