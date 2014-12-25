#include "AnimatedObject.h"

USING_NS_CC;

AnimatedObject::AnimatedObject() :
__pAnimationFrames(NULL),
__pSpriteSheet(NULL),
__pSprite(NULL),
__pAnimationAction(NULL)
{

}

/**
* This initializing method should be used if game object has animation frames.
* It loads a new sprite sheet for the game object, if it isn't already loaded.
* Next it creates animation frames using the sprite sheet.
* After that, it creates a new sprite and adds it as a child of the sprite sheet.
*
* @param textureFileName Name of a file containing game object textures.
* @param frameNamePrefix Frames are described in plist file in "prefixNumber" format, e.g. "balloon2.png".
* 						  This param describes the prefix, e.g. "balloon".
* @param frameCount	  The number of animation frames.
* @param delay			  Time in seconds between animation frames.
* @param layer			  Layer that will hold the sprite sheet.
* @param spriteSheetTag  Tag describing the sprite sheet.
*/
void
AnimatedObject::init(
String textureFileName,
String frameNamePrefix,
int frameCount,
float delay,
Layer* layer,
AnimTag spriteSheetTag)
{
	//Get the sprite sheet.
	__pSpriteSheet = (SpriteBatchNode*)layer->getChildByTag(spriteSheetTag);
	if (__pSpriteSheet == NULL)
	{
		//Create a new sprite sheet if it dosen't exit.
		/*const char* textureFileNameC = (const char*)StringUtil::StringToUtf8N(textureFileName)->GetPointer();
		__pSpriteSheet = CCSpriteBatchNode::batchNodeWithFile(textureFileNameC);*/
		__pSpriteSheet = SpriteBatchNode::create(textureFileName._string);
		if (__pSpriteSheet == NULL) { MessageBox("Sprite sheet is null!!", "Error"); return; }
		__pSpriteSheet->setTag(spriteSheetTag);
		layer->addChild(__pSpriteSheet, 1);
	}
	
	//Get animation frames.
	//__pAnimationFrames = new CCMutableArray<CCSpriteFrame*>();
	for (int i = 1; i <= frameCount; ++i)
	{
		std::ostringstream frameName;
		frameName << frameNamePrefix._string << i << ".png";
		SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName.str());
		if (spriteFrame == NULL) { MessageBox("SpriteFrame is null!!", "Error"); return; }
		__pAnimationFrames.pushBack(spriteFrame);
	}

	//Create animation
	Animation* animation = Animation::createWithSpriteFrames(__pAnimationFrames, delay);
	__pAnimationAction = RepeatForever::create(Animate::create(animation));

	Size size = Director::sharedDirector()->getWinSize();

	//Create game object sprite and add it to the sprite sheet.
	//const char* frameNameC = (const char*)StringUtil::StringToUtf8N(frameNamePrefix + "1.png")->GetPointer();
	std::ostringstream frameName;
	frameName << frameNamePrefix._string  << "1.png";
	__pSprite = Sprite::createWithSpriteFrameName(frameName.str());
	__pSprite->setPosition(ccp(size.width / 2, size.height / 2));
	__pSprite->runAction(__pAnimationAction);
	__pSpriteSheet->addChild(__pSprite);
}

/**
* This initializing method should be used if game object dosen't have animation frames.
* It loads a new sprite sheet for the game object, if it isn't already loaded.
* After that, it creates a new sprite and adds it as a child of the sprite sheet.
*
* @param textureFileName Name of a file containing game object textures.
* @param layer			  Layer that will hold the sprite sheet.
* @param spriteSheetTag  Tag describing the sprite sheet.
*/
void
AnimatedObject::init(
String textureFileName,
Layer* layer,
AnimTag spriteSheetTag)
{
	//Get the sprite sheet.
	__pSpriteSheet = (SpriteBatchNode*)layer->getChildByTag(spriteSheetTag);
	if (__pSpriteSheet == NULL)
	{
		//Create a new sprite sheet if it dosen't exit.
		__pSpriteSheet = SpriteBatchNode::create(textureFileName._string);
		__pSpriteSheet->setTag(spriteSheetTag);
		layer->addChild(__pSpriteSheet, 1);
	}

	Size size = Director::sharedDirector()->getWinSize();

	//Create game object sprite and add it to the sprite sheet.
	__pSprite = Sprite::create(textureFileName._string);
	__pSprite->setPosition(ccp(size.width / 2, size.height / 2));
	__pSpriteSheet->addChild(__pSprite);
}

/**
* Sets game objects sprite position.
* @param pos The new position.
*/
void
AnimatedObject::setPosition(const Point& pos)
{
	__pSprite->setPosition(pos);
}

/**
* @return game object sprite size.
*/
const Size&
AnimatedObject::getSize()
{
	return __pSprite->boundingBox().size;
}

/**
* Stop animation and remove the sprite.
*/
void
AnimatedObject::destroy()
{
	__pSprite->stopAllActions();
	__pSpriteSheet->removeChild(__pSprite, true);
}

/**
* @return the sprite rect.
*/
CCRect
AnimatedObject::getRect()
{
	//The rectangle width is reduced by 15 because textures have blank space around the object.
	return CCRectMake(__pSprite->getPosition().x - __pSprite->getContentSize().width / 2 + 15,
		__pSprite->getPosition().y - __pSprite->getContentSize().height / 2,
		__pSprite->getContentSize().width - 15,
		__pSprite->getContentSize().height);
}
