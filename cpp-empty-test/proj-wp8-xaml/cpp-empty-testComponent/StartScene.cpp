
#include "StartScene.h"
#include "AppMacros.h"
#include "MainScene.h"

USING_NS_CC;

StartScene::StartScene() :
__pBg1(NULL),
__pBg2(NULL),
__pBg3(NULL)
{
}


CCScene* StartScene::scene()
{
	CCScene *scene = CCScene::create();
	StartScene *layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

/**
* This method is called by node() method defined in LAYER_NODE_FUNC macro.
*/
bool
StartScene::init()
{
	// Init super first.
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// Create start button.
	auto pStartButton = MenuItemFont::create("Start", CC_CALLBACK_1(StartScene::menuStartCallback, this));
	pStartButton->setFontSizeObj(50);

	pStartButton->setPosition(Vec2(visibleSize/2)+origin);

	// create menu, it's an autorelease object
	auto menu = Menu::create(pStartButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// Add background to cache.
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("background.plist", "bg_duplicate.png");

	// Create the background sprites.
	__pBg1 = Sprite::create("bg_duplicate.png");
	//Change the anchor point for convenience.
	__pBg1->setAnchorPoint(ccp(0, 0));
	__pBg1->setPosition(ccp(0, 0));

	float bgWidth = __pBg1->getContentSize().width;
	__pBg2 = Sprite::create("bg_duplicate.png");
	__pBg2->setAnchorPoint(ccp(0, 0));
	//Position the second sprite directly after the first (from left to right).
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
StartScene::menuStartCallback(Ref* pSender)
{
	Scene *pScene = MainScene::scene();
	Director::sharedDirector()->replaceScene(pScene);
}

void
StartScene::onEnter()
{
	// Remember to call the parent method.
	Layer::onEnter();
	// This method will schedule updates with every frame. This will call update() callback method.
	scheduleUpdate();
}

/**
* Update the background.
*/
void
StartScene::update(float dt)
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
StartScene::updateBgPosition(CCSprite* bg)
{
	if (bg)
	{
		CCPoint bgPos = bg->getPosition();
		bgPos.x -= 1;
		float bgWidth = bg->getContentSize().width;
		if (bgPos.x < -bgWidth)
		{
			bgPos.x = 2 * bgWidth - 4;
			// To remove a black line between third and first part of the background,
			// after the first part has been moved to the right,
			// the part needs to be detached from the layer and added again.
			// This will move the first part on top of the others.
			// The object needs to be retained as removeChild would delete the object.
			bg->retain();
			this->removeChild(bg, false);
			this->addChild(bg);
		};
		bg->setPosition(bgPos);
	}
}
