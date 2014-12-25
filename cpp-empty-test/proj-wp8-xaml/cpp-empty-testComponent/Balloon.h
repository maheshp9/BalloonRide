#ifndef BALLOON_H_
#define BALLOON_H_

#include "AnimatedObject.h"

/**
* Main character class. Handles balloon movement.
*/
class Balloon :
	public AnimatedObject
{
public:
	Balloon();
	void init(Layer& layer);
	void setMove(float x, float y);

private:
	/**
	* This value indicates how far the object should move based on accelerometer readings.
	*/
	float __xMove;

	/**
	* This value indicates how far the object should move based on accelerometer readings.
	*/
	float __yMove;

	/**
	* This is the balloon movement action. It is updated frequently.
	*/
	FiniteTimeAction* __pMoveAction;

	/**
	* Balloon movement speed.
	*/
	float __speed;

	/**
	* Size of the screen.
	*/
	Size __winSize;

	void move(float dt);
};

#endif /* BALLOON_H_ */
