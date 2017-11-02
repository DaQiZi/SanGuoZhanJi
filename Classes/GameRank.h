#ifndef _GAME_RANK_H_
#define _GAME_RANK_H_

#include "cocos2d.h"
using namespace cocos2d;

class GameRank : public Layer{

public:
	
	static Scene* createScene();
	bool virtual init();
	CREATE_FUNC(GameRank);

	void initData();
	void returnClick();
private:
	Size winSize;
};


#endif