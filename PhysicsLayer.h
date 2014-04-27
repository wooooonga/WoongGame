#ifndef __PHYSICSLAYER_H__
#define __PHYSICSLAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class PhysicsLayer : public cocos2d::Layer
{
public:
	PhysicsLayer(void) {}
	~PhysicsLayer(void) {}

	Scene* createScene();
	void setPhyWorld(PhysicsWorld* world) {m_world = world};

private:
	PhysicsWorld *m_world;
};


#endif