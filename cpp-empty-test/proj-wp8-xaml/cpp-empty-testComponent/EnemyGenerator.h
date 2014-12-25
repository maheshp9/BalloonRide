#ifndef ENEMYGENERATOR_H_
#define ENEMYGENERATOR_H_

#include "cocos2d.h"
#include "Enemy.h"

/**
* This class will generate random opponents (e.g. birds and planes).
*/
class EnemyGenerator :
	public cocos2d::CCNode
{
public:
	EnemyGenerator();
	void init(Layer* pLayer);
	void start();
	Vector<Enemy*>* getEnemies();
	void remove(Vector<Enemy*>* pEnemies);

private:
	/**
	* Generated objects will be added as children of this layer.
	* It should be the MainLayer.
	*/
	Layer* __pLayer;

	/**
	* Holds generated enemy objects.
	*/
	Vector<Enemy*>*	  	  __pEnemies;

	/**
	* Size of the screen.
	*/
	Size __winSize;

	/**
	* This value is increased with every new enemy.
	*/
	float __enemySpeed;

	void generate(float dt);
};

#endif /* ENEMYGENERATOR_H_ */
