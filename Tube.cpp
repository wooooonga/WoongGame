#include "Tube.h"

USING_NS_CC;

Tube::Tube() 
	:capImgSize_x(64.f),
	 capImgSize_y(32.f),
	 tubeImgSize_x(64.f),
	 tubeImgSize_y(52.f),
	 vBottomSprite(NULL) {}
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
	int ChoiceTube	= std::rand() % 5;
	switch(ChoiceTube)
	{
	case TUBETYPE::OneBySix :	
		bottomNum	= 1;
		topNum		= 6;
		break;
	case TUBETYPE::SixByOne :
		bottomNum	= 6;
		topNum		= 1;
		break;
	case TUBETYPE::TwoByFive :
		bottomNum	= 2;
		topNum		= 5;
		break;
	case TUBETYPE::FiveByTwo :
		bottomNum	= 5;
		topNum		= 2;
		break;	
	case TUBETYPE::ThreeByTwo :
		bottomNum	= 3;
		topNum		= 4;
		break;
	default:
		break;
	}

	for(int i = 0; i < bottomNum; i++)
	{
		Sprite* bottom = Sprite::create("Img/MarioTube_Body.png");
		bottom->setPosition(StartingBottomPnt_.x + (tubeImgSize_x / 2), StartingBottomPnt_.y + (tubeImgSize_y / 2)+(i * tubeImgSize_y));
		this->addChild(bottom);
	}
	positionForCap = Point(StartingBottomPnt_.x, StartingBottomPnt_.y + (tubeImgSize_y * bottomNum));
	Sprite* pTubeCap = Sprite::create("Img/MarioTube_Top.png");
	pTubeCap->setPosition(positionForCap.x + (tubeImgSize_x / 2), positionForCap.y);

	PhysicsBody *tubeBody = PhysicsBody::createEdgeBox(Size(tubeImgSize_x, (tubeImgSize_y * bottomNum) + capImgSize_y), 
														MATERIAL_NONE, 1, Point(0, -(tubeImgSize_y * bottomNum) / 2));
	tubeBody->setMass(0);
	tubeBody->setDynamic(false);
	tubeBody->setContactTestBitmask(0x1<<1);
	pTubeCap->setPhysicsBody(tubeBody);
	pTubeCap->setTag(2);
	this->addChild(pTubeCap);
	vBottomSprite = pTubeCap;

	for(int i = 0; i < topNum; i++)
	{
		Sprite* top = Sprite::create("Img/MarioTube_Body.png");
		top->setPosition(Point(StartingTopPnt_.x + top->getContentSize().width / 2, StartingTopPnt_.y - (top->getContentSize().height / 2) -(i * top->getBoundingBox().size.height)));
		this->addChild(top);
	}
	positionForCap = Point(StartingTopPnt_.x, StartingTopPnt_.y -(tubeImgSize_y* topNum));
	Sprite* pTubeCap_r = Sprite::create("Img/MarioTube_Down.png");
	pTubeCap_r->setPosition(positionForCap.x + (tubeImgSize_x / 2), positionForCap.y);

	PhysicsBody *tubeBodyTop = PhysicsBody::createEdgeBox(Size(tubeImgSize_x, (tubeImgSize_y * topNum) + capImgSize_y),
														MATERIAL_NONE, 1, Point(0, ((tubeImgSize_y * topNum)) / 2 ));
	tubeBodyTop->setMass(0);
	tubeBodyTop->setDynamic(false);
	tubeBodyTop->setContactTestBitmask(0x1<<1);
	pTubeCap_r->setPhysicsBody(tubeBodyTop);
	pTubeCap_r->setTag(2);
	this->addChild(pTubeCap_r);
	vTopSprite = pTubeCap_r;
}

Point
Tube::GetTubePosition()
{
	if(vBottomSprite != NULL) 
	{
		return vBottomSprite->getPhysicsBody()->getPosition();
	}
	else
		return Point(0, 0);
		
}

void
Tube::update(float dt)
{
	vBottomSprite->setPosition(vBottomSprite->getPosition().x + (dt * 60 * -1 ), vBottomSprite->getPosition().y);
	vTopSprite->setPosition(vTopSprite->getPosition().x + (dt * 60 * -1 ), vTopSprite->getPosition().y);
	this->setPosition(this->getPosition().x + (dt * 60 * -1), this->getPosition().y);
	if(this->getPosition().x + endingPoint_ + capImgSize_x < -1)
	{
		this->removeAllChildren();
		this->setPosition(0, 0);
		CreateTube();
	}

}