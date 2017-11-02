#ifndef _GAME_PAUSE_H_
#define _GAME_PAUSE_H_
#include "cocos2d.h"

using namespace cocos2d;
class GamePause : public Layer
{
public:
	virtual bool init();

	static Scene* createScene(RenderTexture* spr);

	CREATE_FUNC(GamePause);

	void menuContinueClick();
	void menuRestartClick();
	void menuReturnClick();

	void initData();
private:
	Size winSize;
};


#endif 