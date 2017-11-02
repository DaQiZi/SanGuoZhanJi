#ifndef _MONSTER_TWO_H_
#define _MONSTER_TWO_H_
#include "cocos2d.h"
#include "BloodProgress.h"
#include "FlyWord.h"
#include "PersonAnimation.h"
//#include "ostrem"
using namespace cocos2d;

static std::uniform_int_distribution<unsigned> u(0,10000);
static std::default_random_engine e;

class MonsterTwo : public Sprite{
public:

	MonsterTwo();
	~MonsterTwo();
	void initMonsterSprite( char* monsterName);
	void initMonsterSprite(char *xue_back, char* xue_fore);
	//走动时的动画
	void setAnimation(bool run_directon);
	//正在跑动画
	//攻击时的动画
	void attackAnimation(bool run_directon);

	void hurtAnimation( bool run_directon);
	void deadAnimation( bool run_directon);

	void attackEnd();

	void stopAnimation();
	//在走动  
	bool isRunning;
	//怪物方向

	/*
	
	true表示人脸在左边
	false 在右边
	*/
	bool monsterDirection;
	//在攻击
	bool isAttack;


	CREATE_FUNC(MonsterTwo);


	//判断英雄和怪物的位置
	void followRun(Sprite* m_hero, Sprite* m_map);

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


	
	void hurtEnd();
	bool isHurt;

	



	void deadEnd();

	bool isDead;

	void blinkEnd();

	PersonAnimation* personinformation;
private:

	char *monsterName;
	Sprite* monsterSprite;
	BloodProgress* bloodProgress;

	Sprite* my_hero;
	Sprite* my_map;
	float dis;
	float lastdis;


	//PersonAnimation* personinformation;

	//FlyWord* flyword;
};


#endif