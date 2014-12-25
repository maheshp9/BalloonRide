#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
#include "Balloon.h"
#include "EnemyGenerator.h"

/**
* This scene contains game objects and score.
* It inherits after CCLayer because it has only one layer.
*/
class MainScene :
	public Layer
{
public:
	MainScene();
	virtual bool init();
	static Scene* scene();
	void menuCloseCallback(Ref* pSender);
	virtual void onAcceleration(Acceleration* acc, Event* unused_event);
	virtual void onEnter() override;
	virtual void update(float dt);

	// implement the "static node()" method manually
	CREATE_FUNC(MainScene);

private:
	/**
	* Player controlled character.
	*/
	Balloon* __pBalloon;

	/**
	* Generates birds and planes.
	*/
	EnemyGenerator* __pEnemyGenerator;

	/**
	* Displays current score.
	*/
	LabelTTF* __pScoreLabel;

	/**
	* Current score value.
	*/
	int __score;

	/**
	* First element of a moving background.
	*/
	Sprite* __pBg1;

	/**
	* Second element of a moving background.
	*/
	Sprite* __pBg2;

	/**
	* Third element of a moving background.
	*/
	Sprite* __pBg3;

	void updateEnemies(Rect balloonRect, Vector<Enemy*>* pEnemies);
	void updateScore();
	void updateBgPosition(Sprite* pBg);
	void updateBackground();
};

#endif // __MAINSCENE_H__
