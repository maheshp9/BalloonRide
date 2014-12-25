#include "EnemyGenerator.h"
#include "AnimatedObject.h"

USING_NS_CC;

EnemyGenerator::EnemyGenerator() :
__pLayer(NULL),
__pEnemies(NULL),
__winSize(),
__enemySpeed(0)
{
}

/**
* Set balloon properties and schedule movement update.
* @param layer Layer that will hold sprites of generated objects.
*/
void
EnemyGenerator::init(Layer* layer)
{
	__pEnemies = new Vector<Enemy*>();
	__winSize = Director::sharedDirector()->getWinSize();
	__pLayer = layer;
	__pLayer->addChild(this);
	__enemySpeed = 200.0f;
	std::srand((unsigned)time(NULL));
}

/**
* Schedule object generation.
*/
void
EnemyGenerator::start()
{
	schedule(schedule_selector(EnemyGenerator::generate), 0.5f);
}

/**
* This callback will create
*/
void
EnemyGenerator::generate(float dt)
{
	//create new enemy object
	Enemy* enemy = new Enemy(__enemySpeed);
	__enemySpeed += 1.0f;

	String textureFileName = "plane.png";
	AnimatedObject::AnimTag tag = AnimatedObject::ANIM_PLANE_SPRITESHEET;

	int r = std::rand() % 100;
	if (r > 50)
	{
		// Change enemy
		textureFileName = "twitter.png";
		tag = AnimatedObject::ANIM_TWITTER_SPRITESHEET;
	}

	enemy->init(textureFileName, __pLayer, tag);

	// Choose random starting position
	CCSize enemySize = enemy->getSize();
	r = std::rand() % (int)(__winSize.height - enemySize.height) + enemySize.height / 2;
	float x = __winSize.width + enemySize.width;
	float y = r;
	enemy->setPosition(ccp(x, y));

	__pEnemies->pushBack(enemy);
	__pLayer->addChild(enemy);
	enemy->go();
}

Vector<Enemy*>*
EnemyGenerator::getEnemies()
{
	return __pEnemies;
}

/**
* Remove off screen or colliding objects.
* @param pEnemies Array of enemy objects that should be removed.
*/
void
EnemyGenerator::remove(Vector<Enemy*>* pEnemies)
{
	Vector<Enemy*>::iterator it;
	for (it = pEnemies->begin(); it != pEnemies->end(); it++)
	{
		Enemy* pEnemy = *it;
		pEnemy->destroy();
		__pEnemies->eraseObject(*it, false);
	}
	//__pEnemies->removeObjectsInArray(pEnemies);
}
