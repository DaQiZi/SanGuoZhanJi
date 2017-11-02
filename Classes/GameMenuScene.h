#ifndef _GAME_MENU_SCENE_H_
#define _GAME_MENU_SCENE_H_
#include "cocos2d.h"


#define SETBG 101
#define MUSICLABEL 102

using namespace cocos2d;
class GameMenuScene : public Layer
{
public:
	virtual bool init();

	static Scene* createScene();

	CREATE_FUNC(GameMenuScene);

	

	void initData();

	void menuStartClick();
	void menuExitClick();
	void menuEditClick();
	void menuRankClick();

	void initEditScene();

	void okClick();
	void setMusic(Ref* sender);
	void setVolume(Ref* sender);
private:
	Size winSize;
	Menu* menu;
	bool musicSwitch;
	float musicVolume;
};


#endif 