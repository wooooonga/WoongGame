#include "Tube.h"
#include "GlobalVar.h"

USING_NS_CC;

Tube::Tube() 
	:capImgSize_x(64.f),
	 capImgSize_y(32.f),
	 tubeImgSize_x(64.f),
	 tubeImgSize_y(52.f),
	 plantImgSize_(64.f, 54.f),
	 pCollisionTubeBottom(0),
	 pCollisionTubeTop(0),
	 scrollSpeed_(-2),
	 tubeCount_(0),
	 hasWaitingTube_(false)	{}
	 
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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/Plant.plist");
	char str[50] = {};
	for(int i = 1; i <=2; i++)
	{
		sprintf(str, "PlantBottom%d.png", i);
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		aniFrames1.pushBack(frame);
	}
	char str2[50] = {};
	for(int i = 1; i <=2; i++)
	{
		sprintf(str2, "PlantTop%d.png", i);
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str2);
		aniFrames2.pushBack(frame);
	}

	TubeNum tempTubeType = SetNewTubeType();
	CreateTube(tempTubeType);
	return true;
}

void
Tube::SetPoints(Point _top, Point _bottom, float _end)
{
	StartingTopPnt_		= _top;
	StartingBottomPnt_	= _bottom;
	endingPoint_		= _end;
}

TubeNum
Tube::SetNewTubeType()
{
	TubeNum tubeType;
	tubeType.bottom		= 0 ,
	tubeType.top		= 0;
	int ChoiceTube		= 0;

	srand(time(NULL));
	ChoiceTube	= std::rand() % 5;
	//if((watingTubeType.bottom == 1 && ChoiceTube == TUBETYPE::SixByOne) || (watingTubeType.bottom == 6 && ChoiceTube == TUBETYPE::OneBySix))
	//	ChoiceTube	= (std::rand() % 4) + 2;

	switch(ChoiceTube)
	{
	case TUBETYPE::OneByFive :	
		tubeType.bottom	= 1;
		tubeType.top	= 5;
		break;
	case TUBETYPE::FiveByOne :
		tubeType.bottom	= 5;
		tubeType.top	= 1;
		break;
	case TUBETYPE::TwoByFour :
		tubeType.bottom	= 2;
		tubeType.top	= 4;
		break;
	case TUBETYPE::FourByTwo :
		tubeType.bottom	= 4;
		tubeType.top	= 2;
		break;	
	case TUBETYPE::ThreeByThree :
		tubeType.bottom	= 3;
		tubeType.top	= 3;
		break;
	default:
		break;
	}

	watingTubeType = tubeType;
	hasWaitingTube_ = true;
	return tubeType;
}
void
Tube::CreateTube(TubeNum tubeNum)
{
	Point positionForCap;
	bool makePlant = false;

	for(int i = 0; i < tubeNum.bottom; i++)
	{
		Sprite* bottom = Sprite::create("Img/MarioTube_Body.png");
		bottom->setPosition(StartingBottomPnt_.x + (tubeImgSize_x / 2), StartingBottomPnt_.y + (tubeImgSize_y / 2)+(i * tubeImgSize_y));
		this->addChild(bottom);
	}
	positionForCap = Point(StartingBottomPnt_.x, StartingBottomPnt_.y + (tubeImgSize_y * tubeNum.bottom));
	Sprite* pTubeCap = Sprite::create("Img/MarioTube_Top.png");
	pTubeCap->setPosition(positionForCap.x + (tubeImgSize_x / 2), positionForCap.y);
	this->addChild(pTubeCap);

	PhysicsBody *tubeBody = PhysicsBody::createEdgeBox(Size(tubeImgSize_x, (tubeImgSize_y * tubeNum.bottom) + (capImgSize_y / 2)), 
		MATERIAL_NONE, 1,Point(tubeImgSize_x/2, ((tubeImgSize_y * tubeNum.bottom) + (capImgSize_y / 2))/2));
	tubeBody->setMass(0);
	tubeBody->setContactTestBitmask(0x1<<1);
	pCollisionTubeBottom = Node::create();
	pCollisionTubeBottom->setPosition(StartingBottomPnt_);
	pCollisionTubeBottom->setPhysicsBody(tubeBody);
	pCollisionTubeBottom->setTag(TAGNAME::TUBE);
	this->addChild(pCollisionTubeBottom);

	if(tubeCount_ >= 1) //Create Plant for random after tubecount 15.
	{
		srand(time(NULL));
		cocos2d::log("%d", std::rand() % 100);
		if(std::rand() % 100 < 80 || tubeCount_ == 1)
		{
			makePlant = true;
			if(rand()%2 == 0)
			{
				//////////////////////////
				// create Plant_Bottom
				//////////////////////////
				pPlantBottom_ = Sprite::create("Img/PlantBottom1.png");
				Animation *animation = Animation::createWithSpriteFrames(aniFrames1, 0.3f);
				Animate *animate = Animate::create(animation);
				RepeatForever* actionPlantBottom = RepeatForever::create(animate);
				pPlantBottom_->runAction(actionPlantBottom);

				pPlantBottom_->setPosition(positionForCap.x + (tubeImgSize_x / 2), positionForCap.y);
				ActionInterval *moveUp = MoveBy::create(1.f, Point(0, 40));
				ActionInterval *moveDown = MoveBy::create(10.f, Point(0, -40));
				FiniteTimeAction *seq = Sequence::create(moveUp, moveDown, NULL);
				pPlantBottom_->runAction(seq);

				PhysicsBody * plantBody = PhysicsBody::createEdgeBox(Size(plantImgSize_.width, plantImgSize_.height), 
					PHYSICSSHAPE_MATERIAL_DEFAULT, 1.f);
				plantBody->setDynamic(false);
				plantBody->setMass(2.f);
				plantBody->setContactTestBitmask(0x1<<1);
				pPlantBottom_->setPhysicsBody(plantBody);
				pPlantBottom_->setTag(TAGNAME::TUBE);
				this->addChild(pPlantBottom_, -1);
				makePlant = false;
			}
		}
	}

	for(int i = 0; i < tubeNum.top; i++)
	{
		Sprite* top = Sprite::create("Img/MarioTube_Body.png");
		top->setPosition(Point(StartingTopPnt_.x + top->getContentSize().width / 2, 
								StartingTopPnt_.y - (top->getContentSize().height / 2) -(i * top->getBoundingBox().size.height)));
		this->addChild(top);
	}

	positionForCap = Point(StartingTopPnt_.x, StartingTopPnt_.y -(tubeImgSize_y* tubeNum.top));
	Sprite* pTubeCap_r = Sprite::create("Img/MarioTube_Down.png");
	pTubeCap_r->setPosition(positionForCap.x + (tubeImgSize_x / 2), positionForCap.y);
	this->addChild(pTubeCap_r);

	PhysicsBody *tubeBodyTop = PhysicsBody::createEdgeBox(Size(tubeImgSize_x, (tubeImgSize_y * tubeNum.top) + (capImgSize_y / 2)), 
														PHYSICSSHAPE_MATERIAL_DEFAULT, 1,Point(tubeImgSize_x/2, ((tubeImgSize_y * tubeNum.top) + (capImgSize_y / 2)) / 2 * - 1));
	tubeBodyTop->setMass(0);
	tubeBodyTop->setContactTestBitmask(0x1<<1);
	pCollisionTubeTop = Node::create();
	pCollisionTubeTop->setPosition(StartingTopPnt_);
	pCollisionTubeTop->setPhysicsBody(tubeBodyTop);
	pCollisionTubeTop->setTag(TAGNAME::TUBE);
	this->addChild(pCollisionTubeTop);

	//////////////////////////
	// create Plant_Top
	//////////////////////////
	if(makePlant)
	{
		pPlantTop_ = Sprite::create("Img/PlantTop1.png");
		Animation *animation2 = Animation::createWithSpriteFrames(aniFrames2, 0.3f);
		Animate *animate2 = Animate::create(animation2);
		RepeatForever* actionPlantTop = RepeatForever::create(animate2);
		pPlantTop_->runAction(actionPlantTop);

		pPlantTop_->setPosition(positionForCap.x + (tubeImgSize_x / 2), positionForCap.y);
		ActionInterval *moveUp = MoveBy::create(1.f, Point(0, -40));
		ActionInterval *moveDown = MoveBy::create(10.f, Point(0, 40));
		FiniteTimeAction *seq = Sequence::create(moveUp, moveDown, NULL);
		pPlantTop_->runAction(seq);

		PhysicsBody * plantBody = PhysicsBody::createEdgeBox(Size(plantImgSize_.width, plantImgSize_.height), MATERIAL_NONE
			, 1.f);
		plantBody->setDynamic(false);
		plantBody->setMass(2.f);
		plantBody->setContactTestBitmask(0x1<<1);
		pPlantTop_->setPhysicsBody(plantBody);
		pPlantTop_->setTag(TAGNAME::TUBE);
		this->addChild(pPlantTop_, -1);

		makePlant = false;
	}

	hasWaitingTube_ = false;
}

Point
Tube::GetTubePosition()
{
	if(pCollisionTubeBottom != NULL) 
	{
		return pCollisionTubeBottom->getPhysicsBody()->getPosition();
	}
	else
		return Point(0, 0);
		
}

void
Tube::update(float dt)
{
	pCollisionTubeBottom->setPosition(pCollisionTubeBottom->getPosition().x + (dt * 60 * scrollSpeed_ ), pCollisionTubeBottom->getPosition().y);
	pCollisionTubeTop->setPosition(pCollisionTubeTop->getPosition().x + (dt * 60 * scrollSpeed_ ), pCollisionTubeTop->getPosition().y);
	this->setPosition(this->getPosition().x + (dt * 60 * scrollSpeed_), this->getPosition().y);

	if(this->getPosition().x + endingPoint_ + capImgSize_x < -1)
	{
		this->removeAllChildren(); 
		this->setPosition(0, 0);

		switch(++tubeCount_)
		{
		case 5:
			scrollSpeed_-= 1;
			break;
		default:
			break;
		}
		CreateTube(watingTubeType);
	}
}
