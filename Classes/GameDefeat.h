#ifndef _GAME_DEFEAT_H_
#define _GAME_DEFEAT_H_
#include "cocos2d.h"

using namespace cocos2d;
class GameDefeat : public Layer
{
public:
	virtual bool init();

	static Scene* createScene(RenderTexture* spr);

	CREATE_FUNC(GameDefeat);

	
	void menuRestartClick();
	void menuReturnClick();

	void initData();
private:
	Size winSize;
};


#endif 