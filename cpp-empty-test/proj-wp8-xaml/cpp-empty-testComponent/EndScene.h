#ifndef ENDSCENE_H_
#define ENDSCENE_H_

#include "cocos2d.h"
using namespace cocos2d;
/**
* This scene contains restart and exit buttons.
* It inherits after CCLayer because it has only one layer.
*/
class EndScene :
	public Layer
{
public:
	/**
	* This tag helps to find the layer when scene changes.
	*/
	static const int endLayerTag = 1;

	EndScene();
	bool init();
	static Scene* scene();
	void menuCloseCallback(Ref* pSender);
	void menuRestartCallback(Ref* pSender);
	void setFinalScore(int finalScore);
	void update(float dt);
	void onEnter();

	// implement the "static node()" method manually
	CREATE_FUNC(EndScene);

private:
	/**
	* This label will show the final score.
	*/
	LabelTTF* __pFinalScoreLabel;

	/**
	* First element of a moving background.
	*/
	Sprite* __pBg1;

	/**
	* Second element of the moving background.
	*/
	Sprite* __pBg2;

	/**
	* Third element of the moving background.
	*/
	Sprite* __pBg3;

	void updateBgPosition(Sprite* pBg);
};

#endif /* ENDSCENE_H_ */
