#ifndef _GAME_WIN_H_
#define _GAME_WIN_H_

#include "cocos2d.h"
#include  "cocos-ext.h"
#include "Player.h"


using namespace cocos2d;
USING_NS_CC_EXT;

class GameWin : public Layer, public EditBoxDelegate
{
public:

	~GameWin();

	static Scene* createScene(RenderTexture* spr,int s);

	virtual bool init();

	CREATE_FUNC(GameWin);

	void initData();


	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);

	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);

	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text);

	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);

	void menuRestartClick();
	void menuReturnClick();
	void nameOkClick();
	

	void initEditBox();
private:
	Size winSize;
	std::string name;
	EditBox* pEditBox_name;
	Menu* menuOK;
	int score;
	Layer* menuPause;


	int number;

	Player* playerArray[5];
};


#endif