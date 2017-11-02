#ifndef _MONSTER_ONE_H_
#define _MONSTER_ONE_H_
#include "cocos2d.h"
#include "BloodProgress.h"
#include "FlyWord.h"
using namespace cocos2d;
class MonsterOne : public Sprite{
public:

	MonsterOne();
	~MonsterOne();
	void initMonsterSprite(char* monsterName);
	void initMonsterSprite(char* monsterName, char *xue_back, char* xue_fore);
	//走动时的动画
	void setAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);
	//正在跑动画
	//攻击时的动画
	void attackAnimation(const char *name_plist, const char *name_png,
		const char *name_each, const unsigned int num, bool run_directon);
	void attackEnd();

	void stopAnimation();
	//在走动  
	bool isRunning;
	//怪物方向
	bool monsterDirection;
	//在攻击
	bool isAttack;

	
	CREATE_FUNC(MonsterOne);


	//判断英雄和怪物的位置
	void followRun(Sprite* m_hero,Sprite* m_map);

	//判断攻击
	void judgeAttack();

	//怪物的巡逻路线
	void monsterPatrol();

	//开始怪物的监听
	void startListener(Sprite* m_hero, Sprite* m_map);

	//英雄和怪物的距离
	void updateMonster(float d);
	//检测英雄在怪物的可视范围内的时候
	void update(float delta);
	//返回怪物精灵
	Sprite* getSprite();


	void hurtAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);
	
	void hurtEnd();
	bool isHurt;

	void deadAnimation(const char *name_plist,
		const char *name_each, const unsigned int num, bool run_directon);



	void deadEnd();
	
	bool isDead;

	void blinkEnd();

	
private:

	char *monsterName;
	Sprite* monsterSprite;
	BloodProgress* bloodProgress;

	Sprite* my_hero;
	Sprite* my_map;
	float dis;


	
	
	//FlyWord* flyword;
};


#endif