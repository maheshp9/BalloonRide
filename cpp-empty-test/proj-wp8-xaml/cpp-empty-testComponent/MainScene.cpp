#include "MainScene.h"
#include "EndScene.h"

using namespace cocos2d;
using namespace std;

MainScene::MainScene() :
__pBalloon(NULL),
__pEnemyGenerator(NULL),
__pScoreLabel(NULL),
__score(0),
__pBg1(NULL),
__pBg2(NULL),
__pBg3(NULL)
{
}

/**
* Call this method to create the MainScene.
*/
Scene*
MainScene::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	MainScene *layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

/**
* This method is called by node() method defined in LAYER_NODE_FUNC macro.
*/
bool
MainScene::init()
{
	// Init super first.
	if (!Layer::init())
	{
		return false;
	}
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("balloons.plist.xml", "balloons.png");

	// Ask director the window size.
	Size winSize = Director::sharedDirector()->getWinSize();

	//// Create close button.
	MenuItemImage *pCloseItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(MainScene::menuCloseCallback));
	pCloseItem->setPosition(ccp(winSize.width - 20, 20));

	// create menu, it's an autorelease object
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
	
	// Create the score label.
	__pScoreLabel = LabelTTF::create("Score: 0", "Arial", 50);
	// Position the label on the center of the screen.
	__pScoreLabel->setPosition(ccp(winSize.width / 2, winSize.height - 20));
	// Add the label as a child to this layer.
	this->addChild(__pScoreLabel, 2);

	// Create the background sprites.
	__pBg1 = Sprite::create("bg_duplicate.png");
	//Change the anchor point for convenience.
	__pBg1->setAnchorPoint(ccp(0, 0));
	__pBg1->setPosition(ccp(0, 0));

	float bgWidth = __pBg1->getContentSize().width;
	__pBg2 = Sprite::create("bg_duplicate.png");
	__pBg2->setAnchorPoint(ccp(0, 0));
	//Position the second sprite directly after the first.
	__pBg2->setPosition(ccp(bgWidth - 1, 0));

	__pBg3 = Sprite::create("bg_duplicate.png");
	__pBg3->setAnchorPoint(ccp(0, 0));
	//Position the third sprite directly after the second.
	__pBg3->setPosition(ccp(2 * (bgWidth - 1), 0));

	this->addChild(__pBg1, 0);
	this->addChild(__pBg2, 0);
	this->addChild(__pBg3, 0);

	return true;
}

void
MainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	return;
#endif
	Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

/**
* This callback sets xMove and yMove values of the balloon object.
*/
void
MainScene::onAcceleration(Acceleration* acc, Event* unused_event)
{
	__pBalloon->setMove(acc->y, acc->x);
}

/**
* This callback creates balloon object and enemy generator.
*/
void
MainScene::onEnter()
{
	// Remember to call the parent method.
	Layer::onEnter();

	
	__pBalloon = new Balloon();
	__pBalloon->init(*this);

	__pEnemyGenerator = new EnemyGenerator();
	__pEnemyGenerator->init(this);
	__pEnemyGenerator->start();

	// This method will schedule updates with every frame. This will call update() callback method.
	scheduleUpdate();

	//Start reading accelerometer values.
	this->setAccelerometerEnabled(true);
	
}

void
MainScene::update(float dt)
{
	updateBackground();
	updateScore();
	updateEnemies(__pBalloon->getRect(), __pEnemyGenerator->getEnemies());
}

void
MainScene::updateScore()
{
	__score += 1;
	const int labelLength = 100;
	char scoreLabelText[labelLength];
	snprintf(scoreLabelText, labelLength, "Score: %d", __score);
	if (__score % 10 == 0)
	{
		__pScoreLabel->setString(scoreLabelText);
	}
}

/**
* Check if an enemy is off screen and remove it if so.
* Check if an enemy is colliding with the balloon and end the game if that's the case.
* Change the scene if the game has ended.
*
* @param ballonRect Rectangle describing balloon borders.
* @param pEnemies Array of generated enemies.
*/
void
MainScene::updateEnemies(Rect balloonRect, Vector<Enemy*>* pEnemies)
{
	// When balloon hits a bird or plane, theEnd value is changed to true.
	// Currently the balloon has only one "life".
	bool theEnd = false;

	// This array will hold enemy objects that are off screen or in collision with the balloon.
	Vector<Enemy*>* pEnemiesToRemove = new Vector<Enemy*>();
	Vector<Enemy*>::iterator it;
	if (pEnemies && pEnemies->size() > 0)
	{
		for (it = pEnemies->begin(); it != pEnemies->end(); it++)
		{
			Enemy* pEnemy = *it;
			if (pEnemy)
			{
				Rect rect = pEnemy->getRect();
				bool collision = balloonRect.intersectsRect(rect);
				if (((rect.getMinX() < 0) && (rect.getMaxX() < 0))
					|| (collision))
				{
					// Enemy object is off screen or colliding with the balloon.
					if (collision)
					{
						// Enemy object is colliding with the balloon.
						theEnd = true;
					}
					pEnemiesToRemove->pushBack(pEnemy);
				}
			}
		}

		if (pEnemiesToRemove->size() > 0)
		{
			// Remove off screen or colliding objects.
			__pEnemyGenerator->remove(pEnemiesToRemove);
		}

		// Clean the array.
		pEnemiesToRemove->clear();
	}
	delete pEnemiesToRemove;
	pEnemiesToRemove = NULL;

	if (theEnd)
	{
		// Send the score to the endScene layer.
		CCScene *pScene = EndScene::scene();
		EndScene* pEs = (EndScene*)pScene->getChildByTag(EndScene::endLayerTag);
		pEs->setFinalScore(__score);

		// Run endScene.
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void
MainScene::updateBackground()
{
	updateBgPosition(__pBg1);
	updateBgPosition(__pBg2);
	updateBgPosition(__pBg3);
}

/**
* Move the background sprites.
* If a part is moved off the screen to left,
* it is moved back off the screen to the right.
*
* @param pBg The background sprite that should be moved.
*/
void
MainScene::updateBgPosition(CCSprite* pBg)
{
	if (pBg)
	{
		CCPoint bgPos = pBg->getPosition();
		bgPos.x -= 1;
		float bgWidth = pBg->boundingBox().size.width;
		if (bgPos.x < -bgWidth)
		{
			bgPos.x = 2 * bgWidth - 4;
			// To remove a black line between third and first part of the background,
			// after the first part has been moved to the right,
			// the part needs to be detached from the layer and added again.
			// This will move the first part on top of the others.
			// The object needs to be retained as removeChild would delete the object.
			pBg->retain();
			this->removeChild(pBg, false);
			this->addChild(pBg);
		};
		pBg->setPosition(bgPos);
	}
}
