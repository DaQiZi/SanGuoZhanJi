#ifndef _HERO_H_
#define _HERO_H_
#include "cocos2d.h"
#include "BloodProgress.h"
using namespace cocos2d;

class Hero : public Sprite{

public :
	Hero();
	~Hero();
	void initHeroSprite(char* heroName);
	void initHeroSprite(char* heroName, char *xue_back, char* xue_fore);
	//走动时的动画
	void setAnimation(const char *name_plist, 
		const char *name_each, const unsigned int num, bool run_directon);
	//正在跑动画
	//攻击时的动画
	void attackAnimation(const char *name_plist, const char *name_png,
		const char *name_each, const unsigned int num, bool run_directon);
	//打中人之后，执行的动画
	void attackPersonAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);


	void skillAnimation(Ref* sender);
	//正在跑动画
	void attackEnd();
	void attackPersonEnd();

	void stopAnimation();
	//在走动  手柄控制的
	bool isRunning;
	//英雄的方向
	bool heroDirection;
	//在攻击
	bool isAttack;
	//英雄死亡
	bool isDead;

	//判断英雄的位置
	bool judgeHeroPosition(Size visibleSize);

	Sprite* getSprite();

	void hurtAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);

	void hurtEnd();
	CREATE_FUNC(Hero);
	BloodProgress* getBloodProgress();
	bool getHurt();
	void  setAttackPerson(bool temp);
	bool getAttackPerson();

	bool isAttackPersonAgain;
	int heroAttackNum;

	bool isDoubleHit;

private:

     char *heroName;
	 Sprite* heroSprite;
	 bool isHurt;
	 BloodProgress* bloodProgress;
	 bool isAttackPerson;
	
	
};


#endif