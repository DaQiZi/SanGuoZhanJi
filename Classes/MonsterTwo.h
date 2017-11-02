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
	//�߶�ʱ�Ķ���
	void setAnimation(bool run_directon);
	//�����ܶ���
	//����ʱ�Ķ���
	void attackAnimation(bool run_directon);

	void hurtAnimation( bool run_directon);
	void deadAnimation( bool run_directon);

	void attackEnd();

	void stopAnimation();
	//���߶�  
	bool isRunning;
	//���﷽��

	/*
	
	true��ʾ���������
	false ���ұ�
	*/
	bool monsterDirection;
	//�ڹ���
	bool isAttack;


	CREATE_FUNC(MonsterTwo);


	//�ж�Ӣ�ۺ͹����λ��
	void followRun(Sprite* m_hero, Sprite* m_map);

	//�жϹ���
	void judgeAttack();

	//�����Ѳ��·��
	void monsterPatrol();

	//��ʼ����ļ���
	void startListener(Sprite* m_hero, Sprite* m_map);

	//Ӣ�ۺ͹���ľ���
	void updateMonster(float d);
	//���Ӣ���ڹ���Ŀ��ӷ�Χ�ڵ�ʱ��
	void update(float delta);
	//���ع��ﾫ��
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