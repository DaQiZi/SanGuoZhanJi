#ifndef _SKILL_BUTTON_H_
#define _SKILL_BUTTON_H_


#include "cocos2d.h"
using namespace cocos2d;

class SkillButton : public Layer{
public:

	~SkillButton();
	static SkillButton* create(const char* fore_name,const char* back_name);

	bool init(const char* fore_name, const char* back_name);


	void BeginSkill();

	void endSkill();

	bool isSkill;

	bool isSkillCool;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	///注册触摸代理支持  
	void changeSkillEnd(Ref* sender);
	
private:
	Sprite* sprFore;
	Sprite* sprBack;

	ProgressTimer* pt;

	EventListenerTouchOneByOne* listener;

	bool isCanClick;
};



#endif