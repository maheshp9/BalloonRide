#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class StartScene : public cocos2d::Layer
{
public:
	StartScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	static Scene* scene();
	void menuStartCallback(Ref* pSender);
	virtual void update(float dt);
	virtual void onEnter() override;
	CREATE_FUNC(StartScene);

private:
	Sprite* __pBg1;
	Sprite* __pBg2;
	Sprite* __pBg3;

	void updateBgPosition(Sprite* pBg);
};

#endif // __STARTSCENE_H__
