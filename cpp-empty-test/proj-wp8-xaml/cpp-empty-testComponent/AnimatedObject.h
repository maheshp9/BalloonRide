#ifndef ANIMATEDOBJECT_H_
#define ANIMATEDOBJECT_H_

#include "cocos2d.h"
using namespace cocos2d;
/**
* Base class for GameCharacters, holds sprite and animation.
*/
class AnimatedObject :
	public Node
{
public:
	/**
	* Tags used to indicate a sprite sheet.
	*/
	enum AnimTag
	{
		ANIM_BALLOON_SPRITESHEET,
		ANIM_PLANE_SPRITESHEET,
		ANIM_TWITTER_SPRITESHEET
	};

	AnimatedObject();
	void init(
		String textureFileName,
		String frameNamePrefix,
		int frameCount,
		float delay,
		Layer* layer,
		AnimTag spriteSheetTag);

	void init(
		String textureFileName,
		Layer* layer,
		AnimTag spriteTag);

	void setPosition(const Point& pos);
	cocos2d::Rect getRect();
	const cocos2d::Size& getSize();
	void destroy();

protected:
	/**
	* Array holding animation frames of game object sprite.
	*/
	//cocos2d::CCMutableArray<cocos2d::CCSpriteFrame*>* 	__pAnimationFrames;
	Vector<SpriteFrame*> __pAnimationFrames;

	/**
	* Sprite sheet holding game object animation frames.
	*/
	SpriteBatchNode* __pSpriteSheet;

	/**
	* Game object sprite.
	*/
	Sprite*	__pSprite;

	/**
	* Action describing game object animation.
	*/
	Action* __pAnimationAction;
};

#endif /* ANIMATEDOBJECT_H_ */
